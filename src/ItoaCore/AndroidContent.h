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

#ifndef _ANDROIDCONTENT_INCLUDED_
#define _ANDROIDCONTENT_INCLUDED_

#include "CommonIncludes.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////// Context

class Context: public java::Object {
    JB_WRAPPER_CLASS(Context);
public:
    explicit Context(const jni::LObject& object);
protected:
    Context(const jni::LObject& object,jfieldID instanceField);    
};

typedef java::ObjectPointer<Context> PContext;

/////////////////////////////////////////////////

END_NAMESPACE(android)

#endif // _ANDROIDCONTENT_INCLUDED_

