<img src="https://dl.dropboxusercontent.com/u/12328600/easyjsb1.png" width=500>

EasyJSB
=======

Easy to call C++ or Native(Android/IOS) method in Cocos2dx-JSB by javascript.

This project is base on [EasyNDK for cocos2d-x][1].

If you have familar with EasyNDK, you will understand EasyJSB as well.



HOW TO USE THIS?
================
Evironment

This project is developed on cocos2d-x v.2.2.2, if you want to open Xcode example, download cocos2d-x v2.2.2 
and put EasyJSB project under cocos2dx(your main cocos2dx folder)\projects\ is recommanded.

* Use EasyJSB on IOS

     * Copy 5 folders and 2 files as below that under Classes into your project\Classes folder.
        * [Folder]IOSJSBHelper
        * [Folder]JSBHelper
        * [Folder]IOSNDKHelper
        * [Folder]NDKHelper
        * [Folder]jansson
        * [File]Bridge.cpp
        * [File]Bridge.h

     * Drag 5 folders as above to your Xcode project, 2 files to Classes group.
     
     * Call objective-c method from javascript side.
     example:
     ```
     var map = {};
     map["message"]="I am message from javascript."
     SendMessageToNative("helloNative",map);
     ```

     * Set NDK Receiver on objective-c side.

      ```
      - (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
          if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        
              NSLog(@"into function: %s",__FUNCTION__);
              // tell NDKHelper that RootViewController will get message from Cpp.
              [IOSNDKHelper SetNDKReciever:self];
           }
           return self;
        }
        
        - (void) helloNative:(NSObject *)prms{
        
              //if you want to send callback backward to javascript when complete the work, 
              //you can invoke method as below:
              NSDictionary *dictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:@"hello, i am message from native ios"],@"message", nil];
            
              [IOSJSBHelper SendMessageToJS:@"helloJS" WithParameters:dictionary];
         }
      ```
      
Now you can comunicate easily between javascript and objective-c (ios).

* Use EasyJSB on Android

  For using EasyJSB on Android,
  you have to declare some code in Android project.

   * Write NDK make rule to jni\Android.mk, the example is on below:
      
      ```
      LOCAL_PATH := $(call my-dir)
      include $(CLEAR_VARS)
      LOCAL_MODULE := cocos2djs_shared
      LOCAL_MODULE_FILENAME := libcocos2djs
      LOCAL_SRC_FILES := hellojavascript/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Bridge.cpp \
                   ../../Classes/jansson/dump.c \
                   ../../Classes/jansson/error.c \
                   ../../Classes/jansson/hashtable.c \
                   ../../Classes/jansson/load.c \
                   ../../Classes/jansson/memory.c \
                   ../../Classes/jansson/pack_unpack.c \
                   ../../Classes/jansson/strbuffer.c \
                   ../../Classes/jansson/strconv.c \
                   ../../Classes/jansson/utf.c \
                   ../../Classes/jansson/value.c \
                   ../../Classes/NDKHelper/NDKCallbackNode.cpp \
                   ../../Classes/NDKHelper/NDKHelper.cpp \
                   ../../Classes/JSBHelper/js_bindings_easyJSB.cpp \
                   ../../Classes/JSBHelper/JSBHelper.cpp \
                   ../../Classes/JSBHelper/JSBHelperCallbackNode.cpp
                   
         LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/NDKHelper \
                    $(LOCAL_PATH)/../../Classes/jansson \
                    $(LOCAL_PATH)/../../Classes/JSBHelper
                    
         LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
         LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
         LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
         LOCAL_WHOLE_STATIC_LIBRARIES += spidermonkey_static
         LOCAL_WHOLE_STATIC_LIBRARIES += scriptingcore-spidermonkey
         
         LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT
         
         include $(BUILD_SHARED_LIBRARY)
         
         $(call import-module,cocos2dx)
         $(call import-module,CocosDenshion/android)
         $(call import-module,external/chipmunk)
         $(call import-module,scripting/javascript/spidermonkey-android)
         $(call import-module,scripting/javascript/bindings)
       ```
         
   * Copy AndroidJSBHelper.java to package com.easyjsb.classes
     
   * Call objective-c method from javascript side
       
       example:
       ```
       var map = {};
       map["message"]="I am message from javascript."
       SendMessageToNative("helloNative",map);
       ```
       
   * Set NDK Receiver on Android side.

       ```
       protected void onCreate(Bundle savedInstanceState){
         super.onCreate(savedInstanceState);
         AndroidNDKHelper.SetNDKReciever(this);
	   }
        
       public void helloNative(JSONObject prms){
		 Log.i(TAG, TAG+" this is method: helloNative in native Android, prms: "+prms.toString());
		
		 //if you want to send callback backward to javascript when complete the work, 
         //you can invoke method as below:
		 JSONObject obj = new JSONObject();
		 try {
		      obj.put("message","I am message from native Android");
		    } catch (JSONException e) {
		      e.printStackTrace();
		  }
		  AndroidJSBHelper.SendMessageToJS(this, "helloJS", obj);
	   }
    
       static {
           System.loadLibrary("cocos2djs");
       }
       ```
       
Now you can comunicate easily between javascript and Java (Android).

Read more
----------

   * Blogger: [小鰻的cocos2d-x / JSB/ HTML5學習筆記Blogger][2]

[1]: https://github.com/aajiwani/EasyNDK-for-cocos2dx "EasyNDK for cocos2d-x"
[2]: http://lp43-cocos2dx.blogspot.tw/2014/01/cocos2d-x-jsbeasyjsb-beta.html "小鰻的cocos2d-x / JSB/ HTML5學習筆記"
