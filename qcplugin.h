// (CC) quartzcomposer.jp 
// 2005/07/31 version 0.1
// Licensed under Attribution-NonCommercial-ShareAlike : http://creativecommons.org/licenses/by-nc-sa/2.5/

#include <Carbon/Carbon.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface GFNodeManager : NSObject
- (void)registerNodeWithClass:(Class)patch_class;
@end

@protocol GFPlugInRegistration
+ (void)registerNodesWithManager:(GFNodeManager*)manager;
@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface GFNode : NSObject
{
    int __dummyNode[13];
}
@end

@interface GFGraph : GFNode
{
	int __dummyGraph[7];
}
@end

@interface QCPatch : GFGraph
{
	int __dummyPatch[19];
}
@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface QCNumberPort
- (double)doubleValue;
- (void)setDoubleValue:(double)value;
@end

@interface QCColorPort
- (float)redComponent;
- (float)greenComponent;
- (float)blueComponent;
- (float)alphaComponent;
- (void)setRedComponent:(float)red;
- (void)setGreenComponent:(float)green;
- (void)setBlueComponent:(float)blue;
- (void)setAlphaComponent:(float)alpha;
@end

@interface QCStringPort
- (NSString*)stringValue;
- (void)setStringValue:(NSString*)fp8;
@end

@interface QCBooleanPort
- (BOOL)booleanValue;
- (void)setBooleanValue:(BOOL)value;
@end

@interface QCIndexPort
- (unsigned int)indexValue;
- (void)setIndexValue:(unsigned int)value;
@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface QCGLPort_Color
- (void)set:(CGLContextObj)ctx;
- (void)unset:(CGLContextObj)ctx;
@end

@interface QCGLPort_Image
- (void)set:(CGLContextObj)ctx;
- (void)unset:(CGLContextObj)ctx;
@end

@interface QCGLPort_Blending
- (void)set:(CGLContextObj)ctx;
- (void)unset:(CGLContextObj)ctx;
@end

@interface QCGLPort_Culling
- (void)set:(CGLContextObj)ctx;
- (void)unset:(CGLContextObj)ctx;
@end

@interface QCGLPort_ZBuffer
- (void)set:(CGLContextObj)ctx;
- (void)unset:(CGLContextObj)ctx;
@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface QCOpenGLContext
- (CGLContextObj)CGLContextObj;
@end
