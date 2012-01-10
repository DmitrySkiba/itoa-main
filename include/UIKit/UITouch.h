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

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

/*
 * UITouchPhase
 */

typedef enum {
    UITouchPhaseBegan,
    UITouchPhaseMoved,
    UITouchPhaseStationary,
    UITouchPhaseEnded,
    UITouchPhaseCancelled,
    UITouchPhaseInvalid=-1
} UITouchPhase;

/*
 * UITouch
 */

@class UIWindow, UIView;

@interface UITouch: NSObject {
    @public void* m_impl;
}

@property(nonatomic,readonly) NSTimeInterval timestamp;
@property(nonatomic,readonly) UITouchPhase phase;
@property(nonatomic,readonly) NSUInteger tapCount;

@property(nonatomic,readonly) UIWindow* window;
@property(nonatomic,readonly) UIView* view;

-(CGPoint)locationInView:(UIView*)view;
-(CGPoint)previousLocationInView:(UIView*)view;

@end
