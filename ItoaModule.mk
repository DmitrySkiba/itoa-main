#
# Copyright (C) 2011 Dmitry Skiba
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

MODULE_PATH := $(call my-dir)

$(call itoa-copy-files,\
    $(MODULE_PATH)/app,app)

$(call itoa-copy-files,\
    $(MODULE_PATH)/java,app/src)

#================================================ ItoaCore

include $(CLEAR_VARS)

MODULE_NAME := core

$(eval $(call itoa-copy-file,\
    $(MODULE_PATH)/LICENSE.txt,lib$(MODULE_NAME).LICENSE.txt))

MODULE_CFLAGS := \
    -I$(MODULE_PATH)/include \
    -I$(MODULE_PATH)/src \

MODULE_SRC_FILES += \
    src/ItoaCore/Core.cpp \
    src/ItoaCore/AndroidOS.cpp \
    src/ItoaCore/AndroidGraphics.cpp \
    src/ItoaCore/AndroidView.cpp \
    src/ItoaCore/AndroidContent.cpp \
    src/ItoaCore/AndroidWidget.cpp \
    src/ItoaCore/ItoaWidget.cpp \
    src/ItoaCore/ItoaActivity.cpp \
    src/ItoaCore/ItoaLive.cpp \
    src/ItoaCore/ItoaLiveCast.cpp \
    \
    src/ItoaCore/misc/RunLoopPort.cpp \
    src/ItoaCore/misc/sofcn.c \

MODULE_LDLIBS := -llog -ldl
MODULE_SHARED_LIBRARIES := jnipp objc cf

include $(BUILD_SHARED_LIBRARY)

#================================================ CoreGraphics

include $(CLEAR_VARS)

MODULE_NAME := cg

$(call itoa-sysroot-copy-files,\
    $(MODULE_PATH)/include/CoreGraphics,usr/include/CoreGraphics)

$(eval $(call itoa-copy-file,\
    $(MODULE_PATH)/LICENSE.txt,lib$(MODULE_NAME).LICENSE.txt))

MODULE_CFLAGS := \
    -I$(MODULE_PATH)/include \
    -I$(MODULE_PATH)/src \
    \
    -std=gnu99 -Wcast-qual \

MODULE_SRC_FILES += \
    src/CoreGraphics/CGInternal.c \
    src/CoreGraphics/CGGeometry.c \
    src/CoreGraphics/CGColor.c \
    src/CoreGraphics/CGColorSpace.c \
    src/CoreGraphics/CGContext.cpp \
    src/CoreGraphics/CGAffineTransform.c \
    
MODULE_LDLIBS := -llog -ldl

MODULE_SHARED_LIBRARIES := jnipp macemu cf core

include $(BUILD_SHARED_LIBRARY)

#================================================ UIKit & QuartzCore

include $(CLEAR_VARS)

MODULE_NAME := uikit

$(call itoa-sysroot-copy-files,\
    $(MODULE_PATH)/include/UIKit,usr/include/UIKit)

$(call itoa-sysroot-copy-files,\
    $(MODULE_PATH)/include/QuartzCore,usr/include/QuartzCore)

$(eval $(call itoa-copy-file,\
    $(MODULE_PATH)/LICENSE.txt,lib$(MODULE_NAME).LICENSE.txt))

#MODULE_CFLAGS += \
#    -I$(MODULE_PATH)/include \
#    -I$(MODULE_PATH)/src \
#    -I$(MODULE_PATH)/src/UIKit/ \
#    -I$(MODULE_PATH)/src/UIKit/Utils \
#   
#MODULE_SRC_FILES +=  \
#    src/UIKit/Layer.mm \
#    \
#    src/UIKit/UIScreen.mm \
#    src/UIKit/UIColor.m \
#    src/UIKit/Application.mm \
#    src/UIKit/Responder.mm \
#    src/UIKit/View.mm \
#    src/UIKit/ViewController.mm \
#    src/UIKit/Window.mm \
#    src/UIKit/Event.mm \
#    src/UIKit/Touch.mm \
#    src/UIKit/Control.mm \
#    src/UIKit/Button.mm \
#    src/UIKit/Label.mm \
#    \
#    src/UIKit/Utils/ImplBase.mm \
#    src/UIKit/Utils/Misc.mm \
#    src/UIKit/Utils/RLPerformer.m \
#    src/UIKit/Utils/RunDelayed.cpp \
#
#MODULE_LDLIBS := -llog
#MODULE_SHARED_LIBRARIES := macemu jnipp objc cf cg foundation core
#
#include $(BUILD_SHARED_LIBRARY)

