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
import android.graphics.Canvas;
import android.graphics.Rect;
import android.view.MotionEvent;
import android.widget.TextView;

public class LiveTextView extends TextView {

    public LiveTextView(Context context) {
        super(context);
    }
    
    @Override
    public boolean dispatchTouchEvent(MotionEvent event) {
        if (!FreeLayout.preDispatchTouchEvent(this,event)) {
            return false;
        }
        return super.dispatchTouchEvent(event);
    }
    
    @Override
    public void getHitRect(Rect hitRect) {
        super.getHitRect(hitRect);
        FreeLayout.postGetHitRect(this,hitRect);
    }
    
    @Override
    public void invalidate(Rect dirty) {
        dirty=FreeLayout.preInvalidate(this,dirty);
        super.invalidate(dirty);
    }
    
    @Override
    public void invalidate() {
        FreeLayout.invalidate(this);
    }
    
    @Override
    public void invalidate(int left,int top,int right,int bottom) {
        FreeLayout.invalidate(this,left,top,right,bottom);
    }
    
//    public void onDraw(Canvas canvas) {
//        nativeOnDraw(canvas);
//    }
    
    /////////////////////////////////// implementation
    
    private native void nativeOnDraw(Canvas canvas);
    
    /////////////////////////////////// JNIpp

    protected native void finalize();
    @SuppressWarnings("unused")
    private int nativeInstance;
}
