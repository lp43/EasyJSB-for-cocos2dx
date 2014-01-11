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
