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
#import <UIKit/UIControl.h>

/*
 * UIButtonType
 */

typedef enum {
    UIButtonTypeCustom,
    UIButtonTypeRoundedRect,
    UIButtonTypeDetailDisclosure,
    UIButtonTypeInfoLight,
    UIButtonTypeInfoDark,
    UIButtonTypeContactAdd,
} UIButtonType;

/*
 * UIButton
 */

@interface UIButton: UIControl

+(UIButton*)buttonWithType:(UIButtonType)type;

-(void)setTitle:(NSString*)title forState:(UIControlState)state;
// -(void)setTitleColor:(UIColor*)color forState:(UIControlState)state;
// -(void)setTitleShadowColor:(UIColor*)color forState:(UIControlState)state;
// -(void)setImage:(UIImage*)image forState:(UIControlState)state;
// -(void)setBackgroundImage:(UIImage*)image forState:(UIControlState)state;

@end
