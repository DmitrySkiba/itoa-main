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
#import <UIKit/UIResponder.h>

/*
 * UIViewAutoresizing
 */

enum {
    UIViewAutoresizingNone                  =0x00,
    UIViewAutoresizingFlexibleLeftMargin    =0x01,
    UIViewAutoresizingFlexibleWidth         =0x02,
    UIViewAutoresizingFlexibleRightMargin   =0x04,
    UIViewAutoresizingFlexibleTopMargin     =0x08,
    UIViewAutoresizingFlexibleHeight        =0x10,
    UIViewAutoresizingFlexibleBottomMargin  =0x20
};
typedef NSUInteger UIViewAutoresizing;

/*
 * UIView
 */

@class CALayer, UIWindow, UIColor;

@interface UIView: UIResponder

-(id)initWithFrame:(CGRect)frame;

/* layer */

+(Class)layerClass;
@property(nonatomic,readonly) CALayer* layer;

/* hierarchy */

@property(nonatomic,readonly) UIWindow* window;
@property(nonatomic,readonly) UIView* superview;
@property(nonatomic,readonly,copy) NSArray* subviews;

-(BOOL)isDescendantOfView:(UIView*)view;

-(void)removeFromSuperview;

-(void)addSubview:(UIView*)subview;
-(void)insertSubview:(UIView*)subview atIndex:(NSInteger)index;
-(void)insertSubview:(UIView*)subview belowSubview:(UIView*)siblingSubview;
-(void)insertSubview:(UIView*)subview aboveSubview:(UIView*)siblingSubview;
-(void)exchangeSubviewAtIndex:(NSInteger)index1 withSubviewAtIndex:(NSInteger)index2;

-(void)bringSubviewToFront:(UIView*)subview;
-(void)sendSubviewToBack:(UIView*)subview;

-(void)didAddSubview:(UIView*)subview;
-(void)willRemoveSubview:(UIView*)subview;
-(void)willMoveToSuperview:(UIView*)superview;
-(void)didMoveToSuperview;
-(void)willMoveToWindow:(UIWindow*)window;
-(void)didMoveToWindow;

/* geometry */

@property(nonatomic) CGRect frame;
@property(nonatomic) CGRect bounds;
@property(nonatomic) CGPoint center;
@property(nonatomic) CGAffineTransform transform;

-(CGPoint)convertPoint:(CGPoint)point toView:(UIView*)view;
-(CGPoint)convertPoint:(CGPoint)point fromView:(UIView*)view;
-(CGRect)convertRect:(CGRect)rect toView:(UIView*)view;
-(CGRect)convertRect:(CGRect)rect fromView:(UIView*)view;

-(UIView*)hitTest:(CGPoint)point withEvent:(UIEvent*)event;
-(BOOL)pointInside:(CGPoint)point withEvent:(UIEvent*)event;

/* */

@property(nonatomic,getter=isHidden) BOOL hidden;

@property(nonatomic,retain) UIColor* backgroundColor;
@property(nonatomic) UIViewAutoresizing autoresizingMask;

@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;
@property(nonatomic) NSInteger tag;

@end
