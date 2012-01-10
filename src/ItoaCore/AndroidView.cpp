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

#include "AndroidView.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////// MotionEvent

#define JB_CURRENT_CLASS MotionEvent

JB_DEFINE_WRAPPER_CLASS(
    "android/view/MotionEvent"
    ,
    NoFields
    ,
    Methods
    (
        GetAction,
        "getAction",
        "()I"
    )
    (
        GetDownTime,
        "getDownTime",
        "()J"
    )
    (
        GetX,
        "getX",
        "()F"
    )
    (
        GetY,
        "getY",
        "()F"
    )
    (
        SetLocation,
        "setLocation",
        "(FF)V"
    )
)

MotionEvent::MotionEvent(const jni::LObject& object):
    java::Object(object)
{
}

int32_t MotionEvent::GetAction() const {
    return JB_CALL_THIS(IntMethod,GetAction);
}

int64_t MotionEvent::GetDownTime() const {
    return JB_CALL_THIS(LongMethod,GetDownTime);
}

float MotionEvent::GetX() const {
    return JB_CALL_THIS(FloatMethod,GetX);
}

float MotionEvent::GetY() const {
    return JB_CALL_THIS(FloatMethod,GetY);
}

void MotionEvent::SetLocation(float x,float y) {
    JB_CALL_THIS(VoidMethod,SetLocation,x,y);
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// ViewLayoutParams

#define JB_CURRENT_CLASS ViewLayoutParams

JB_DEFINE_WRAPPER_CLASS(
    "android/view/ViewGroup$LayoutParams"
    ,
    Fields
    (
        Width,
        "width","I"
    )
    (
        Height,
        "height","I"
    )
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(II)V"
    )
)

ViewLayoutParams::ViewLayoutParams(int32_t width,int32_t height):
    java::Object(JB_NEW(Constructor,width,height))
{
}

ViewLayoutParams::ViewLayoutParams(const jni::LObject& object):
    java::Object(object)
{
}

int32_t ViewLayoutParams::GetWidth() const {
    return JB_GET_THIS(IntField,Width);
}

int32_t ViewLayoutParams::GetHeight() const {
    return JB_GET_THIS(IntField,Height);
}

GraphicsSize ViewLayoutParams::GetSize() const {
    return GraphicsSize(GetWidth(),GetHeight());
}

void ViewLayoutParams::SetWidth(int32_t width) {
    JB_SET_THIS(IntField,Width,width);
}

void ViewLayoutParams::SetHeight(int32_t height) {
    JB_SET_THIS(IntField,Height,height);
}

void ViewLayoutParams::SetSize(GraphicsSize size) {
    SetWidth(size.GetWidth());
    SetHeight(size.GetHeight());
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// View

#define JB_CURRENT_CLASS View

JB_DEFINE_WRAPPER_CLASS(
    "android/view/View"
    ,
    NoFields
    ,
    Methods
    (
        GetContext,
        "getContext",
        "()Landroid/content/Context;"
    )
    (
        GetWindowVisibleDisplayFrame,
        "getWindowVisibleDisplayFrame",
        "(Landroid/graphics/Rect;)V"
    )
    (
        GetLayoutParams,
        "getLayoutParams",
        "()Landroid/view/ViewGroup$LayoutParams;"
    )
    (
        SetLayoutParams,
        "setLayoutParams",
        "(Landroid/view/ViewGroup$LayoutParams;)V"
    )
    (
        Invalidate,
        "invalidate",
        "(Landroid/graphics/Rect;)V"
    )
    (
        RequestLayout,
        "requestLayout",
        "()V"
    )
    (
        GetVisibility,
        "getVisibility",
        "()I"
    )
    (
        SetVisibility,
        "setVisibility",
        "(I)V"
    )
    (
        SetBackgroundDrawable,
        "setBackgroundDrawable",
        "(Landroid/graphics/drawable/Drawable;)V"
    )
    (
        DispatchTouchEvent,
        "dispatchTouchEvent",
        "(Landroid/view/MotionEvent;)Z"
    )
)

View::View(const jni::LObject& object):
    java::Object(object)
{
}

View::View(const jni::LObject& object,jfieldID instanceField):
    java::Object(object,instanceField)
{
}

PContext View::GetContext() const {
    return PContext::Wrap(JB_CALL_THIS(ObjectMethod,GetContext));    
}

GraphicsRect View::GetWindowVisibleDisplayFrame() const {
    PRect rect(new Rect());
    JB_CALL_THIS(VoidMethod,GetWindowVisibleDisplayFrame,rect);
    return rect->GetRect();
}

PViewLayoutParams View::GetLayoutParams() const {
    return PViewLayoutParams::Wrap(
        JB_CALL_THIS(ObjectMethod,GetLayoutParams)
    );
}

void View::SetLayoutParams(PViewLayoutParams params) {
    JB_CALL_THIS(VoidMethod,SetLayoutParams,params);
}

void View::Invalidate(GraphicsRect grect) {
    PRect rect=PRect(new Rect(grect));
    JB_CALL_THIS(VoidMethod,Invalidate,rect);
}

void View::RequestLayout() {
    JB_CALL_THIS(VoidMethod,RequestLayout);
}

int32_t View::GetVisibility() const {
    return JB_CALL_THIS(IntMethod,GetVisibility);
}

void View::SetVisibility(int32_t visibility) {
    JB_CALL_THIS(VoidMethod,SetVisibility,visibility);
}

void View::SetBackgroundColor(int32_t color) {
    PBGColorDrawable drawable=new BGColorDrawable(color);
    JB_CALL_THIS(VoidMethod,SetBackgroundDrawable,drawable);
}

void View::RemoveBackground() {
    JB_CALL_THIS(VoidMethod,SetBackgroundDrawable,0);    
}

bool View::DispatchTouchEvent(PMotionEvent event) {
    return JB_CALL_THIS(BooleanMethod,DispatchTouchEvent,event);
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// ViewGroup

#define JB_CURRENT_CLASS ViewGroup

JB_DEFINE_WRAPPER_CLASS(
    "android/view/ViewGroup"
    ,
    NoFields
    ,
    Methods
    (
        AddView,
        "addView",
        "(Landroid/view/View;I)V"
    )
    (
        RemoveView,
        "removeView",
        "(Landroid/view/View;)V"
    )
    (
        RemoveViewAt,
        "removeViewAt",
        "(I)V"
    )
    (
        SetClipChildren,
        "setClipChildren",
        "(Z)V"
    )
)

ViewGroup::ViewGroup(const jni::LObject& object):
    View(object)
{
}

ViewGroup::ViewGroup(const jni::LObject& object,jfieldID instanceField):
    View(object,instanceField)
{
}

void ViewGroup::AddView(PView view) {
    AddView(view,-1);
}

void ViewGroup::AddView(PView view,int32_t index) {
    JB_CALL_THIS(VoidMethod,AddView,view,index);
}

void ViewGroup::RemoveView(PView view) {
    JB_CALL_THIS(VoidMethod,RemoveView,view);
}

void ViewGroup::RemoveViewAt(int32_t index) {
    JB_CALL_THIS(VoidMethod,RemoveViewAt,index);
}

void ViewGroup::SetClipChildren(bool clip) {
    JB_CALL_THIS(VoidMethod,SetClipChildren,clip);
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// Window

#define JB_CURRENT_CLASS Window

JB_DEFINE_WRAPPER_CLASS(
    "android/view/Window"
    ,
    NoFields
    ,
    Methods
    (
        GetDecorView,
        "getDecorView",
        "()Landroid/view/View;"
    )
    (
        SetFlags,
        "setFlags",
        "(II)V"
    )
    (
        SetContentView,
        "setContentView",
        "(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V"
    )
)

Window::Window(const jni::LObject& object):
    java::Object(object)
{
}

PView Window::GetDecorView() const {
    return new View(JB_CALL_THIS(ObjectMethod,GetDecorView));
}

void Window::AddFlags(int32_t flags) {
    SetFlags(flags,flags);
}

void Window::SetFlags(int32_t flags,int32_t mask) {
    JB_CALL_THIS(VoidMethod,SetFlags,flags,mask);
}

void Window::SetContentView(PView view,PViewLayoutParams layoutParams) {
    JB_CALL_THIS(VoidMethod,SetContentView,view,layoutParams);    
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// Display

#define JB_CURRENT_CLASS Display

JB_DEFINE_WRAPPER_CLASS(
    "android/view/Display"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(I)V"
    )
    (
        GetWidth,
        "getWidth",
        "()I"
    )
    (
        GetHeight,
        "getHeight",
        "()I"
    )
)

Display::Display(int32_t display):
    java::Object(JB_NEW(Constructor,display))
{
}

int32_t Display::GetWidth() const {
    return JB_CALL_THIS(IntMethod,GetWidth);
}

int32_t Display::GetHeight() const {
    return JB_CALL_THIS(IntMethod,GetHeight);
}

GraphicsSize Display::GetSize() const {
    return GraphicsSize(GetWidth(),GetHeight());
}

PDisplay Display::GetDefaultDisplay() {
    return new Display(DEFAULT_DISPLAY);
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// ViewConfiguration

#define JB_CURRENT_CLASS ViewConfiguration

JB_DEFINE_WRAPPER_CLASS(
    "android/view/ViewConfiguration"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(Landroid/content/Context;)V"
    )
    (
        GetScaledTouchSlop,
        "getScaledTouchSlop",
        "()I"
    )
)

ViewConfiguration::ViewConfiguration(PContext context):
    java::Object(JB_NEW(Constructor,context))
{
}

ViewConfiguration::ViewConfiguration(const jni::LObject& object):
    java::Object(object)
{
}

int32_t ViewConfiguration::GetScaledTouchSlop() const {
    return JB_CALL_THIS(IntMethod,GetScaledTouchSlop);
}

#undef JB_CURRENT_CLASS

/////////////////////////////////////////////////

END_NAMESPACE(android)

