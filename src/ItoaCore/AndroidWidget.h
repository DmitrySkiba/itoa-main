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

#ifndef _ANDROIDWIDGET_INCLUDED_
#define _ANDROIDWIDGET_INCLUDED_

#include "CommonIncludes.h"
#include "AndroidView.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////// TextView

class TextView: public View {
    JB_WRAPPER_CLASS(TextView);
public:
    TextView(const jni::LObject& object);
    java::PString GetText() const;
    int32_t GetGravity() const;
    void SetText(java::PString text);
    void SetGravity(int32_t gravity);
    void SetTextColor(int32_t color);
protected:
    TextView(const jni::LObject&,jfieldID);
};

typedef java::ObjectPointer<TextView> PTextView;

///////////////////////////////////////////////// Button

class Button: public TextView {
    JB_WRAPPER_CLASS(Button);
public:
    Button(const jni::LObject& object);
protected:
    Button(const jni::LObject&,jfieldID);
};

typedef java::ObjectPointer<Button> PButton;

/////////////////////////////////////////////////

END_NAMESPACE(android)

#endif // _ANDROIDWIDGET_INCLUDED_

