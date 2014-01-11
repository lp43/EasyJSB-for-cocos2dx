//
//  Bridge.h
//  EasyJSBSample
//
//  Created by Simon on 14/1/4.
//
//

#ifndef __EasyJSBSample__Bridge__
#define __EasyJSBSample__Bridge__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class Bridge : public CCNode{
public:
    void helloCpp(CCNode* sender, void* data);
};
#endif /* defined(__EasyJSBSample__Bridge__) */
