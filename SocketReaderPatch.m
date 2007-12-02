//
//  SocketReaderPatch.m
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

#import "SocketReaderPatch.h"
#include <sys/socket.h>
#include <netinet/in.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////
@implementation SocketReaderPatch : QCPatch
+ (int)executionMode {  return 0; }
+ (BOOL)allowsSubpatches { return NO; }
- (BOOL)execute:(QCOpenGLContext*)qcglctx time:(double)exec_time arguments:(id)arg { return YES; }

- (id)setup:(id)arg {
  port_ = 12345;
  host_ = [NSString stringWithString:@"localhost"];
  [outputString setStringValue:@"waiting..."];
  [self setupSocket];

  return arg;
}

// -------------------------------------------------------------------
// Socket stuff
//
- (void) setupSocket {
  struct sockaddr_in addr;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // Setup its address structure
  bzero(&addr, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY); // Bind to any of the system addresses
  addr.sin_port = htons(port_);             // Let the system choose a port for us

  assert(0 == bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)));
  assert(0 == listen(sockfd, 5));

  // Find out the port number so we can pass it to the net service initializer
  socklen_t namelen = sizeof(struct sockaddr_in);
  getsockname(sockfd, (struct sockaddr *)&addr, &namelen);

  // Create NSFileHandle to communicate with socket
  listeningSocket_ = [[NSFileHandle alloc] initWithFileDescriptor:sockfd];

  // Register for NSFileHandle socket-related Notifications
  NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
  [nc addObserver:self
         selector:@selector(accepted:)
             name:NSFileHandleConnectionAcceptedNotification
            object:nil];

  // Accept connections in background and notify
  [listeningSocket_ acceptConnectionInBackgroundAndNotify];
}

- (void)cleanup:(id)arg {
  [[NSNotificationCenter defaultCenter] removeObserver:self];
  [listeningSocket_ closeFile];
  [listeningSocket_ release];
}

// -------------------------------------------------------------------
// callback
//
- (void)accepted:(NSNotification *)notification {
  readingSocket_ = [[notification userInfo]
    objectForKey:NSFileHandleNotificationFileHandleItem];
  [readingSocket_ retain];
  assert(NULL != readingSocket_);

  NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
  [nc addObserver:self
         selector:@selector(recieved:)
             name:NSFileHandleReadCompletionNotification
           object:nil];
  [readingSocket_ readInBackgroundAndNotify];
}

- (void)recieved:(NSNotification *)notification {
  NSLog(@"recieved");
  NSData *messageData = [[notification userInfo]
    objectForKey:NSFileHandleNotificationDataItem];
  assert(NULL != messageData);

  if (0 == [messageData length]) {
    [readingSocket_ readInBackgroundAndNotify];
    return;
  }

  NSString *message = [NSString stringWithUTF8String:[messageData bytes]];
  [outputString setStringValue:message];

  [readingSocket_ readInBackgroundAndNotify];
}

@end
// vim:set ft=objc:
