/* ddbd.h
 *  
 * Copyright (C) 2004 Free Software Foundation, Inc.
 *
 * Author: Enrico Sersale <enrico@imago.ro>
 * Date: February 2004
 *
 * This file is part of the GNUstep GWorkspace application
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

#ifndef DDBD_H
#define DDBD_H

#include <Foundation/Foundation.h>
#include "config.h"
#ifdef HAVE_SQLITE
  #include "SQLite.h"
#endif

enum {   
  DDBdInsertTreeUpdate,
  DDBdRemoveTreeUpdate,
  DDBdFileOperationUpdate,
  DDBdDaylyUpdate
};

typedef BOOL (*boolIMP)(id, SEL, id);
typedef char *(*charIMP)(id, SEL, id);

@protocol	DDBdProtocol

- (BOOL)dbactive;

- (BOOL)insertPath:(NSString *)path;

- (BOOL)removePath:(NSString *)path;

- (oneway void)removePaths:(NSArray *)paths;

- (void)insertDirectoryTreesFromPaths:(NSData *)info;

- (void)removeTreesFromPaths:(NSData *)info;

- (NSData *)treeFromPath:(NSData *)pathinfo;

- (NSData *)directoryTreeFromPath:(NSString *)path;

- (NSString *)annotationsForPath:(NSString *)path;

- (oneway void)setAnnotations:(NSString *)annotations
                      forPath:(NSString *)path;

- (NSString *)fileTypeForPath:(NSString *)path;

- (oneway void)setFileType:(NSString *)type
                   forPath:(NSString *)path;

- (NSString *)modificationDateForPath:(NSString *)path;

- (oneway void)setModificationDate:(NSString *)datedescr
                           forPath:(NSString *)path;

- (NSData *)iconDataForPath:(NSString *)path;

- (oneway void)setIconData:(NSData *)data
                   forPath:(NSString *)path;

- (BOOL)setInfoOfPath:(NSString *)src
               toPath:(NSString *)dst;

- (BOOL)performWriteQuery:(NSString *)query;

@end


@interface DDBd: NSObject <DDBdProtocol>
{
  NSString *dbpath;
  NSConnection *conn;
  NSRecursiveLock *lock;
  NSFileManager *fm;
  NSNotificationCenter *nc; 

  NSMutableCharacterSet *skipSet;
  
#ifdef HAVE_SQLITE
  sqlite3 *db;
#endif
}

- (NSData *)infoOfType:(NSString *)type
               forPath:(NSString *)path;

- (void)setInfo:(NSString *)info
         ofType:(NSString *)type
        forPath:(NSString *)path;

- (BOOL)checkPath:(NSString *)path;
                                                     
- (void)connectionBecameInvalid:(NSNotification *)notification;

- (void)fileSystemDidChange:(NSNotification *)notif;

- (void)performDaylyUpdate:(id)sender;

- (void)threadWillExit:(NSNotification *)notification;
            
@end


@interface DDBd (indexing)

- (void)indexContentsOfFile:(NSString *)path;

@end

#endif // DDBD_H
