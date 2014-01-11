//
//  JSBHelperCallbackNode.cpp
//  JSBHelperCallbackNode-for-cocos2dx
//
//  Created by Simon on 04/01/2014.
//
//

#include "JSBHelperCallbackNode.h"

JSBHelperCallbackNode::JSBHelperCallbackNode(const char *name, SEL_CallFuncND sel, CCNode *target)
{
    this->name = name;
    this->sel = sel;
    this->target = target;
}

string JSBHelperCallbackNode::getName()
{
    return this->name;
}

SEL_CallFuncND JSBHelperCallbackNode::getSelector()
{
    return this->sel;
}

CCNode* JSBHelperCallbackNode::getTarget()
{
    return this->target;
}