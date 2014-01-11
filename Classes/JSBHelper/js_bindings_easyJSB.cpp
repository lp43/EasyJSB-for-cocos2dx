#include "JSBHelper.h"
#include "ScriptingCore.h"

JSBool JSB_JSBHelper_SendMessageToCppWithParams(JSContext *cx, uint32_t argc, jsval *vp){
	std::string func_name ;
	std::string parameter ;
    
	jsval *argv = JS_ARGV(cx, vp);
	jsval_to_std_string(cx, argv[0], &func_name);
    jsval_to_std_string(cx, argv[1], &parameter);

    JSBHelper::CallCppFunction(func_name.c_str(),parameter.c_str());
    
    //JSVAL_TO_INT(argv[1]);
    
	return JS_TRUE;
}
JSBool JSB_JSBHelper_SendMessageToNative(JSContext *cx, uint32_t argc, jsval *vp){
    CCLog("into function: %s, line: %d",__FUNCTION__,__LINE__);
    
	std::string func_name ;
	std::string parameter ;
    
	jsval *argv = JS_ARGV(cx, vp);
    CCLog("into function: %s, line: %d",__FUNCTION__,__LINE__);

	jsval_to_std_string(cx, argv[0], &func_name);
    CCLog("into function: %s, line: %d",__FUNCTION__,__LINE__);

    jsval_to_std_string(cx, argv[1], &parameter);
    CCLog("into function: %s, line: %d",__FUNCTION__,__LINE__);
    
    JSBHelper::CallNativeFunction(func_name.c_str(),parameter.c_str());
    CCLog("into function: %s, line: %d",__FUNCTION__,__LINE__);
    
    //JSVAL_TO_INT(argv[1]);
    
	return JS_TRUE;
}
void register_JSBHelper_js(JSContext* cx, JSObject* global){
	jsval nsval;
	JSObject *pJsbObject;
    
    JS_GetProperty(cx, global, "JSBHelper", &nsval);
    
	if (nsval == JSVAL_VOID) {
        
		pJsbObject = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(pJsbObject);
		JS_SetProperty(cx, global, "JSBHelper", &nsval);
        
	} else{
        
		JS_ValueToObject(cx, nsval, &pJsbObject);

    }

	JS_DefineFunction(cx, pJsbObject, "SendMessageToCppWithParams", JSB_JSBHelper_SendMessageToCppWithParams, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, pJsbObject, "SendMessageToNative", JSB_JSBHelper_SendMessageToNative, 2, JSPROP_READONLY | JSPROP_PERMANENT);
}
