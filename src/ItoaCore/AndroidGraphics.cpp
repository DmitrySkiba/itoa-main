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

#include "AndroidGraphics.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////// Matrix

#define JB_CURRENT_CLASS Matrix

JB_DEFINE_WRAPPER_CLASS(
    "android/graphics/Matrix"
    ,
    Fields
    (
        NativeInstance,
        "native_instance",
        "I"
    )
    ,
    Methods
    (
        Constructor,
        "<init>",
        "()V"
    )
)

///////////////////////////////////////

class Matrix::Instance {
    const static uint8_t kUnknown_Mask=0x80;
public:
    const float* GetValues() const {
        return m_values;
    }
    void SetValues(const float* values) {
        memcpy(m_values,values,sizeof(m_values));
        m_typeMask=kUnknown_Mask;
    }
private:
    Instance();
    Instance(const Instance&);
    Instance& operator=(const Instance&);
private:
    float m_values[9];
    uint8_t m_typeMask;
};

///////////////////////////////////////

Matrix::Matrix():
    java::Object(JB_NEW(Constructor))
{
}

Matrix::Matrix(const jni::LObject& object):
    java::Object(object)
{
}

Matrix::Instance* Matrix::GetInstance() const {
    int32_t instance=JB_GET_THIS(IntField,NativeInstance);
    return reinterpret_cast<Instance*>(instance);
}

const float* Matrix::GetValues() const {
    return GetInstance()->GetValues();
}

void Matrix::SetValues(const float* values) {
    GetInstance()->SetValues(values);
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// Rect

#define JB_CURRENT_CLASS Rect

JB_DEFINE_WRAPPER_CLASS(
    "android/graphics/Rect"
    ,
    Fields
    (
        Left,
        "left","I"
    )
    (
        Right,
        "right","I"
    )
    (
        Top,
        "top","I"
    )
    (
        Bottom,
        "bottom","I"
    )
    ,
    Methods
    (
        Constructor,
        "<init>","()V"
    )
)

Rect::Rect():
    java::Object(JB_NEW(Constructor))
{
}

Rect::Rect(const GraphicsRect& rect):
    java::Object(JB_NEW(Constructor))
{
    SetRect(rect);
}

Rect::Rect(const jni::LObject& object):
    java::Object(object)
{
}

GraphicsRect Rect::GetRect() const {
    int32_t left=JB_GET_THIS(IntField,Left);
    int32_t right=JB_GET_THIS(IntField,Right);
    int32_t top=JB_GET_THIS(IntField,Top);
    int32_t bottom=JB_GET_THIS(IntField,Bottom);
    return GraphicsRect::MakeLTRB(left,top,right,bottom);
}

void Rect::SetRect(const GraphicsRect& rect) {
    JB_SET_THIS(IntField,Left,rect.left);
    JB_SET_THIS(IntField,Top,rect.top);
    JB_SET_THIS(IntField,Right,rect.right);
    JB_SET_THIS(IntField,Bottom,rect.bottom);
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// Paint

#define JB_CURRENT_CLASS Paint

JB_DEFINE_WRAPPER_CLASS(
    "android/graphics/Paint"
    ,
    Fields
    (
        NativePaint,
        "mNativePaint","I"
    )
    ,
    Methods
    (
        Constructor,
        "<init>",
        "()V"
    )
    (
        GetStyle,
        "+native_getStyle",
        "(I)I"
    )
    (
        SetStyle,
        "+native_setStyle",
        "(II)V"
    )
    (
        GetColor,
        "getColor",
        "()I"
    )
    (
        SetColor,
        "setColor",
        "(I)V"
    )
)

Paint::Paint():
    java::Object(JB_NEW(Constructor))
{
}

Paint::Paint(const jni::LObject& object):
    java::Object(object)
{
}
    
PaintStyleID Paint::GetStyle() const {
    int32_t nativePaint=JB_GET_THIS(IntField,NativePaint);
    return PaintStyleID(
        JB_CALL_STATIC(IntMethod,GetStyle,nativePaint)
    );
}

void Paint::SetStyle(PaintStyleID style) {
    int32_t nativePaint=JB_GET_THIS(IntField,NativePaint);
    JB_CALL_STATIC(VoidMethod,SetStyle,nativePaint,int32_t(style));    
}

int32_t Paint::GetColor() const {
    return JB_CALL_THIS(IntMethod,GetColor);
}

void Paint::SetColor(int32_t color) {
    JB_CALL_THIS(VoidMethod,SetColor,color);
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// Drawable

Drawable::Drawable(const jni::LObject& object):
    java::Object(object)
{
}

Drawable::Drawable(const jni::LObject& object,jfieldID instanceField):
    java::Object(object,instanceField)
{
}

///////////////////////////////////////////////// BGColorDrawable

#define JB_CURRENT_CLASS BGColorDrawable

JB_DEFINE_WRAPPER_CLASS(
    "com/itoa/BGColorDrawable"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>","(I)V"
    )
)

BGColorDrawable::BGColorDrawable(int32_t color):
    Drawable(JB_NEW(Constructor,color))
{
}

BGColorDrawable::BGColorDrawable(const jni::LObject& object):
    Drawable(object)
{
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// Canvas

#define JB_CURRENT_CLASS Canvas

JB_DEFINE_WRAPPER_CLASS(
    "android/graphics/Canvas"
    ,
    NoFields
    ,
    Methods
    (
        DrawRectCoordinates,
        "drawRect",
        "(FFFFLandroid/graphics/Paint;)V"
    )
)

Canvas::Canvas(const jni::LObject& object):
    java::Object(object)
{
}

void Canvas::DrawRect(
    float left,float top,float right,float bottom,
    PPaint paint)
{
    JB_CALL_THIS(VoidMethod,
        DrawRectCoordinates,
        left,top,right,bottom,paint);
}

#undef JB_CURRENT_CLASS

/////////////////////////////////////////////////

END_NAMESPACE(android)

