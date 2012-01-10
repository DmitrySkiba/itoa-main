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

#include "ItoaLiveCast.h"

BEGIN_NAMESPACE(itoa)

///////////////////////////////////////////////// ILiveClass

#define JB_CURRENT_CLASS ILiveClass

JB_DEFINE_WRAPPER_CLASS(
    "com/itoa/ILiveClass"
    ,
    NoFields
    ,
    Methods
    (
        GetJBInstance,
        "getJBInstance",
        "()I"
    )
)

java::Object* ILiveClass::GetInstance(jobject object) {
    int instance=JB_CALL(IntMethod,jni::LObject::Wrap(object),GetJBInstance);
    return reinterpret_cast<java::Object*>(instance);    
}

#undef JB_CURRENT_CLASS

/////////////////////////////////////////////////

END_NAMESPACE(itoa)
