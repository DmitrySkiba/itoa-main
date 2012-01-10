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

#include <CoreGraphics/CGContext.h>
#include "CGInternal.h"
#include "CGContextInternal.h"

///////////////////////////////////////////////////////////////////// CGContext

typedef struct _CGContext {
    CFRuntimeBase _runtime;
    android::PCanvas canvas;
    android::PPaint paint;
    CGColorRef fillColor;
} CGContext;

OBJECT_COMMON_IMPLEMENTATION(CGContext);

///////////////////////////////////////////////// CGContext class

static void _CGContextFinalize(CFTypeRef contextRef) {
    CGContext* context=_CGContextFromTypeRef(contextRef);
    context->~CGContext();
}

static Boolean _CGContextEqual(CFTypeRef contextRef1,CFTypeRef contextRef2) {
    // TODO
    return true;
}

static CFStringRef _CGContextCopyDescription(CFTypeRef contextRef,CFDictionaryRef formatOptions) {
    CGContext* context=_CGContextFromTypeRef(contextRef);
    CFAllocatorRef allocator=CFGetAllocator(contextRef);
    CFMutableStringRef description=CFStringCreateMutable(allocator,0);
    CFStringAppendFormat(description,NULL,CFSTR("<CGContext %p> "),context);
    return description;
}

static CFStringRef _CGContextCopyDebugDescription(CFTypeRef contextRef) {
    return _CGContextCopyDescription(contextRef,NULL);
}

static CFHashCode _CGContextHash(CFTypeRef contextRef) {
    // TODO
    return (CFHashCode)contextRef;
}

OBJECT_CLASS_SPECIFICATION(CGContext)={
    0,
    "CGContext",
    NULL, // init
    NULL, // copy
    _CGContextFinalize,
    _CGContextEqual,
    _CGContextHash,
    _CGContextCopyDescription,
    _CGContextCopyDebugDescription
};

///////////////////////////////////////////////// implementation

// CG_EXPORT CGContextRef CGContextCreate() {
//     CGContext* context=(CGContext*)_CGNewObject(
//         CGContextGetTypeID(),
//         sizeof(CGContext)-sizeof(CFRuntimeBase));
//     if (context==NULL) {
//         return NULL;
//     }
//     return context;
// }

CG_EXPORT CGContextRef CGContextCreateFromCanvas(android::PCanvas canvas) {
    CGContext* context=(CGContext*)_CGNewObject(
        CGContextGetTypeID(),
        sizeof(CGContext)-sizeof(CFRuntimeBase));
    if (context==NULL) {
        return NULL;
    }
    new (context) CGContext();
    context->canvas=canvas;
    context->paint=new android::Paint();
    return context;
}

CG_EXPORT void CGContextSetFillColorWithColor(CGContextRef context,CGColorRef color) {
    if (!CGColorEqualToColor(context->fillColor,color)) {
        CGColorRelease(context->fillColor);
        context->fillColor=CGColorRetain(color);
    }
}

CG_EXPORT void CGContextSetRGBFillColor(CGContextRef context,
    CGFloat red,CGFloat green,CGFloat blue,CGFloat alpha)
{
    CGFloat components[]={red,green,blue,alpha};
    CGColorSpaceRef deviceRGB=CGColorSpaceCreateDeviceRGB();
    if (!deviceRGB) {
        return;
    }
    if (!CGColorEqualToComponents(context->fillColor,deviceRGB,components)) {
        CGColorRef color=CGColorCreate(deviceRGB,components);
        CGContextSetFillColorWithColor(context,color);
        CGColorRelease(color);
    }
    CGColorSpaceRelease(deviceRGB);
}

CG_EXPORT void CGContextSetGrayFillColor(CGContextRef context,
    CGFloat gray,CGFloat alpha)
{
    CGFloat components[]={gray,alpha};
    CGColorSpaceRef deviceGray=CGColorSpaceCreateDeviceGray();
    if (!deviceGray) {
        return;
    }
    if (!CGColorEqualToComponents(context->fillColor,deviceGray,components)) {
        CGColorRef color=CGColorCreate(deviceGray,components);
        CGContextSetFillColorWithColor(context,color);
        CGColorRelease(color);
    }
    CGColorSpaceRelease(deviceGray);
}

CG_EXPORT void CGContextFillRect(CGContextRef context,CGRect rect) {
    context->paint->SetColor(CGColorGetARGB(context->fillColor));
    context->paint->SetStyle(android::PaintStyle::FILL);
    context->canvas->DrawRect(
        rect.origin.x,
        rect.origin.y,
        rect.origin.x+rect.size.width,
        rect.origin.y+rect.size.height,
        context->paint);
}
