EasyJSB
=======

Easy to call C++ or Native(Android/IOS) method in Cocos2dx-JSB by javascript.

This project is base on EasyNDK for cocos2d-x (https://github.com/aajiwani/EasyNDK-for-cocos2dx).

If you have familar with EasyNDK, you will understand EasyJSB as well.



HOW TO USE THIS?
================
1.Evironment
This project is developed on cocos2d-x v.2.2.2, if you want to open Xcode example, download cocos2d-x v2.2.2 
and put EasyJSB project under cocos2dx(your main cocos2dx folder)\projects\ is recommanded.

2.Use EasyJSB on IOS
1) Copy 5 folders and 2 files as below that under Classes into your project\Classes folder.
●[Folder]IOSJSBHelper
●[Folder]JSBHelper
●[Folder]IOSNDKHelper
●[Folder]NDKHelper
●[Folder]jansson
●[File]Bridge.cpp
●[File]Bridge.h

2)Set NDK Receiver on objective-c side.

3)Call objective-c method from javascript side.
example:
var map = {};
map["message"]="I am message from javascript."
SendMessageToNative("obj-c method name",map);

now obj-c can get message as EasyNDK.
