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

#ifndef _GRAPHICSPRIMITIVES_INCLUDED_
#define _GRAPHICSPRIMITIVES_INCLUDED_

#include <inttypes.h>

///////////////////////////////////////////////// GraphicsSize

class GraphicsSize {
public:
    GraphicsSize():
        m_width(0),m_height(0)
    {
    }
    GraphicsSize(int32_t width,int32_t height):
        m_width(width),m_height(height)
    {
    }
    int32_t GetWidth() const {
        return m_width;
    }
    int32_t GetHeight() const {
        return m_height;
    }
    void SetWidth(int32_t width) {
        m_width=width;
    }
    void SetHeight(int32_t height) {
        m_height=height;
    }
    void Set(int32_t width,int32_t height) {
        m_width=width;
        m_height=height;
    }
private:
    int32_t m_width;
    int32_t m_height;
};

///////////////////////////////////////////////// GraphicsRect

class GraphicsRect {
public:
    GraphicsRect():
        left(0),right(0),top(0),bottom(0)
    {
    }
    GraphicsRect(int32_t _left,int32_t _top,int32_t _right,int32_t _bottom):
        left(_left),top(_top),
        right(_right),bottom(_bottom)
    {
    }
public:
    int32_t GetLeft() const {
        return left;
    }
    int32_t GetTop() const {
        return top;
    }
    int32_t GetRight() const {
        return right;
    }
    int32_t GetBottom() const {
        return bottom;
    }

    int32_t GetX() const {
        return left;
    }
    int32_t GetY() const {
        return top;
    }
    
    int32_t GetWidth() const {
        return right-left;
    }
    int32_t GetHeight() const {
        return bottom-top;
    }
    
    static GraphicsRect MakeLTRB(int32_t left,int32_t top,int32_t right,int32_t bottom) {
        return GraphicsRect(left,top,right,bottom);
    }
    static GraphicsRect MakeXYWH(int32_t x,int32_t y,int32_t width,int32_t height) {
        return GraphicsRect(x,y,x+width,y+height);
    }
public:
    int32_t left;
    int32_t right;
    int32_t top;
    int32_t bottom;
};

/////////////////////////////////////////////////

#endif // _GRAPHICSPRIMITIVES_INCLUDED_

