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
 * CALayer
 */

@interface CALayer: NSObject {
    @public void* m_impl;
    @private void* m_delegateImpl;
}

+(CALayer*)layer;

-(id)init;
-(id)initWithBounds:(CGRect)bounds;

@property(nonatomic,assign) id delegate;

@property(nonatomic,readonly) CALayer* superlayer;
-(void)removeFromSuperlayer;

@property(nonatomic,copy) NSArray* sublayers;
-(void)addSublayer:(CALayer*)layer;
-(void)insertSublayer:(CALayer*)layer atIndex:(unsigned int)index;
-(void)insertSublayer:(CALayer*)layer below:(CALayer*)sibling;
-(void)insertSublayer:(CALayer*)layer above:(CALayer*)sibling;
-(void)replaceSublayer:(CALayer*)layer with:(CALayer*)layer2;

-(void)setNeedsDisplay;
-(void)setNeedsDisplayInRect:(CGRect)rect;

-(void)drawInContext:(CGContextRef)context;

@property(nonatomic) CGRect frame;
@property(nonatomic) CGRect bounds;
@property(nonatomic) CGPoint position;
@property(nonatomic) CGPoint anchorPoint;

-(CGAffineTransform)affineTransform;
-(void)setAffineTransform:(CGAffineTransform)transform;

@property(nonatomic) BOOL masksToBounds;
@property(nonatomic,getter=isHidden) BOOL hidden;
@property(nonatomic) CGColorRef backgroundColor;

-(CGPoint)convertPoint:(CGPoint)point fromLayer:(CALayer*)layer;
-(CGPoint)convertPoint:(CGPoint)point toLayer:(CALayer*)layer;
-(CGRect)convertRect:(CGRect)rect fromLayer:(CALayer*)layer;
-(CGRect)convertRect:(CGRect)rect toLayer:(CALayer*)layer;

-(BOOL)containsPoint:(CGPoint)point;

@end

/*
 * CALayerDelegate
 */

@interface NSObject (CALayerDelegate)

-(void)displayLayer:(CALayer*)layer;
-(void)drawLayer:(CALayer*)layer inContext:(CGContextRef)context;

@end
