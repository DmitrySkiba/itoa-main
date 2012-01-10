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

#include "ItoaWidget.h"

BEGIN_NAMESPACE(itoa)

///////////////////////////////////////////////// FreeLayoutParams

#define JB_CURRENT_CLASS FreeLayoutParams

JB_DEFINE_WRAPPER_CLASS(
    "com/itoa/FreeLayout$LayoutParams"
    ,
    Fields
    (
        Matrix,
        "matrix","Landroid/graphics/Matrix;"
    )
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(IILandroid/graphics/Matrix;)V"
    )
)

FreeLayoutParams::FreeLayoutParams():
    ViewLayoutParams(JB_NEW(Constructor,0,0,0))
{
}

FreeLayoutParams::FreeLayoutParams(int32_t width,int32_t height,android::PMatrix matrix):
    ViewLayoutParams(JB_NEW(Constructor,width,height,matrix))
{
}

FreeLayoutParams::FreeLayoutParams(const jni::LObject& object):
    ViewLayoutParams(object)
{
}

android::PMatrix FreeLayoutParams::GetMatrix() const {
    return android::PMatrix::Wrap(JB_GET_THIS(ObjectField,Matrix));
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// FreeLayout

#define JB_CURRENT_CLASS FreeLayout

JB_DEFINE_WRAPPER_CLASS(
    "com/itoa/FreeLayout"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(Landroid/content/Context;)V"
    )
)

FreeLayout::FreeLayout(android::PContext context):
    ViewGroup(JB_NEW(Constructor,context))
{
}

FreeLayout::FreeLayout(const jni::LObject& object):
    ViewGroup(object)
{
}

FreeLayout::FreeLayout(const jni::LObject& object,jfieldID instanceField):
    ViewGroup(object,instanceField)
{
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// SubviewLayout

#define JB_CURRENT_CLASS SubviewLayout

JB_DEFINE_WRAPPER_CLASS(
    "com/itoa/SubviewLayout"
    ,
    NoFields
    ,
    Methods
    (
        Constructor,
        "<init>",
        "(Landroid/view/View;Landroid/content/Context;)V"
    )
)

SubviewLayout::SubviewLayout(android::PView superview,android::PContext context):
    FreeLayout(JB_NEW(Constructor,superview,context))
{
}

SubviewLayout::SubviewLayout(const jni::LObject& object):
    FreeLayout(object)
{
}

void SubviewLayout::AddView(android::PView view,int32_t index) {
    if (index!=-1) {
        index+=1;
    }
    FreeLayout::AddView(view,index);
}

void SubviewLayout::RemoveViewAt(int32_t index) {
    FreeLayout::RemoveViewAt(index+1);
}

#undef JB_CURRENT_CLASS

/////////////////////////////////////////////////

END_NAMESPACE(itoa)

