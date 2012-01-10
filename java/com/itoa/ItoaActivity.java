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

import java.lang.reflect.Field;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

public class ItoaActivity extends Activity {
    
    public void onCreate(Bundle savedState) {
        System.loadLibrary("macemu");
        System.loadLibrary("jnipp");
        System.loadLibrary("objc");
        System.loadLibrary("cf");
        System.loadLibrary("core");
        System.loadLibrary("cg");
        System.loadLibrary("foundation");
        System.loadLibrary("uikit");
        System.loadLibrary("application");
        nativeOnCreate(savedState);
        super.onCreate(savedState);
    }

    public void onPause() {
        nativeOnPause();
        super.onPause();
    }
    
    private void handleActivityMessages(boolean handle) throws Exception {
        Field mainThreadField=Activity.class.getDeclaredField("mMainThread");
        mainThreadField.setAccessible(true);
        Object activityThread=mainThreadField.get(this);
        
        Field hField=activityThread.getClass().getDeclaredField("mH");
        hField.setAccessible(true);
        Handler handler=(Handler)hField.get(activityThread);
        
        Field callbackField=Handler.class.getDeclaredField("mCallback");
        callbackField.setAccessible(true);
        if (handle) {
            callbackField.set(handler,new Handler.Callback() {
                public boolean handleMessage(Message message) {
                    return nativeHandleActivityMessage(message);
                }
            });
        } else {
            callbackField.set(handler,null);
        }
    }
    
    private native void nativeOnCreate(Bundle savedState);
    private native void nativeOnPause();
    private native boolean nativeHandleActivityMessage(Message message);
    
    /////////////////////////////////// JNIpp

    protected native void finalize();
    @SuppressWarnings("unused")
    private int nativeInstance;
}
