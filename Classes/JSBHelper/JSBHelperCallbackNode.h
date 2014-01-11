//
//  JSBHelperCallbackNode.cpp
//  JSBHelperCallbackNode-for-cocos2dx
//
//  Created by Simon on 04/01/2014.
//
//

#ifndef __JSBHelper_for_cocos2dx__JSBHelperCallbackNode__
#define __JSBHelper_for_cocos2dx__JSBHelperCallbackNode__

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class JSBHelperCallbackNode
{
    private :
    string name;
    SEL_CallFuncND sel;
    CCNode *target;
    
    public :
    JSBHelperCallbackNode(const char *name, SEL_CallFuncND sel, CCNode *target);
    string getName();
    SEL_CallFuncND getSelector();
    CCNode* getTarget();
};

#endif /* defined(__JSBHelper_for_cocos2dx__JSBHelperCallbackNode__) */
