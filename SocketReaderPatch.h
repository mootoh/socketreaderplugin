//
//  SocketReaderPatch.h
//
//  Created by Motohiro Takayama on 07/06/16.
//
//  Based on following:
//  - Quartz Composer Custom Patch : http://quartzcomposer.jp/article/16648245.html
//  - Xcode Template for Custom Quartz Composer Patches : http://fdiv.net/2007/05/08/xcode-template-for-custom-quartz-composer-patches/
//
//    (CC) quartzcomposer.jp 
//    2005/08/01 version 0.11
//    Licensed under Attribution-NonCommercial-ShareAlike : http://creativecommons.org/licenses/by-nc-sa/2.5/
//

#import "qcplugin.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface SocketReaderPatch : QCPatch
{
  QCStringPort *outputString;

  int port_;
  NSString *host_;
  NSFileHandle *listeningSocket_;
  NSFileHandle *readingSocket_;
}

// QCPatch
+ (int)executionMode;
+ (BOOL)allowsSubpatches;
- (id)setup:(id)arg;
- (BOOL)execute:(QCOpenGLContext*)qcglctx time:(double)exec_time arguments:(id)arg;
- (void)cleanup:(id)arg;

- (void)setupSocket;
@end
