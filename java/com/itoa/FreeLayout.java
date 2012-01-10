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

package com.itoa;

import android.content.Context;
import android.graphics.Matrix;
import android.graphics.Rect;
import android.graphics.RectF;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.view.animation.Transformation;

public class FreeLayout extends ViewGroup {
    
    public FreeLayout(Context context) {
        super(context);
        setStaticTransformationsEnabled(true);
        setClipChildren(false);
    }
    
    public static Matrix getViewMatrix(View view) {
        ViewGroup.LayoutParams layoutParams=view.getLayoutParams();
        if (layoutParams instanceof LayoutParams) {
            return ((LayoutParams)layoutParams).matrix;
        } else {
            return null;
        }
    }
    
    public static void transformFrame(Rect rect,Matrix m) {
        m_tempRectF.set(rect);
        m_tempRectF.sort();
        m.mapRect(m_tempRectF);
        m_tempRectF.roundOut(rect);
    }
    
    public static Rect preInvalidate(View view,Rect dirty) {
        Matrix m=getViewMatrix(view);
        if (m!=null) {
            if (dirty!=m_tempRect) {
                m_tempRect.set(dirty);
                dirty=m_tempRect;
            }
            transformFrame(m_tempRect,m);
        }
        return dirty;
    }
    public static void invalidate(View view) {
        m_tempRect.set(
            view.getScrollX(),
            view.getScrollY(),
            view.getScrollX()+view.getWidth(),
            view.getScrollY()+view.getHeight());
        view.invalidate(m_tempRect);
    }
    public static void invalidate(View view,int left,int top,int right,int bottom) {
        m_tempRect.set(left,top,right,bottom);
        view.invalidate(m_tempRect);
    }
    
    public static boolean preDispatchTouchEvent(View view,MotionEvent event) {
        Matrix m=getViewMatrix(view);
        if (m!=null) {
            Matrix mi=new Matrix();
            if (m.invert(mi)) {
                float[] points=new float[]{event.getX(),event.getY()};
                mi.mapPoints(points);
                if (event.getAction()==MotionEvent.ACTION_DOWN && (
                    points[0]<view.getLeft() || points[0]>=view.getRight() ||
                    points[1]<view.getTop() || points[1]>=view.getBottom()))
                {
                    return false;
                }
                event.setLocation(points[0],points[1]);
            }
        }
        return true;
    }
    
    public static void postGetHitRect(View view,Rect hitRect) {
        Matrix m=getViewMatrix(view);
        if (m!=null) {
            transformFrame(hitRect,m);
        }
    }

    ///////////////////////////////////////////// LayoutParams

    public static class LayoutParams extends ViewGroup.LayoutParams {
        public LayoutParams(int width,int height,Matrix matrix) {
            super(width,height);
            this.matrix=matrix;
        }
        public LayoutParams(int width,int height) {
            this(width,height,null);
        }
        public LayoutParams(ViewGroup.LayoutParams source) {
            super(source);
        }

        public Matrix matrix;
    }
    
    ///////////////////////////////////////////// implementation

    @Override
    protected void onMeasure(int widthMeasureSpec,int heightMeasureSpec) {
        measureChildren(widthMeasureSpec,heightMeasureSpec);
        setMeasuredDimension(
            resolveSize(getSuggestedMinimumWidth(),widthMeasureSpec),
            resolveSize(getSuggestedMinimumWidth(),heightMeasureSpec));
    }

    @Override
    protected ViewGroup.LayoutParams generateDefaultLayoutParams() {
        return new LayoutParams(100,100);
    }

    @Override
    protected void onLayout(boolean changed,int l,int t,int r,int b) {
        int count=getChildCount();
        for (int i=0;i<count;i++) {
            View child=getChildAt(i);
            if (child.getVisibility()!=GONE) {
                child.layout(
                    0,
                    0,
                    child.getMeasuredWidth(),
                    child.getMeasuredHeight());
            }
        }
    }

    @Override
    protected boolean checkLayoutParams(ViewGroup.LayoutParams p) {
        return p instanceof LayoutParams;
    }

    @Override
    protected ViewGroup.LayoutParams generateLayoutParams(ViewGroup.LayoutParams p) {
        return new LayoutParams(p);
    }
    
    @Override
    protected boolean getChildStaticTransformation(View child,Transformation t) {
        Matrix m=getViewMatrix(child);
        if (m!=null) {
            t.getMatrix().set(m);
            t.setTransformationType(Transformation.TYPE_MATRIX);
            return true;
        } else {
            return false;
        }
    }
    
    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        if (!preDispatchTouchEvent(this,ev)) {
            return false;
        }
        return super.dispatchTouchEvent(ev);
    }
    
    @Override
    public ViewParent invalidateChildInParent(final int[] location,final Rect dirty) {
        Matrix m=getViewMatrix(this);
        if (m==null) {
            return super.invalidateChildInParent(location,dirty);
        }
        m_tempICPRect.set(dirty);
        ViewParent result=super.invalidateChildInParent(location,m_tempICPRect);
        dirty.union(m_tempICPRect);
        transformFrame(dirty,m);
        return result;
    }
    
    @Override
    public void getHitRect(Rect hitRect) {
        super.getHitRect(hitRect);
        postGetHitRect(this,hitRect);
    }
    
    @Override
    public void invalidate(Rect dirty) {
        dirty=preInvalidate(this,dirty);
        super.invalidate(dirty);
    }
    
    @Override
    public void invalidate() {
        invalidate(this);
    }
    
    @Override
    public void invalidate(int left,int top,int right,int bottom) {
        invalidate(this,left,top,right,bottom);
    }
    
    ///////////////////////////////////////////// data

    private static Rect m_tempRect=new Rect();
    private static Rect m_tempICPRect=new Rect();
    private static RectF m_tempRectF=new RectF();
}
