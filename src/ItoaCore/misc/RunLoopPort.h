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

#ifndef _RUNLOOPPORT_INCLUDED_
#define _RUNLOOPPORT_INCLUDED_

#include <dropins/pthreadpp.h>
#include <Common/NonCopyable.h>
#include <dropins/errno_t.h>
#include <stdint.h>

/* These classes are somewhat complicated because they are
 *  used from C interface, so no exceptions are allowed.
 */

///////////////////////////////////////////////// RunLoopPort

class RunLoopPort: NonCopyable {
public:
    class Waiter;
    class SignalCallback;
public:
    RunLoopPort();
    ~RunLoopPort();
    errno_t Create();
    void Signal();
    errno_t AddWaiter(Waiter & waiter,size_t myIndex);
    void RemoveWaiter(Waiter & waiter);
private:
    void Close();
    void SignalWaiterLocked(Waiter&,size_t);
    void SignalWaitersLocked();
    void RemoveWaitersLocked();
private:
    struct WaiterInfo {
        Waiter* waiter;
        size_t myIndex;
    };
    WaiterInfo* m_waiters;
    size_t m_waiterCount;
    size_t m_maxWaiterCount;
    pthreadpp::mutex_wrapper m_guard;
    bool m_signalled;
};

///////////////////////// RunLoopPort::Waiter

class RunLoopPort::Waiter: NonCopyable {
public:
    const static int32_t MaxWait=0x7FFFFFFF;
    const static int32_t InfiniteWait=0xFFFFFFFF;
public:
    Waiter();
    errno_t Create();
    errno_t Wait(int32_t milliseconds);
    bool Signal(size_t index);
    bool IsSignalled() const;
    size_t GetSignalledIndex() const;
    void SetSignalCallback(SignalCallback* callback);
private:
    void FireSignalCallbackLocked();
private:
    pthreadpp::cond_wrapper m_cond;
    mutable pthreadpp::mutex_wrapper m_guard;
    size_t m_signalledIndex;
    SignalCallback* m_signalCallback;
    const static size_t InvalidIndex=(size_t)-1;
};

///////////////////////// RunLoopPort::SignalCallback

class RunLoopPort::SignalCallback: NonCopyable {
public:
    virtual void OnSignalled(size_t portIndex)=0;
};

/////////////////////////////////////////////////

#endif // _RUNLOOPPORT_INCLUDED_

