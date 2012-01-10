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

#ifndef _ITOAWIDGET_INCLUDED_
#define _ITOAWIDGET_INCLUDED_

#include "AndroidView.h"

BEGIN_NAMESPACE(itoa)

///////////////////////////////////////////////// FreeLayoutParams

class FreeLayoutParams: public android::ViewLayoutParams {
    JB_WRAPPER_CLASS(FreeLayoutParams);
public:
    FreeLayoutParams();
    FreeLayoutParams(int32_t width,int32_t height,android::PMatrix matrix=0);
    FreeLayoutParams(const jni::LObject& object);
    android::PMatrix GetMatrix() const;
    void SetMatrix(android::PMatrix matrix);
};

typedef java::ObjectPointer<FreeLayoutParams> PFreeLayoutParams;

///////////////////////////////////////////////// FreeLayout

class FreeLayout: public android::ViewGroup {
    JB_WRAPPER_CLASS(FreeLayout);
public:
    FreeLayout(android::PContext context);
    FreeLayout(const jni::LObject& object);
protected:
    FreeLayout(const jni::LObject&,jfieldID);
};

typedef java::ObjectPointer<FreeLayout> PFreeLayout;

///////////////////////////////////////////////// SubviewLayout

class SubviewLayout: public FreeLayout {
    JB_WRAPPER_CLASS(SubviewLayout);
public:
    using FreeLayout::AddView;
public:
    SubviewLayout(android::PView superview,android::PContext context);
    SubviewLayout(const jni::LObject& object);
    virtual void AddView(android::PView view,int32_t index);
    virtual void RemoveViewAt(int32_t index);
};

typedef java::ObjectPointer<SubviewLayout> PSubviewLayout;

/////////////////////////////////////////////////

END_NAMESPACE(itoa)

#endif // _ITOAWIDGET_INCLUDED_

