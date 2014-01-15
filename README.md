<img src="https://dl.dropboxusercontent.com/u/12328600/easyjsb1.png" width=500>

EasyJSB
=======

Easy to call C++ or Native(Android/IOS) method in Cocos2dx-JSB by javascript.

This project is base on [EasyNDK for cocos2d-x][1].

If you have familar with EasyNDK, you will understand EasyJSB as well.



HOW TO USE THIS?
================
1. Evironment

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

     * Call objective-c method from javascript side.example:
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
              NSDictionary *dictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:@"hello, i am message from native ios"],@"message", nil];
            
              //if you want to send callback backward to javascript when finish work on obj-c side, 
              //you can invoke method as below:
              [IOSJSBHelper SendMessageToJS:@"helloJS" WithParameters:dictionary];
         }
      ```
      
Now you can commucate easily between javascript and native.

Read more
----------

   * Blogger: [小鰻的cocos2d-x / JSB/ HTML5學習筆記Blogger][2]

[1]: https://github.com/aajiwani/EasyNDK-for-cocos2dx "EasyNDK for cocos2d-x"
[2]: http://lp43-cocos2dx.blogspot.tw/2014/01/cocos2d-x-jsbeasyjsb-beta.html "小鰻的cocos2d-x / JSB/ HTML5學習筆記"
