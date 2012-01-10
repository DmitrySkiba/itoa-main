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
#import <UIKit/UIKitBase.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIEvent.h>

@protocol UIApplicationDelegate;

/*
 * UIApplication
 */

@interface UIApplication: UIResponder

+(UIApplication*)sharedApplication;

@property(nonatomic,assign) id<UIApplicationDelegate> delegate;
@property(nonatomic,readonly) NSArray* windows;

-(void)sendEvent:(UIEvent*)event;
-(BOOL)sendAction:(SEL)action to:(id)target from:(id)sender forEvent:(UIEvent*)event;

@end

UIKIT_EXPORT UIApplication* UIApp;

/*
 * UIApplicationDelegate
 */

@protocol UIApplicationDelegate<NSObject>

//@optional

-(void)applicationDidFinishLaunching:(UIApplication*)application;

//-(void)applicationDidBecomeActive:(UIApplication*)application;
//-(void)applicationWillResignActive:(UIApplication*)application;
//-(BOOL)application:(UIApplication*)application handleOpenURL:(NSURL *)url;
//-(void)applicationDidReceiveMemoryWarning:(UIApplication*)application;
//-(void)applicationWillTerminate:(UIApplication*)application;
//-(void)applicationSignificantTimeChange:(UIApplication*)application;
//-(void)application:(UIApplication*)application willChangeStatusBarOrientation:(UIInterfaceOrientation)newStatusBarOrientation duration:(NSTimeInterval)duration;
//-(void)application:(UIApplication*)application didChangeStatusBarOrientation:(UIInterfaceOrientation)oldStatusBarOrientation;
//-(void)application:(UIApplication*)application willChangeStatusBarFrame:(CGRect)newStatusBarFrame;
//-(void)application:(UIApplication*)application didChangeStatusBarFrame:(CGRect)oldStatusBarFrame;

@end

/*
 * UIApplicationMain
 */

UIKIT_EXPORT int UIApplicationMain(int argc,char* argv[],
                                   NSString* principalClassName,
                                   NSString* delegateClassName);
