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
#import <UIKit/UIView.h>
#import <UIKit/UIEvent.h>
#import <UIKit/UITouch.h>

/*
 * UIControlState
 */

enum {
    UIControlStateNormal            =0x00000000,                      
    UIControlStateHighlighted       =0x00000001,
    UIControlStateDisabled          =0x00000002,
    UIControlStateSelected          =0x00000004,
    UIControlStateApplication       =0x00FF0000,
    UIControlStateReserved          =0xFF000000
};
typedef NSUInteger UIControlState;

/*
 * UIControlEvents
 */

enum {
    UIControlEventTouchDown         =0x00000001,
    UIControlEventTouchDownRepeat   =0x00000002,
    UIControlEventTouchDragInside   =0x00000004,
    UIControlEventTouchDragOutside  =0x00000008,
    UIControlEventTouchDragEnter    =0x00000010,
    UIControlEventTouchDragExit     =0x00000020,
    UIControlEventTouchUpInside     =0x00000040,
    UIControlEventTouchUpOutside    =0x00000080,
    UIControlEventTouchCancel       =0x00000100,
    UIControlEventAllTouchEvents    =0x00000FFF,
    
    UIControlEventApplicationReserved=0x0F000000,
    UIControlEventSystemReserved    =0xF0000000,
    
    UIControlEventAllEvents         =0xFFFFFFFF
};
typedef NSUInteger UIControlEvents;

/*
 * UIControl
 */

@interface UIControl: UIView

@property(nonatomic,getter=isEnabled) BOOL enabled;
@property(nonatomic,getter=isSelected) BOOL selected;
@property(nonatomic,getter=isHighlighted) BOOL highlighted;
@property(nonatomic,readonly) UIControlState state;

@property(nonatomic,readonly,getter=isTracking) BOOL tracking;
@property(nonatomic,readonly,getter=isTouchInside) BOOL touchInside;

-(BOOL)beginTrackingWithTouch:(UITouch*)touch withEvent:(UIEvent*)event;
-(BOOL)continueTrackingWithTouch:(UITouch*)touch withEvent:(UIEvent*)event;
-(void)endTrackingWithTouch:(UITouch*)touch withEvent:(UIEvent*)event;
-(void)cancelTrackingWithEvent:(UIEvent*)event;

-(void)addTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)events;
-(void)removeTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)events;

//-(NSSet*)allTargets;
//-(UIControlEvents)allControlEvents;
//-(NSArray *)actionsForTarget:(id)target forControlEvent:(UIControlEvents)controlEvent;

-(void)sendAction:(SEL)action to:(id)target forEvent:(UIEvent *)event;
//-(void)sendActionsForControlEvents:(UIControlEvents)controlEvents;

@end
