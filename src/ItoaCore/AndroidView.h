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

#ifndef _ANDROIDVIEW_INCLUDED_
#define _ANDROIDVIEW_INCLUDED_

#include "CommonIncludes.h"
#include "GraphicsPrimitives.h"
#include "AndroidGraphics.h"
#include "AndroidContent.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////// MotionEvent

class MotionEvent: public java::Object {
    JB_WRAPPER_CLASS(MotionEvent);
public:
    const static int32_t ACTION_DOWN=0;
    const static int32_t ACTION_UP=1;
    const static int32_t ACTION_MOVE=2;
    const static int32_t ACTION_CANCEL=3;
    const static int32_t ACTION_OUTSIDE=4;
public:
    MotionEvent(const jni::LObject& object);
    int32_t GetAction() const;
    int64_t GetDownTime() const;
    float GetX() const;
    float GetY() const;
    void SetLocation(float x,float y);
};

typedef java::ObjectPointer<MotionEvent> PMotionEvent;

///////////////////////////////////////////////// ViewLayoutParams

class ViewLayoutParams: public java::Object {
    JB_WRAPPER_CLASS(ViewLayoutParams);
public:
    const static int32_t FILL_PARENT=-1;
    const static int32_t WRAP_CONTENT=-2;
public:
    ViewLayoutParams(int32_t width,int32_t height);
    ViewLayoutParams(const jni::LObject& object);
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    GraphicsSize GetSize() const;
    void SetWidth(int32_t width);
    void SetHeight(int32_t height);
    void SetSize(GraphicsSize size);
};

typedef java::ObjectPointer<ViewLayoutParams> PViewLayoutParams;

///////////////////////////////////////////////// View

class View: public java::Object {
    JB_WRAPPER_CLASS(View);
public:
    const static int32_t VISIBLE=0x00000000;
    const static int32_t INVISIBLE=0x00000004;
    const static int32_t GONE=0x00000008;
public:
    explicit View(const jni::LObject& object);
    PContext GetContext() const;
    GraphicsRect GetWindowVisibleDisplayFrame() const;
    PViewLayoutParams GetLayoutParams() const;
    void SetLayoutParams(PViewLayoutParams params);
    void Invalidate(GraphicsRect rect);
    void RequestLayout();
    int32_t GetVisibility() const;
    void SetVisibility(int32_t visibility);
    void SetBackgroundColor(int32_t color);
    void RemoveBackground();
    bool DispatchTouchEvent(PMotionEvent event);
protected:
    View(const jni::LObject& object,jfieldID instanceField);
};

typedef java::ObjectPointer<View> PView;

///////////////////////////////////////////////// ViewGroup

class ViewGroup: public View {
    JB_WRAPPER_CLASS(ViewGroup);
public:
    ViewGroup(const jni::LObject& object);
    void AddView(PView view);
    void RemoveView(PView view);
    void SetClipChildren(bool clip);
    virtual void AddView(PView view,int32_t index);
    virtual void RemoveViewAt(int32_t index);
protected:
    ViewGroup(const jni::LObject& object,jfieldID instanceField);
};

typedef java::ObjectPointer<ViewGroup> PViewGroup;

///////////////////////////////////////////////// Window

class Window: public java::Object {
    JB_WRAPPER_CLASS(Window);
public:
    const static int32_t FLAG_LAYOUT_IN_SCREEN=0x00000100;
public:
    explicit Window(const jni::LObject& object);
    PView GetDecorView() const;
    void AddFlags(int32_t flags);
    void SetFlags(int32_t flags,int32_t mask);
    void SetContentView(PView view,PViewLayoutParams layoutParams);
};

typedef java::ObjectPointer<Window> PWindow;

///////////////////////////////////////////////// Display

class Display: public java::Object {
    JB_WRAPPER_CLASS(Display);
    typedef java::ObjectPointer<Display> PDisplay;
public:
    const static int32_t DEFAULT_DISPLAY=0;
public:
    Display(int32_t display);
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    GraphicsSize GetSize() const;
    static PDisplay GetDefaultDisplay();
};

typedef java::ObjectPointer<Display> PDisplay;

///////////////////////////////////////////////// ViewConfiguration

class ViewConfiguration: public java::Object {
    JB_WRAPPER_CLASS(ViewConfiguration);
public:
    ViewConfiguration(PContext context);
    ViewConfiguration(const jni::LObject& object);
    int32_t GetScaledTouchSlop() const;
};

typedef java::ObjectPointer<ViewConfiguration> PViewConfiguration;

///////////////////////////////////////////////// Gravity

class Gravity {
public:
    const static int32_t NO_GRAVITY=0x0000;
    const static int32_t AXIS_SPECIFIED=0x0001;
    const static int32_t AXIS_PULL_BEFORE=0x0002;
    const static int32_t AXIS_PULL_AFTER=0x0004;
    const static int32_t AXIS_CLIP=0x0008;
    const static int32_t AXIS_X_SHIFT=0;
    const static int32_t AXIS_Y_SHIFT=4;
    const static int32_t TOP=(AXIS_PULL_BEFORE|AXIS_SPECIFIED)<<AXIS_Y_SHIFT;
    const static int32_t BOTTOM=(AXIS_PULL_AFTER|AXIS_SPECIFIED)<<AXIS_Y_SHIFT;
    const static int32_t LEFT=(AXIS_PULL_BEFORE|AXIS_SPECIFIED)<<AXIS_X_SHIFT;
    const static int32_t RIGHT=(AXIS_PULL_AFTER|AXIS_SPECIFIED)<<AXIS_X_SHIFT;
    const static int32_t CENTER_VERTICAL=AXIS_SPECIFIED<<AXIS_Y_SHIFT;
    const static int32_t FILL_VERTICAL=TOP|BOTTOM;
    const static int32_t CENTER_HORIZONTAL=AXIS_SPECIFIED<<AXIS_X_SHIFT;
    const static int32_t FILL_HORIZONTAL=LEFT|RIGHT;
    const static int32_t CENTER=CENTER_VERTICAL|CENTER_HORIZONTAL;
    const static int32_t FILL=FILL_VERTICAL|FILL_HORIZONTAL;
    const static int32_t CLIP_VERTICAL=AXIS_CLIP<<AXIS_Y_SHIFT;
    const static int32_t CLIP_HORIZONTAL=AXIS_CLIP<<AXIS_X_SHIFT;
    const static int32_t HORIZONTAL_GRAVITY_MASK=
        (AXIS_SPECIFIED | AXIS_PULL_BEFORE | AXIS_PULL_AFTER) << AXIS_X_SHIFT;
    const static int32_t VERTICAL_GRAVITY_MASK=
        (AXIS_SPECIFIED | AXIS_PULL_BEFORE | AXIS_PULL_AFTER) << AXIS_Y_SHIFT;
    const static int32_t DISPLAY_CLIP_VERTICAL=0x10000000;
    const static int32_t DISPLAY_CLIP_HORIZONTAL=0x01000000;
};

/////////////////////////////////////////////////

END_NAMESPACE(android)

#endif // _ANDROIDVIEW_INCLUDED_

