//
//  principal.h
//
//  Created by ?? ?? on 07/06/16.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//
//
//  Based on Quartz Composer Custom Patch : http://quartzcomposer.jp/article/16648245.html
//    (CC) quartzcomposer.jp 
//    2005/08/01 version 0.11
//    Licensed under Attribution-NonCommercial-ShareAlike : http://creativecommons.org/licenses/by-nc-sa/2.5/
//

#import <Cocoa/Cocoa.h>
#import "qcplugin.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface SocketReaderPatchPlugin : NSObject <GFPlugInRegistration>
+ (void)registerNodesWithManager:(GFNodeManager*)manager;
@end
