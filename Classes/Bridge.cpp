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
    CCLog("This is method: helloCpp in Cpp, get parameter: %s",(char*)data);

    CCDictionary* dic = new CCDictionary();
    dic->setObject(CCString::create("I am message from CPP"), "message");
    
//    SendMessageToJS("helloJS", NULL);
    SendMessageToJS("helloJS", dic);
    dic->release();
};