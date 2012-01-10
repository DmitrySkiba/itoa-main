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

import android.os.Handler;
import android.os.Message;

public class LiveHandler extends Handler {
    
    public void handleMessage(Message message) {
        nativeHandleMessage(message);
    }

    private native void nativeHandleMessage(Message message);
    
    /////////////////////////////////// JNIpp

    protected native void finalize();
    @SuppressWarnings("unused")
    private int nativeInstance;
}
