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

#ifndef _ANDROIDGRAPHICS_INCLUDED_
#define _ANDROIDGRAPHICS_INCLUDED_

#include "CommonIncludes.h"
#include "GraphicsPrimitives.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////// Matrix

class Matrix: public java::Object {
    JB_WRAPPER_CLASS(Matrix);
    class Instance;
public:
    Matrix();
    Matrix(const jni::LObject& object);
    const float* GetValues() const;
    void SetValues(const float* values);
private:
    Instance* GetInstance() const;
};

typedef java::ObjectPointer<Matrix> PMatrix;

///////////////////////////////////////////////// Rect

class Rect: public java::Object {
    JB_WRAPPER_CLASS(Rect);
public:
    Rect();
    explicit Rect(const GraphicsRect& rect);
    explicit Rect(const jni::LObject& object);
    GraphicsRect GetRect() const;
    void SetRect(const GraphicsRect& rect);
};

typedef java::ObjectPointer<Rect> PRect;

///////////////////////////////////////////////// PaintStyle

struct PaintStyle {
    enum ID {
        FILL,
        STROKE,
        FILL_AND_STROKE,
    };
};

typedef PaintStyle::ID PaintStyleID;

///////////////////////////////////////////////// Paint

class Paint: public java::Object {
    JB_WRAPPER_CLASS(Paint);
public:
    Paint();
    explicit Paint(const jni::LObject& object);
    PaintStyleID GetStyle() const;
    void SetStyle(PaintStyleID style);
    int32_t GetColor() const;
    void SetColor(int32_t color);
};

typedef java::ObjectPointer<Paint> PPaint;

///////////////////////////////////////////////// Drawable

class Drawable: public java::Object {
public:
    Drawable(const jni::LObject& object);
protected:
    Drawable(const jni::LObject&,jfieldID);
};

typedef java::ObjectPointer<Drawable> PDrawable;

///////////////////////////////////////////////// BGColorDrawable

class BGColorDrawable: public Drawable {
    JB_WRAPPER_CLASS(BGColorDrawable);
public:
    BGColorDrawable(int32_t color);
    BGColorDrawable(const jni::LObject& object);
};

typedef java::ObjectPointer<BGColorDrawable> PBGColorDrawable;

///////////////////////////////////////////////// Canvas

class Canvas: public java::Object {
    JB_WRAPPER_CLASS(Canvas);
public:
    explicit Canvas(const jni::LObject& object);
    void DrawRect(
        float left,float top,float right,float bottom,
        PPaint paint);
};

typedef java::ObjectPointer<Canvas> PCanvas;

/////////////////////////////////////////////////

END_NAMESPACE(android)

#endif // _ANDROIDGRAPHICS_INCLUDED_

