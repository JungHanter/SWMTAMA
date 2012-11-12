LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Animal.cpp \
                   ../../Classes/BasisScene.cpp \
                   ../../Classes/DataManager.cpp \
                   ../../Classes/Elephant.cpp \
                   ../../Classes/InGameScene.cpp \
                   ../../Classes/Lion.cpp \
                   ../../Classes/LoadingScene.cpp \
                   ../../Classes/LoginScene.cpp \
                   ../../Classes/Monkey.cpp \
                   ../../Classes/NetworkManager.cpp \
                   ../../Classes/Parameters.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/PreparingScene.cpp \
                   ../../Classes/SceneManager.cpp \
                   ../../Classes/Speaker.cpp \
                   ../../Classes/Squirrel.cpp \
                   ../../Classes/UIManager.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
		/Installation/cocos2d/cocos2d-2.0-x-2.0.3/cocos2dx/platform/android/jni

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
