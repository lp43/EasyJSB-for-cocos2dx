//
//  JSBHelper.h
//  TestJSBHelper
//
//  Created by Simon on 14/1/4.
//
//

#ifndef __JSBHelperSample__JSBHelper__
#define __JSBHelperSample__JSBHelper__

#include "jansson.h"
#include <iostream>
#include "cocos2d.h"
#include "JSBHelperCallbackNode.h"


using namespace cocos2d;

class JSBHelper : public cocos2d::CCObject
{
public:
    //Don't need to understand.
    static void CallCppFunction(const char* methodName ,const char* methodParams);
    static void CallNativeFunction(const char* methodName ,const char* methodParams);
    //Before you call Cpp function from Javascript, need to add Cpp function to JSBHelper by this function.
    static void AddSelector(const char *name, SEL_CallFuncND selector, CCNode* target);
    static void HandleMessage(json_t *methodName, json_t* methodParams);
    
private :
    static vector<JSBHelperCallbackNode> selectorList;
    static void RemoveAtIndex(int index);
};
extern "C"
{
    //Call Javascript function.
    void SendMessageToJS(const char* jsMethodName,CCObject* obj);
}
#endif /* defined(__JSBHelperSample__JSBHelper__) */
