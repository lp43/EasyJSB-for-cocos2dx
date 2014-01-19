//
//  Bridge.cpp
//  EasyJSBSample
//
//  Created by Simon on 14/1/4.
//
//

#include "Bridge.h"
#include "JSBHelper.h"
using namespace std;

void Bridge::helloCpp(CCNode* sender, void* data){
    CCLog("This is method: helloCpp in Cpp");
    
    CCDictionary* dic = (CCDictionary*)data;
    const char* str = dic->valueForKey("message")->getCString();
    CCLog("parameter is: %s",str);
    const char* str2 = dic->valueForKey("message2")->getCString();
    CCLog("parameter is: %s",str2);
    
    CCDictionary* dic2 = new CCDictionary();
    dic2->setObject(CCString::create("I am message from CPP"), "message");
    
//    SendMessageToJS("helloJS", NULL);
    SendMessageToJS("helloJS", dic2);
    dic2->release();
};