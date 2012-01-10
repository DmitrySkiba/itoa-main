/*
 * Copyright (C) 2011 Dmitry Skiba
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "RunLoopPort.h"
#include <malloc.h>
#include <string.h>

///////////////////////////////////////////////// RunLoopPort

RunLoopPort::RunLoopPort():
    m_waiters(0),
    m_waiterCount(0),
    m_maxWaiterCount(0),
    m_signalled(false)
{
}
    
RunLoopPort::~RunLoopPort() {
    Close();
}

errno_t RunLoopPort::Create() {
    errno_t error=m_guard.init();
    if (error) {
        return error;
    }
    m_signalled=false;
    return 0;
}

void RunLoopPort::Close() {
    pthreadpp::mutex_wrapper_guard lock(m_guard);
    SignalWaitersLocked();
    RemoveWaitersLocked();
    m_signalled=false;
}

void RunLoopPort::Signal() {
    pthreadpp::mutex_wrapper_guard lock(m_guard);
    if (m_signalled) {
        return;
    }
    m_signalled=true;
    SignalWaitersLocked();
}

errno_t RunLoopPort::AddWaiter(Waiter & waiter,size_t myIndex) {
    pthreadpp::mutex_wrapper_guard lock(m_guard);
    if (m_waiterCount==m_maxWaiterCount) {
        size_t maxCount=m_maxWaiterCount?
            2*m_maxWaiterCount:
            16;
        WaiterInfo* waiters=(WaiterInfo*)malloc(
            maxCount*sizeof(WaiterInfo));
        if (!waiters) {
            return ENOMEM;
        }
        if (m_waiters) {
            memcpy(
                waiters,
                m_waiters,
                m_waiterCount*sizeof(WaiterInfo));
            free(m_waiters);
        }
        m_maxWaiterCount=maxCount;
        m_waiters=waiters;
    }
    WaiterInfo wi={&waiter,myIndex};
    m_waiters[m_waiterCount++]=wi;
    SignalWaiterLocked(waiter,myIndex);
    return 0;
}

void RunLoopPort::RemoveWaiter(Waiter & waiter) {
    pthreadpp::mutex_wrapper_guard lock(m_guard);
    for (size_t i=0;i!=m_waiterCount;++i) {
        if (m_waiters[i].waiter==&waiter) {
            memmove(
                m_waiters+i,
                m_waiters+(i+1),
                m_waiterCount-(i+1));
            m_waiterCount-=1;
            break;
        }
    }
}

void RunLoopPort::RemoveWaitersLocked() {
    if (m_waiters) {
        free(m_waiters);
        m_waiters=0;
        m_waiterCount=0;
        m_maxWaiterCount=0;
    }
}

void RunLoopPort::SignalWaiterLocked(Waiter & waiter,size_t myIndex) {
    if (m_signalled && waiter.Signal(myIndex)) {
        m_signalled=false;
    }
}

void RunLoopPort::SignalWaitersLocked() {
    for (size_t i=0;i!=m_waiterCount;++i) {
        if (!m_signalled) {
            break;
        }
        WaiterInfo & wi=m_waiters[i];
        SignalWaiterLocked(*wi.waiter,wi.myIndex);
    }
}

///////////////////////////////////////////////// RunLoopPort::Waiter

RunLoopPort::Waiter::Waiter():
    m_signalledIndex(InvalidIndex),
    m_signalCallback(0)
{
}

errno_t RunLoopPort::Waiter::Create() {
    errno_t error=m_cond.init();
    if (!error) {
        error=m_guard.init();
    }
    return error;
}

errno_t RunLoopPort::Waiter::Wait(int32_t milliseconds) {
    pthreadpp::mutex_wrapper_guard lock(m_guard);
    if (m_signalledIndex!=InvalidIndex) {
        return 0;
    }
    errno_t waitError;
    if (milliseconds>=0) {
        const int64_t Millisecond=1000;
        const int64_t MilliToNanosecond=1000000;

        int64_t absMilliseconds;
        {
            struct timespec time;
            if (clock_gettime(CLOCK_REALTIME,&time)) {
                return EAGAIN;
            }
            absMilliseconds=(time.tv_sec*Millisecond)+
                ((time.tv_nsec+MilliToNanosecond/2)/MilliToNanosecond);
        }
        absMilliseconds+=milliseconds;

        struct timespec absTime;
        {
            if ((absMilliseconds/Millisecond)>MaxWait) {
                waitError=pthread_cond_wait(&m_cond,&m_guard);
            } else {
                absTime.tv_sec=(int32_t)
                    (absMilliseconds/Millisecond);
                absTime.tv_nsec=(int32_t)
                    ((absMilliseconds%Millisecond)*MilliToNanosecond);
            }
        }
        waitError=pthread_cond_timedwait(&m_cond,&m_guard,&absTime);
    } else {
        if (milliseconds!=InfiniteWait) {
            return EINVAL;
        }
        waitError=pthread_cond_wait(&m_cond,&m_guard);
    }
    if (m_signalledIndex!=InvalidIndex) {
        return 0;
    }
    return waitError;
}

bool RunLoopPort::Waiter::Signal(size_t index) {
    pthreadpp::mutex_wrapper_guard lock(m_guard);
    if (m_signalledIndex!=InvalidIndex) {
        return false;
    }
    pthread_cond_signal(&m_cond);
    m_signalledIndex=index;
    FireSignalCallbackLocked();
    return true;
}

bool RunLoopPort::Waiter::IsSignalled() const {
    pthreadpp::mutex_wrapper_guard lock(m_guard);
    return m_signalledIndex!=InvalidIndex;
}

size_t RunLoopPort::Waiter::GetSignalledIndex() const {
    pthreadpp::mutex_wrapper_guard lock(m_guard);
    return m_signalledIndex;
}

void RunLoopPort::Waiter::SetSignalCallback(SignalCallback* callback) {
    pthreadpp::mutex_wrapper_guard lock(m_guard);
    m_signalCallback=callback;
    FireSignalCallbackLocked();
}

void RunLoopPort::Waiter::FireSignalCallbackLocked() {
    if (m_signalledIndex!=InvalidIndex && m_signalCallback) {
        m_signalCallback->OnSignalled(m_signalledIndex);
    }
}
