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

#ifndef _ITOAACTIVITY_INCLUDED_
#define _ITOAACTIVITY_INCLUDED_

#include <CoreFoundation/CFRunLoop.h>
#include "CommonIncludes.h"
#include "AndroidOS.h"
#include "AndroidView.h"
#include "ItoaWidget.h"
#include "AndroidContent.h"
#include "ItoaLive.h"
#include "misc/RunLoopPort.h"

BEGIN_NAMESPACE(itoa)

///////////////////////////////////////////////////////////////////// Activity

class Activity: public android::Context,
    private RunLoopPort::SignalCallback
{
    JB_LIVE_CLASS(Activity);
    typedef java::ObjectPointer<Activity> PActivity;
    class InternalHandler;
    struct WhatMessage;
    struct WhatActivityMessage;
    //TODO WhatMessage -> WhatInternalMessage, 
    //     HandleMessage-> HandleInternalMessage
public:
    android::PWindow GetWindow() const;
    android::PLiveDesktopLayout GetDesktopLayout() const;
    GraphicsRect GetDesktopFrame() const;
    static PActivity GetInstance();
private:
    Activity(const jni::LObject& object);
    virtual ~Activity();
    void OnCreate();
    void OnPause();
    void HandleActivityMessages(bool handle);
    bool HandleActivityMessage(android::PMessage message);
    void HandleMessage(android::PMessage message);
    virtual void OnSignalled(size_t portIndex);
    static void InitializeClass();
    static void RawOnCreate(JNIEnv*,jobject,jobject);
    static void RawOnPause(JNIEnv*,jobject);
    static jboolean RawHandleActivityMessage(JNIEnv*,jobject,jobject);
    static void RLPSetImpl();
    static Boolean RLPWait(CFArrayRef,CFTimeInterval,CFIndex*);
    friend jint ::JNI_OnLoad(JavaVM*,void*);
private:
    InternalHandler* m_handler;
    android::PLiveDesktopLayout m_desktopLayout;
    static PActivity m_instance;
};

typedef java::ObjectPointer<Activity> PActivity;

///////////////////////////////////////////////////////////////////// helpers

inline PActivity GetActivity() {
    return Activity::GetInstance();
}

/////////////////////////////////////////////////////////////////////

END_NAMESPACE(itoa)

#endif // _ITOAACTIVITY_INCLUDED_
