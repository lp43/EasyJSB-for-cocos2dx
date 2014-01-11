var JSBHelper = JSBHelper || {};
JSBHelper.selectorArray = {};
/**
 * [Corresponding to Manner second]
 *
 * Call Cpp function.
 *
 * @param func_name Function you want to use within Cpp.
 * @param func_params Parameters you want to send that is needed by Cpp function.
 * @param callback_name If Cpp function completed the work, what JS function name is you want to get message after that.
 * @param callback If Cpp function completed the work, what JS function is you want to get message after that.
 */
SendMessageToNativeWithCallbackName = function(func_name, func_params, callback_name, callback){
    if( sys.platform == 'browser')return;

    var type_cb = typeof callback;

    if(type_cb != 'function')
        throw "Expression is of type " +type_cb+ ",not function";


    var callMethod = {};
    callMethod["calling_method_name"] = func_name;
    //結果︰{"calling_method_name":"checkNetwork"}

    var jsonStr = null;
    if(func_params!==null){
        var callParam = {};
        for(key in func_params){
            callParam[key] = func_params[key];
        }
        callMethod["calling_method_params"] = callParam;

        jsonStr = JSON.stringify(callMethod);
        cc.log("jsonStr: "+jsonStr);
    }


    if(callback!==null)
    JSBHelper.AddSelector(callback_name, callback);

    JSBHelper.SendMessageToNative(func_name, jsonStr);
};
/**
 *
 * Call Cpp function.
 *
 * If you can't use this method for null, use sendMessageToCppWithCallbackName alternatively.
 *
 * @param func_name Function you want to use within Cpp.
 * @param func_params Parameters you want to send that is needed by Cpp function.
 * @param callback If Cpp function completed the work, what JS function is you want to get message after that.
 */
//SendMessageToNativeWithCallback = function(func_name, func_params, callback){
//    if( sys.platform == 'browser')return;
//
//    var type_cb = typeof callback;
//
//    if(type_cb != 'function')
//        throw "Expression is of type " +type_cb+ ",not function";
//
////    cc.log("function is: "+callback.toString());
//
//    var fName = callback.toString().match(/function ([^\(]+)/)[1];
//
//    cc.log("func name: "+fName);
//
//    SendMessageToNativeWithCallbackName(func_name,func_params,fName,callback);
//};
/**
 * [Corresponding to Manner second]
 *
 * Call Cpp function.
 *
 * @param func_name Function you want to use within Cpp.
 * @param func_params Parameters you want to send that is needed by Cpp function.
 * @param callback_name If Cpp function completed the work, what JS function name is you want to get message after that.
 * @param callback If Cpp function completed the work, what JS function is you want to get message after that.
 */
SendMessageToCppWithCallbackName = function(func_name, func_params, callback_name, callback){
    if( sys.platform == 'browser')return;

    cc.log("into SendMessageToCppWithCallbackName");




    var jsonParams = null;
    if(func_params!==null){
        var callMethod = {};
        callMethod["calling_method_name"] = func_name;
        //結果︰{"calling_method_name":"checkNetwork"}

        var callParam = {};
        for(key in func_params){
            callParam[key] = func_params[key];
        }
        callMethod["calling_method_params"] = callParam;

        jsonParams = JSON.stringify(callMethod);
//        cc.log("jsonParams: "+jsonParams);
    }

    if(callback!==null){
        var type_cb = typeof callback;

        if(type_cb != 'function')
            throw "Expression is of type " +type_cb+ ",not function";

        JSBHelper.AddSelector(callback_name, callback);
    }


    JSBHelper.SendMessageToCppWithParams(func_name, func_params);
};
/**
 * [Corresponding to third manner]
 *
 * Call Cpp function.
 *
 * If you can't use this method for null, use sendMessageToCppWithCallbackName alternatively.
 *
 * @param func_name Function you want to use within Cpp.
 * @param func_params Parameters you want to send that is needed by Cpp function.
 * @param callback If Cpp function completed the work, what JS function is you want to get message after that.
 */
SendMessageToCppWithCallback = function(func_name, func_params, callback){
    if( sys.platform == 'browser')return;

    var type_cb = typeof callback;

    if(type_cb != 'function')
        throw "Expression is of type " +type_cb+ ",not function";

//    cc.log("function is: "+callback.toString());

    var fName = callback.toString().match(/function ([^\(]+)/)[1];

    cc.log("func name: "+fName);

    SendMessageToCppWithCallbackName(func_name,func_params,fName,callback);
};
SendMessageToCpp = function(func_name, func_params){
    if( sys.platform == 'browser')return;

    cc.log("into JS: SendMessageToCpp");
    SendMessageToCppWithCallbackName(func_name,func_params,null,null);
};
/**
 *
 * Before you want to call JS function on Cpp side,
 * you need to addSelector function to JSBHelper.
 *
 * @param func_name What function name you will plan to be called from Cpp side.
 * @param selector What function you will plan to be called from Cpp side.
 */
JSBHelper.AddSelector = function(func_name, selector){
    if( sys.platform == 'browser')return;
    cc.log("into JS: AddSelector");

    JSBHelper.selectorArray[func_name] = selector;
};
/**
 * This is callback from Cpp,
 * you don't need to understand it.
 *
 * @param func_name
 * @param returnValue
 * @constructor
 */
JSBHelper.GetMessageFromCpp = function(func_name,returnValue){
    if( sys.platform == 'browser')return;

    if(JSBHelper.selectorArray[func_name]==null){
        cc.log("[Error!!] Can't find function: "+func_name+". Please ensure it has been addSelector in Javascript side.");
        return;
    }
//     cc.log("returnValue: "+returnValue);
    JSBHelper.selectorArray[func_name](returnValue);

    delete JSBHelper.selectorArray[func_name];
};
