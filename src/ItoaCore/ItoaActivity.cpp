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

#include "ItoaActivity.h"
#include "misc/sofcn.h"
#include "Common/log.h"

extern "C" void call_dyld_handlers();

BEGIN_NAMESPACE(itoa)

///////////////////////////////////////////////////////////////////// helpers

static void CallMain() {
    call_dyld_handlers();
    soinfo_t* application=find_so("libapplication.so");
    if (application) {
        void* main=dlsym(application,"main");
        if (main) {
            const char* argv[]={"libapplication.so"};
            ((int(*)(int,const char**))main)(1,argv);
        }
    }
}

///////////////////////////////////////////////// JavaExit

#define JB_CURRENT_CLASS JavaExit

JB_DEFINE_ACCESSOR(
    "java/lang/System"
    ,
    NoFields
    ,
    Methods
    (
        RunFinalizersOnExit,
        "+runFinalizersOnExit",
        "(Z)V"
    )
    (
        Exit,
        "+exit",
        "(I)V"
    )
)

static void JavaExit(int32_t exitCode) {
    JB_CALL_STATIC(VoidMethod,RunFinalizersOnExit,true);
    JB_CALL_STATIC(VoidMethod,Exit,exitCode);
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////////////////////////// Activity:: classes

class Activity::InternalHandler: public android::LiveHandler {
public:
    InternalHandler(Activity& activity):
        m_activity(activity)
    {
    }
    virtual void HandleMessage(android::PMessage message) {
        m_activity.HandleMessage(message);    
    }
private:
    Activity& m_activity;
};

struct Activity::WhatMessage {
    enum ID {
        START,
        QUIT_LOOP,
        EXIT
    };
};

struct Activity::WhatActivityMessage {
    enum ID {
        PAUSE_ACTIVITY=101,
        PAUSE_ACTIVITY_FINISHING=102,
        RESUME_ACTIVITY=107,
    };
};

///////////////////////////////////////////////////////////////////// Activity

#define JB_CURRENT_CLASS Activity

JB_DEFINE_LIVE_CLASS(
    "com/itoa/ItoaActivity"
    ,
    NoFields
    ,
    Methods
    (
        GetWindow,
        "getWindow",
        "()Landroid/view/Window;"
    )
    (
        HandleActivityMessages,
        "handleActivityMessages",
        "(Z)V"
    )
    ,
    Callbacks
    (
        Native(Activity::RawOnCreate),
        "nativeOnCreate",
        "(Landroid/os/Bundle;)V"
    )
    (
        Native(Activity::RawOnPause),
        "nativeOnPause",
        "()V"
    )
    (
        Native(Activity::RawHandleActivityMessage),
        "nativeHandleActivityMessage",
        "(Landroid/os/Message;)Z"
    )
)

PActivity Activity::m_instance;

Activity::Activity(const jni::LObject& object):
    android::Context(object,GetInstanceFieldID()),
    m_handler(0)
{
}

Activity::~Activity() {
    if (m_handler) {
        m_handler->Release();
    }
}

android::PWindow Activity::GetWindow() const {
    return android::PWindow::Wrap(JB_CALL(ObjectMethod,*this,GetWindow));
}

android::PLiveDesktopLayout Activity::GetDesktopLayout() const {
    return m_desktopLayout;
}

GraphicsRect Activity::GetDesktopFrame() const {
    return GetWindow()->
        GetDecorView()->
        GetWindowVisibleDisplayFrame();
}

void Activity::InitializeClass() {
    JB_INIT_CLASS();    
}

PActivity Activity::GetInstance() {
    return m_instance;
}

void Activity::OnCreate() {
    RLPSetImpl();
    {
        android::PWindow window=GetWindow();
        android::PDisplay display=android::Display::GetDefaultDisplay(); 
        m_desktopLayout=new android::LiveDesktopLayout(this);
        window->AddFlags(android::Window::FLAG_LAYOUT_IN_SCREEN);
        window->SetContentView(
            m_desktopLayout,
            new android::ViewLayoutParams(display->GetWidth(),display->GetHeight()));
    }
    m_handler=new InternalHandler(*this);
    m_handler->Retain();
    m_handler->SendEmptyMessage(WhatMessage::START);
    HandleActivityMessages(true);
    android::Looper::MyQueue()->SetQuitAllowed(true);
}
void Activity::RawOnCreate(JNIEnv*,jobject thiz,jobject) {
    m_instance=PActivity(new Activity(jni::LObject::Wrap(thiz)));
    m_instance->OnCreate();
}

void Activity::OnPause() {
    m_handler->SendEmptyMessage(WhatMessage::EXIT);
}
void Activity::RawOnPause(JNIEnv*,jobject) {
    m_instance->OnPause();
}

void Activity::HandleMessage(android::PMessage message) {
    switch (message->GetWhat()) {
        case WhatMessage::START:
        {
            CallMain();
            break;        
        }
        case WhatMessage::QUIT_LOOP:
        {
            android::Looper::MyLooper()->Quit();
            break;
        }
        case WhatMessage::EXIT:
        {
            LOG("Exiting...");
            JavaExit(0);
            break;
        }
    }
}

void Activity::HandleActivityMessages(bool handle) {
    JB_CALL_THIS(VoidMethod,HandleActivityMessages,handle);
}

bool Activity::HandleActivityMessage(android::PMessage message) {
    if (message->GetWhat()==WhatActivityMessage::PAUSE_ACTIVITY ||
        message->GetWhat()==WhatActivityMessage::PAUSE_ACTIVITY_FINISHING)
    {
        LOG("Preparing to exit...");
        HandleActivityMessages(false);
        android::PMessage messageCopy=android::Message::Obtain(message);
        message->GetTarget()->SendMessage(messageCopy);
        android::Looper::MyLooper()->Quit();
        CFRunLoopStop(CFRunLoopGetMain());
        return true;
    }
    return false;
}
jboolean Activity::RawHandleActivityMessage(JNIEnv*,jobject thiz,jobject message) {
    return m_instance->HandleActivityMessage(android::PMessage::Wrap(message));
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// RunLoopPort stuff

inline RunLoopPort* GetRLP(void* data) {
    return static_cast<RunLoopPort*>(data);
}
inline RunLoopPort* GetRLPFromRef(const void* ref) {
    return GetRLP(CFRunLoopPortGetImplData(CFRunLoopPortRef(ref)));
}

static void RLPDestroy(void* data) {
    GetRLP(data)->~RunLoopPort();
}
static Boolean RLPCreate(void* data) {
    new (data) RunLoopPort();
    errno_t error=GetRLP(data)->Create();
    if (error) {
        RLPDestroy(data);
        return false;
    }
    return true;
}
static Boolean RLPSignal(void* data) {
    GetRLP(data)->Signal();
    return true;
}

void Activity::OnSignalled(size_t portIndex) {
    m_handler->SendEmptyMessage(WhatMessage::QUIT_LOOP);
}

//TODO add NSAutoreleasePool somewhere into the event loop

Boolean Activity::RLPWait(CFArrayRef ports,CFTimeInterval interval,CFIndex* signalledIndex) {
    *signalledIndex=-1;
    RunLoopPort::Waiter waiter;
    errno_t error=error=waiter.Create();
    if (error) {
        return false;
    }
    //TODO do callback trick on main thread only
    waiter.SetSignalCallback(&*m_instance);
    CFIndex count=CFArrayGetCount(ports);
    //LOG("waiting %d ports for %g seconds...",count,interval);
    for (CFIndex i=0;i!=count;++i) {
        RunLoopPort* port=GetRLPFromRef(CFArrayGetValueAtIndex(ports,i));
        error=port->AddWaiter(waiter,i);
        if (error || waiter.IsSignalled()) {
            if (!error) {
                port->RemoveWaiter(waiter);
            }
            for (;i;) {
                RunLoopPort* port=GetRLPFromRef(CFArrayGetValueAtIndex(ports,--i));
                port->RemoveWaiter(waiter);
            }
            if (waiter.IsSignalled()) {
                *signalledIndex=CFIndex(waiter.GetSignalledIndex());
                error=0;
            }
            //LOG("wait completed: %d [%d]",int(!error || error==ETIMEDOUT),*signalledIndex);
            return !error || error==ETIMEDOUT;
        }
    }
    int32_t milliseconds=0;
    if ((interval*1000)>RunLoopPort::Waiter::MaxWait) {
        milliseconds=RunLoopPort::Waiter::InfiniteWait;
    } else {
        milliseconds=int32_t(interval*1000);
    }
    {
        if (milliseconds!=RunLoopPort::Waiter::InfiniteWait) {
            m_instance->m_handler->SendEmptyMessageDelayed(
                WhatMessage::QUIT_LOOP,
                milliseconds);
        }
        android::Looper::Loop();
        m_instance->m_handler->RemoveMessages(WhatMessage::QUIT_LOOP);
    }
    //error=waiter.Wait(milliseconds);
    for (CFIndex i=0;i!=count;++i) {
        RunLoopPort* port=GetRLPFromRef(CFArrayGetValueAtIndex(ports,i));
        port->RemoveWaiter(waiter);
    }
    if (waiter.IsSignalled()) {
        *signalledIndex=CFIndex(waiter.GetSignalledIndex());
        error=0;
    }
    //LOG("wait completed: %d [%d]",int(!error || error==ETIMEDOUT),*signalledIndex);
    return !error || error==ETIMEDOUT;
}

void Activity::RLPSetImpl() {
    CFRunLoopPortImpl impl={
        sizeof(RunLoopPort),
        RLPCreate,
        RLPDestroy,
        RLPSignal,
        &Activity::RLPWait
    };
    CFRunLoopPortSetImpl(&impl);
}

/////////////////////////////////////////////////////////////////////

END_NAMESPACE(itoa)

