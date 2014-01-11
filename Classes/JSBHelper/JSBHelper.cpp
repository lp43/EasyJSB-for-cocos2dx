//
//  JSBHelper.cpp
//  TestJSBHelper
//
//  Created by Simon on 14/1/4.
//
//

#include "JSBHelper.h"
#include "ScriptingCore.h"
#include "NDKHelper.h"

#define __CALLED_METHOD__           "calling_method_name"
#define __CALLED_METHOD_PARAMS__    "calling_method_params"

using namespace std;
CCObject *m_pSelectorTarget = NULL;
vector<JSBHelperCallbackNode> JSBHelper::selectorList;
JSObject *jsJSBHelperObject = NULL;
extern jsval anonEvaluate(JSContext *cx, JSObject *thisObj, const char* string);

//Don't need to understand.
void JSBHelper::CallCppFunction(const char* methodName ,const char* methodParams){
//    CCLog("into callCppFunc, methodName is: %s, methodParams is: %s", methodName, methodParams);
    if (methodName == NULL){
        CCLog("[Error!!] Can't call cpp function without function name.");
        return;
    }
    
//    CCLog("into 26");
//    CCLog("into JSBHelper::selectorList.size(): %lu",JSBHelper::selectorList.size());
    
    for (unsigned int i = 0; i < JSBHelper::selectorList.size(); ++i)
    {
//         CCLog("into 29");
        if (JSBHelper::selectorList[i].getName().compare(methodName) == 0)
        {
//         CCLog("into 32");
            SEL_CallFuncND sel = JSBHelper::selectorList[i].getSelector();
            CCNode *target = JSBHelper::selectorList[i].getTarget();
//                CCLog("into 34");
            if (sel) {
                (target->*sel)(NULL,(void*)methodParams);
            }
            
            break;
        }else{
            CCLog("[Error!!] Can't find function: %s. Please ensure it has been addSelector in Cpp side.",methodName);
        }
    }
}
void JSBHelper::CallNativeFunction(const char* methodName ,const char* methodParams){
//    CCLog("into CallNativeFunction, methodName is: %s, methodParams is: %s", methodName, methodParams);
    
    if (methodName == NULL){
        CCLog("[Error!!] Can't call cpp function without function name.");
        return;
    }
    
    json_error_t jerror;
    json_t* jsonPrms = json_loads(methodParams, 0, &jerror);

    if (!jsonPrms)
    {
        fprintf(stderr, "error: on line %d: %s\n", jerror.line, jerror.text);
    }
    
    if (methodParams != NULL)
    {
        json_t *toBeSentJson = json_object();
        json_t *jsonMethodParams = json_object_get(jsonPrms, __CALLED_METHOD_PARAMS__);

        json_object_set_new(toBeSentJson, __CALLED_METHOD_PARAMS__, jsonMethodParams);
        CCObject* obj = (CCDictionary*)NDKHelper::GetCCObjectFromJson(toBeSentJson);
        SendMessageWithParams(methodName, obj);
        json_decref(jsonPrms);
        json_decref(toBeSentJson);
        json_decref(jsonMethodParams);
    }
    
}
//Before you call Cpp function from Javascript, need to add Cpp function to JSBHelper by this function.
void JSBHelper::AddSelector( const char *name, SEL_CallFuncND selector, CCNode* target)
{
    JSBHelper::selectorList.push_back(JSBHelperCallbackNode( name, selector, target));
}


void JSBHelper::HandleMessage(json_t *methodName, json_t* methodParams)
{
//    CCLog("into HandleMessage, methodParams:%s",json_string_value(methodParams));
    
    SendMessageToJS(json_string_value(methodName), NDKHelper::GetCCObjectFromJson(methodParams));
}
void JSBHelper::RemoveAtIndex(int index)
{
    JSBHelper::selectorList[index] = JSBHelper::selectorList.back();
    JSBHelper::selectorList.pop_back();
    CCLog("JSBHelper::selectorList size: %lu ",JSBHelper::selectorList.size());
//    JSBHelper::selectorList.erase(JSBHelper::selectorList.begin() + index);
//    CCLog("JSBHelper::selectorList size: %lu ",JSBHelper::selectorList.size());
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../cocos2dx/platform/android/jni/JniHelper.h"
#include <android/log.h>
#include <jni.h>
#define  LOG_TAG    "EasyJSB-for-cocos2dx"

#endif
extern "C"
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // Method for recieving NDK messages from Java, Android
    void Java_com_easyjsb_classes_AndroidJSBHelper_JSCallHandler(JNIEnv* env, jobject thiz, jstring json)
    {
        string jsonString = JniHelper::jstring2string(json);
        const char *jsonCharArray = jsonString.c_str();
        
        CCLOG("jsonCharArray: %s",jsonCharArray);
        
        json_error_t error;
        json_t *root;
        root = json_loads(jsonCharArray, 0, &error);
        
        if (!root)
        {
            fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
            return;
        }
        
        json_t *jsonMethodName, *jsonMethodParams;
        jsonMethodName = json_object_get(root, __CALLED_METHOD__);
        jsonMethodParams = json_object_get(root, __CALLED_METHOD_PARAMS__);
        
        // Just to see on the log screen if messages are propogating properly
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, jsonCharArray);
        JSBHelper::HandleMessage(jsonMethodName, jsonMethodParams);

        json_decref(root);
    }
#endif
    
    //Call Javascript function.
    void SendMessageToJS(const char* jsMethodName,CCObject* cobj){
        
        ScriptingCore* sc = ScriptingCore::getInstance();
        JSContext *cx = sc->getGlobalContext();
        
        const char *methodParams = NULL;
        string jsonStr("");
        
        if(cobj){
//            CCLog("into have cobj");
           
            json_t *jsonParams = NDKHelper::GetJsonFromCCObject(cobj);
            jsonStr = json_dumps(jsonParams, JSON_COMPACT | JSON_ENSURE_ASCII);
            methodParams = jsonStr.c_str();

        }

//        CCLOG("methodParams in SendMessageToJS: %s",methodParams);
        if (jsJSBHelperObject == NULL)
            jsJSBHelperObject = JSVAL_TO_OBJECT(anonEvaluate(cx, sc->getGlobalObject(), "(function () { return JSBHelper; })()"));
        
        if (methodParams)
        {
//            CCLog("into methodParams = 2");
            jsval argv[2];
            argv[0] = c_string_to_jsval(cx,jsMethodName);
            argv[1] = c_string_to_jsval(cx,methodParams);
            
            jsval res;
            JS_CallFunctionName(cx, jsJSBHelperObject, "GetMessageFromCpp", 2, argv, &res);
        }
        else
        {
//                        CCLog("into methodParams = 1");
            jsval argv[1];
            argv[0] = c_string_to_jsval(cx,jsMethodName);
            
            jsval res;
            JS_CallFunctionName(cx, jsJSBHelperObject, "GetMessageFromCpp", 1, argv, &res);
        }
        
    }
}