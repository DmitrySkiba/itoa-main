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

#ifndef _ITOALIVECAST_INCLUDED_
#define _ITOALIVECAST_INCLUDED_

#include "CommonIncludes.h"

BEGIN_NAMESPACE(itoa)

///////////////////////////////////////////////// ILiveClass

class ILiveClass {
    JB_WRAPPER_CLASS(ILiveClass);
public:
    static java::Object* GetInstance(jobject object);
};

///////////////////////////////////////////////// LiveClassBase

template <class BaseType>
class LiveClassBase: public BaseType {
protected:
    LiveClassBase(const jni::LObject& object,jfieldID instanceField):
        BaseType(object,instanceField)
    {
    }
    static java::Object* GetInstanceBase(jobject object,jfieldID) {
        return itoa::ILiveClass::GetInstance(object);
    }
};

///////////////////////////////////////////////// live casts

template <class OtherObjectType>
inline bool IsLiveInstanceOf(const jni::AbstractObject& object) {
    if (!object.GetJObject()) {
        return false;
    }
    jni::LObject objectClass=jni::GetObjectClass(object);
    jni::LObject otherObjectClass=OtherObjectType::GetTypeClass();
    jni::LObject liveClass=ILiveClass::GetTypeClass();
    if (jni::IsAssignableFrom(objectClass,liveClass) &&
        jni::IsAssignableFrom(otherObjectClass,liveClass))
    {
        do {
            objectClass=jni::GetSuperclass(objectClass);
        } while (jni::IsAssignableFrom(objectClass,liveClass));
        do {
            otherObjectClass=jni::GetSuperclass(otherObjectClass);
        } while (jni::IsAssignableFrom(otherObjectClass,liveClass));
    }
    return jni::IsAssignableFrom(objectClass,otherObjectClass);
}

template <class OtherObjectType>
inline java::ObjectPointer<OtherObjectType> LiveCast(const jni::AbstractObject& object) {
    if (!IsLiveInstanceOf<OtherObjectType>(object)) {
        throw std::bad_cast();
    }
    return java::ObjectPointer<OtherObjectType>::Wrap(object.GetJObject());
}

/////////////////////////////////////////////////

END_NAMESPACE(itoa)

#endif // _ITOALIVECAST_INCLUDED_

