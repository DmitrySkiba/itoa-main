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

#ifndef _ITOALIVE_INCLUDED_
#define _ITOALIVE_INCLUDED_

#include "AndroidOS.h"
#include "AndroidView.h"
#include "AndroidWidget.h"
#include "ItoaWidget.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////// LiveHandler

class LiveHandler: public Handler {
    JB_LIVE_CLASS(LiveHandler);
protected:
    LiveHandler();
    virtual void HandleMessage(PMessage message)=0;
private:
    static void RawHandleMessage(JNIEnv*,jobject,jobject);
};

typedef java::ObjectPointer<LiveHandler> PLiveHandler;

///////////////////////////////////////////////// LiveDesktopLayout

class LiveDesktopLayout: public itoa::FreeLayout {
    JB_LIVE_CLASS(LiveDesktopLayout);
public:
    class TouchCallback;    
public:
    LiveDesktopLayout(android::PContext context);
    void SetTouchCallback(TouchCallback* callback);
private:
    bool DoDispatchTouchEvent(android::PMotionEvent event);
    static bool RawDispatchTouchEvent(JNIEnv*,jobject,jobject);
private:
    TouchCallback* m_callback;
};

typedef java::ObjectPointer<LiveDesktopLayout> PLiveDesktopLayout;

///////////////////////////////////////////////// LiveDesktopLayout::TouchCallback

class LiveDesktopLayout::TouchCallback {
public:
    TouchCallback() {}
    virtual ~TouchCallback() {}
    virtual bool OnTouchEvent(android::PMotionEvent event)=0;
private:
    TouchCallback(const TouchCallback&);
    TouchCallback& operator=(const TouchCallback&);
};

///////////////////////////////////////////////// LiveViewCallback

class LiveViewCallback {
public:
    LiveViewCallback() {}
    virtual void OnDraw(PView view,PCanvas canvas)=0;
private:
    LiveViewCallback(const LiveViewCallback&);
    LiveViewCallback& operator=(const LiveViewCallback&);
};

///////////////////////////////////////////////// LiveViewImpl

class LiveViewImpl {
public:
    LiveViewImpl();
    LiveViewCallback* GetCallback() const;
    void SetCallback(LiveViewCallback* callback);
protected:
    virtual void OnDraw(PView view,PCanvas canvas);
private:
    LiveViewCallback* m_callback;
};

///////////////////////////////////////////////// LiveView

class LiveView: public View, public LiveViewImpl {
protected:
    LiveView(const jni::LObject& object,jfieldID instanceField);
};

typedef java::ObjectPointer<LiveView> PLiveView;

///////////////////////////////////////////////// LiveViewGroup

class LiveViewGroup: public ViewGroup, public LiveViewImpl {
protected:
    LiveViewGroup(const jni::LObject& object,jfieldID instanceField);
};

typedef java::ObjectPointer<LiveViewGroup> PLiveViewGroup;

///////////////////////////////////////////////// LiveFreeLayout

class LiveFreeLayout: public LiveViewGroup {
    JB_LIVE_CLASS(LiveFreeLayout);
public:
    explicit LiveFreeLayout(PContext context);
private:
    static void RawOnDraw(JNIEnv*,jobject,jobject);
};

typedef java::ObjectPointer<LiveFreeLayout> PLiveFreeLayout;

///////////////////////////////////////////////// LiveGenericView

class LiveGenericView: public LiveView {
    JB_LIVE_CLASS(LiveGenericView);
public:
    explicit LiveGenericView(PContext context);
private:
    static void RawOnDraw(JNIEnv*,jobject,jobject);
};

typedef java::ObjectPointer<LiveGenericView> PLiveGenericView;

///////////////////////////////////////////////// LiveButton

class LiveButton: public LiveView {
    JB_LIVE_CLASS(LiveButton);
public:
    explicit LiveButton(PContext context);
};

typedef java::ObjectPointer<LiveButton> PLiveButton;

///////////////////////////////////////////////// LiveTextView

class LiveTextView: public LiveView {
    JB_LIVE_CLASS(LiveTextView);
public:
    LiveTextView(PContext context);
    android::PTextView GetWrapper() const;
};

typedef java::ObjectPointer<LiveTextView> PLiveTextView;

/////////////////////////////////////////////////

END_NAMESPACE(android)

#endif // _ITOALIVE_INCLUDED_

