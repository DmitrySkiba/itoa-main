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

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitBase.h>
#import <UIKit/UIView.h>
#import <UIKit/UIEvent.h>

/*
 * UIWindow notifications
 */

UIKIT_EXPORT NSString* const UIWindowDidBecomeVisibleNotification;
UIKIT_EXPORT NSString* const UIWindowDidBecomeHiddenNotification;
UIKIT_EXPORT NSString* const UIWindowDidBecomeKeyNotification;
UIKIT_EXPORT NSString* const UIWindowDidResignKeyNotification;

/*
 * UIWindow
 */

@interface UIWindow: UIView

@property(nonatomic,readonly,getter=isKeyWindow) BOOL keyWindow;

-(void)becomeKeyWindow;
-(void)resignKeyWindow;
-(void)makeKeyWindow;
-(void)makeKeyAndVisible;

-(UIResponder*)nextResponder;

-(void)sendEvent:(UIEvent*)event;

@end
