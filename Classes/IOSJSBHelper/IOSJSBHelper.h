//
//  IOSJSBHelper.h
//  ChallengeJS
//
//  Created by Simon on 14/1/9.
//
//
#ifndef __EasyNDK_for_cocos2dx__IOSJSBHelper__
#define __EasyNDK_for_cocos2dx__IOSJSBHelper__
#import <Foundation/Foundation.h>

@interface IOSJSBHelper : NSObject
+ (void) SendMessageToJS:(NSString*)methodName WithParameters:(NSDictionary*)prms;
@end

#endif /* defined(__EasyJSB_for_cocos2dx__IOSJSBHelper__) */