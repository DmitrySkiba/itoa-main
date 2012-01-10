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
import android.view.MotionEvent;

public class LiveDesktopLayout extends FreeLayout {
    
    public LiveDesktopLayout(Context context) {
        super(context);
    }
    
    public boolean dispatchTouchEvent(MotionEvent event) {
        if (m_insideDispatchTouchEvent) {
            return super.dispatchTouchEvent(event);
        }
        try {
            m_insideDispatchTouchEvent=true;
            return nativeDispatchTouchEvent(event);
        }
        finally {
            m_insideDispatchTouchEvent=false;
        }
    }
    
    /////////////////////////////////// implementation
    
    private native boolean nativeDispatchTouchEvent(MotionEvent event);
    
    private boolean m_insideDispatchTouchEvent;
    
    /////////////////////////////////// JNIpp

    protected native void finalize();
    @SuppressWarnings("unused")
    private int nativeInstance;
}
