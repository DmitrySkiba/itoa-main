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

#include "AndroidWidget.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////// TextView

#define JB_CURRENT_CLASS TextView

JB_DEFINE_WRAPPER_CLASS(
    "android/widget/TextView"
    ,
    NoFields
    ,
    Methods
    (
        GetText,
        "getText",
        "()Ljava/lang/CharSequence;"
    )
    (
        SetText,
        "setText",
        "(Ljava/lang/CharSequence;)V"
    )
    (
        GetGravity,
        "getGravity",
        "()I"
    )
    (
        SetGravity,
        "setGravity",
        "(I)V"
    )
    (
        SetTextColor,
        "setTextColor",
        "(I)V"
    )
)

TextView::TextView(const jni::LObject& object):
    View(object)
{
}

TextView::TextView(const jni::LObject& object,jfieldID instanceField):
    View(object,instanceField)
{
}

java::PString TextView::GetText() const {
    return java::PCharSequence::Wrap(JB_CALL_THIS(ObjectMethod,GetText))->ToString();
}

void TextView::SetText(java::PString text) {
    JB_CALL_THIS(VoidMethod,SetText,text);    
}

int32_t TextView::GetGravity() const {
    return JB_CALL_THIS(IntMethod,GetGravity);
}

void TextView::SetGravity(int32_t gravity) {
    JB_CALL_THIS(VoidMethod,SetGravity,gravity);    
}

void TextView::SetTextColor(int32_t color) {
    JB_CALL_THIS(VoidMethod,SetTextColor,color);    
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////// Button

#define JB_CURRENT_CLASS Button

JB_DEFINE_WRAPPER_CLASS(
    "android/widget/Button"
    ,
    NoFields
    ,
    NoMethods
)

Button::Button(const jni::LObject& object):
    TextView(object)
{
}

Button::Button(const jni::LObject& object,jfieldID instanceField):
    TextView(object,instanceField)
{
}

#undef JB_CURRENT_CLASS

/////////////////////////////////////////////////

END_NAMESPACE(android)

