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

#include <CoreGraphics/CGAffineTransform.h>
#include <math.h>
#include <string.h>
#include <dropins/countof.h>

///////////////////////////////////////////////////////////////////// CGAffineTransform

const CGAffineTransform CGAffineTransformIdentity={1,0,0,1,0,0};

CGAffineTransform CGAffineTransformMakeTranslation(CGFloat tx,CGFloat ty) {
    CGAffineTransform result={1,0,0,1,tx,ty};
    return result;
}

CGAffineTransform CGAffineTransformMakeScale(CGFloat sx,CGFloat sy) {
    CGAffineTransform result={sx,0,0,sy,0,0};
    return result;
}

CGAffineTransform CGAffineTransformMakeRotation(CGFloat radians) {
    CGFloat sinus=sinf(radians);
    CGFloat cosinus=cosf(radians);
    CGAffineTransform result={cosinus,sinus,-sinus,cosinus,0,0};
    return result;
}

bool CGAffineTransformIsIdentity(CGAffineTransform T) {
    return !memcmp(&T,&CGAffineTransformIdentity,sizeof(T));
}

CGAffineTransform CGAffineTransformTranslate(CGAffineTransform T,CGFloat tx,CGFloat ty) {
    return CGAffineTransformConcat(T,CGAffineTransformMakeTranslation(tx,ty));
}

CGAffineTransform CGAffineTransformScale(CGAffineTransform T,CGFloat sx,CGFloat sy) {
    return CGAffineTransformConcat(T,CGAffineTransformMakeScale(sx,sy));
}

CGAffineTransform CGAffineTransformRotate(CGAffineTransform T,CGFloat angle) {
    return CGAffineTransformConcat(T,CGAffineTransformMakeRotation(angle));
}

CGAffineTransform CGAffineTransformInvert(CGAffineTransform T) {
    CGFloat determinant=(T.a*T.d-T.c*T.b);
    if (determinant==0) {
        return T;
    } else {
        CGAffineTransform result={
            T.d/determinant,
            -T.b/determinant,
            -T.c/determinant,
            T.a/determinant,
            (-T.d*T.tx+T.c*T.ty)/determinant,
            (T.b*T.tx-T.a*T.ty)/determinant
        };
        return result;
    }
}

/*
CGAffineTransform OptimizedInvert(CGAffineTransform T) {
    double determinant=(double)T.a*T.d-(double)T.c*T.b;
    if (determinant!=0) {
        double a=T.d/determinant;
        double b=-T.b/determinant;
        double c=-T.c/determinant;
        double d=T.a/determinant;
        double tx=a*T.tx+c*T.ty;
        double ty=b*T.tx+d*T.ty;
        T.a=a;
        T.b=b;
        T.c=c;
        T.d=d;
        T.tx=-tx;
        T.ty=-ty;
    }
    return T;
}*/

CGAffineTransform CGAffineTransformConcat(CGAffineTransform T1,CGAffineTransform T2) {
    CGAffineTransform result={
        T1.a*T2.a+T1.b*T2.c,
        T1.a*T2.b+T1.b*T2.d,
        T1.c*T2.a+T1.d*T2.c,
        T1.c*T2.b+T1.d*T2.d,
        T1.tx*T2.a+T1.ty*T2.c+T2.tx,
        T1.tx*T2.b+T1.ty*T2.d+T2.ty
    };
    return result;
}

CGPoint CGPointApplyAffineTransform(CGPoint point,CGAffineTransform T) {
    CGPoint result={
        T.a*point.x+T.c*point.y+T.tx,
        T.b*point.x+T.d*point.y+T.ty
    };
    return result;
}

CGSize CGSizeApplyAffineTransform(CGSize size,CGAffineTransform T) {
    CGSize result={
        T.a*size.width+T.c*size.height+T.tx,
        T.b*size.width+T.d*size.height+T.ty
    };
    return result;
}

CGRect CGRectApplyAffineTransform(CGRect rect,CGAffineTransform transform) {
    if (fabs(rect.origin.x)==CGFLOAT_MAX ||
        fabs(rect.origin.y)==CGFLOAT_MAX)
    {
        return rect;
    }
    CGPoint points[4];
    points[0]=rect.origin;
    points[1]=CGPointMake(rect.origin.x,rect.origin.y+rect.size.height);
    points[2]=CGPointMake(rect.origin.x+rect.size.width,rect.origin.y+rect.size.height);
    points[3]=CGPointMake(rect.origin.x+rect.size.width,rect.origin.y);
    for (size_t i=0;i!=countof(points);++i) {
        points[i]=CGPointApplyAffineTransform(points[i],transform);
    }
    CGPoint topLeft=points[0];
    CGPoint rightBottom=points[0];
    for (size_t i=0;i!=countof(points);++i) {
        if (topLeft.x>points[i].x) {
            topLeft.x=points[i].x;
        }
        if (rightBottom.x<points[i].x) {
            rightBottom.x=points[i].x;
        }
        if (topLeft.y>points[i].y) {
            topLeft.y=points[i].y;
        }
        if (rightBottom.y<points[i].y) {
            rightBottom.y=points[i].y;
        }
    }
    rect.origin=topLeft;
    rect.size.width=rightBottom.x-topLeft.x;
    rect.size.height=rightBottom.y-topLeft.y;
    return rect;
}

