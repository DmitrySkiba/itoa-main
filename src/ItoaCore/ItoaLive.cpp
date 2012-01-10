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

#include "ItoaLive.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////// LiveHandler

#define JB_CURRENT_CLASS LiveHandler

JB_DEFINE_LIVE_CLASS(
    "com/itoa/LiveHandler"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>","()V"
    )
    ,
    Callbacks
    (
        Native(LiveHandler::RawHandleMessage),
        "nativeHandleMessage",
        "(Landroid/os/Message;)V"
    )
)

LiveHandler::LiveHandler():
    Handler(JB_NEW(Constructor),GetInstanceFieldID())
{
}

void LiveHandler::RawHandleMessage(JNIEnv*,jobject thiz,jobject message) {
    PLiveHandler::Wrap(thiz)->HandleMessage(PMessage::Wrap(message));
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// LiveDesktopLayout

#define JB_CURRENT_CLASS LiveDesktopLayout

JB_DEFINE_LIVE_CLASS(
    "com/itoa/LiveDesktopLayout"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(Landroid/content/Context;)V"
    )
    ,
    Callbacks
    (
        Native(LiveDesktopLayout::RawDispatchTouchEvent),
        "nativeDispatchTouchEvent",
        "(Landroid/view/MotionEvent;)Z"
    )
)

LiveDesktopLayout::LiveDesktopLayout(android::PContext context):
    FreeLayout(JB_NEW(Constructor,context),GetInstanceFieldID()),
    m_callback(0)
{
}

void LiveDesktopLayout::SetTouchCallback(TouchCallback* callback) {
    m_callback=callback;
}

bool LiveDesktopLayout::DoDispatchTouchEvent(android::PMotionEvent event) {
    if (m_callback) {
        return m_callback->OnTouchEvent(event);
    } else {
        return DispatchTouchEvent(event);
    }
}

bool LiveDesktopLayout::RawDispatchTouchEvent(JNIEnv*,jobject thiz,jobject event) {
    return PLiveDesktopLayout::Wrap(thiz)->DoDispatchTouchEvent(android::PMotionEvent::Wrap(event));
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// LiveViewImpl

LiveViewImpl::LiveViewImpl():
    m_callback(0)
{
}

void LiveViewImpl::OnDraw(PView view,PCanvas canvas) {
    if (m_callback) {
        m_callback->OnDraw(view,canvas);
    }
}

LiveViewCallback* LiveViewImpl::GetCallback() const {
    return m_callback;
}

void LiveViewImpl::SetCallback(LiveViewCallback* callback) {
    m_callback=callback;
}

///////////////////////////////////////////////// LiveView

LiveView::LiveView(const jni::LObject& object,jfieldID instanceField):
    View(object,instanceField)
{
}

///////////////////////////////////////////////// LiveViewGroup

LiveViewGroup::LiveViewGroup(const jni::LObject& object,jfieldID instanceField):
    ViewGroup(object,instanceField)
{
}

///////////////////////////////////////////////// LiveFreeLayout

#define JB_CURRENT_CLASS LiveFreeLayout

JB_DEFINE_LIVE_CLASS(
    "com/itoa/LiveFreeLayout"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(Landroid/content/Context;)V"
    )
    ,
    Callbacks
    (
        Native(LiveFreeLayout::RawOnDraw),
        "nativeOnDraw",
        "(Landroid/graphics/Canvas;)V"
    )
)

LiveFreeLayout::LiveFreeLayout(PContext context):
    LiveViewGroup(JB_NEW(Constructor,context),GetInstanceFieldID())
{
}

void LiveFreeLayout::RawOnDraw(JNIEnv*,jobject thiz,jobject canvas) {
    PLiveFreeLayout instance=PLiveFreeLayout::Wrap(thiz);
    instance->OnDraw(instance,PCanvas::Wrap(canvas));
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// LiveGenericView

#define JB_CURRENT_CLASS LiveGenericView

JB_DEFINE_LIVE_CLASS(
    "com/itoa/LiveView"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(Landroid/content/Context;)V"
    )
    ,
    Callbacks
    (
        Native(LiveGenericView::RawOnDraw),
        "nativeOnDraw",
        "(Landroid/graphics/Canvas;)V"
    )
)

LiveGenericView::LiveGenericView(PContext context):
    LiveView(JB_NEW(Constructor,context),GetInstanceFieldID())
{
}

void LiveGenericView::RawOnDraw(JNIEnv*,jobject thiz,jobject canvas) {
    PLiveGenericView instance=PLiveGenericView::Wrap(thiz);
    instance->OnDraw(instance,PCanvas::Wrap(canvas));
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// LiveButton

#define JB_CURRENT_CLASS LiveButton

JB_DEFINE_LIVE_CLASS(
    "com/itoa/LiveButton"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(Landroid/content/Context;)V"
    )
    ,
    NoCallbacks
)

LiveButton::LiveButton(PContext context):
    LiveView(JB_NEW(Constructor,context),GetInstanceFieldID())
{
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// LiveTextView

#define JB_CURRENT_CLASS LiveTextView

JB_DEFINE_LIVE_CLASS(
    "com/itoa/LiveTextView"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(Landroid/content/Context;)V"
    )
    ,
    NoCallbacks
)

LiveTextView::LiveTextView(PContext context):
    LiveView(JB_NEW(Constructor,context),GetInstanceFieldID())
{
}

android::PTextView LiveTextView::GetWrapper() const {
    return java::Cast<android::TextView>(*this);
}

#undef JB_CURRENT_CLASS

/////////////////////////////////////////////////

END_NAMESPACE(android)

