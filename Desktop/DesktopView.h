/* DesktopView.h
 *  
 * Copyright (C) 2004 Free Software Foundation, Inc.
 *
 * Author: Enrico Sersale <enrico@imago.ro>
 * Date: May 2004
 *
 * This file is part of the GNUstep Desktop application
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef DESKTOP_VIEW_H
#define DESKTOP_VIEW_H

#include "FSNIconsView.h"

@class NSImage;
@class Desktop;

typedef enum BackImageStyle {
  BackImageCenterStyle = 0,
  BackImageFitStyle = 1,
  BackImageTileStyle = 2
} BackImageStyle;


@interface DesktopView : FSNIconsView
{
  NSRect screenFrame;  
  NSRect *grid;
  int gridcount;
  int rowcount;

	NSImage *dragIcon;
  NSPoint dragPoint;
  int insertIndex;
	BOOL dragLocalIcon;
  
  NSImage *backImage;
  NSString *imagePath;
  NSPoint imagePoint;
  BackImageStyle backImageStyle;
  BOOL useBackImage;
    
  Desktop *desktop;
}

- (void)newVolumeMountedAtPath:(NSString *)vpath;

- (void)workspaceWillUnmountVolumeAtPath:(NSString *)vpath;

- (void)workspaceDidUnmountVolumeAtPath:(NSString *)vpath;

- (void)showMountedVolumes;

- (void)dockPositionDidChange;

- (int)firstFreeGridIndex;

- (int)firstFreeGridIndexAfterIndex:(int)index;

- (BOOL)isFreeGridIndex:(int)index;

- (FSNIcon *)iconWithGridIndex:(int)index;

- (int)indexOfGridRectContainingPoint:(NSPoint)p;

- (NSRect)iconBoundsInGridAtIndex:(int)index;

- (void)makeIconsGrid;

- (NSImage *)tshelfBackground;

- (void)updateDefaults;

@end


@interface DesktopView (DraggingDestination)

- (unsigned int)draggingEntered:(id <NSDraggingInfo>)sender;

- (unsigned int)draggingUpdated:(id <NSDraggingInfo>)sender;

- (void)draggingExited:(id <NSDraggingInfo>)sender;

- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender;

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender;

- (void)concludeDragOperation:(id <NSDraggingInfo>)sender;

@end


@interface DesktopView (BackgroundColors)

- (NSColor *)currentColor;

- (void)setCurrentColor:(NSColor *)color;

- (void)createBackImage:(NSImage *)image;

- (NSImage *)backImage;

- (NSString *)backImagePath;

- (void)setBackImageAtPath:(NSString *)impath;

- (BOOL)useBackImage;

- (void)setUseBackImage:(BOOL)value;

- (BackImageStyle)backImageStyle;

- (void)setBackImageStyle:(BackImageStyle)style;

@end

#endif // DESKTOP_VIEW_H
