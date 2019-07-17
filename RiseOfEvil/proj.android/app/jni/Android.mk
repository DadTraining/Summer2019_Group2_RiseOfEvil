LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
	           $(LOCAL_PATH)/../../../Classes/LoadingScene.cpp \
	           $(LOCAL_PATH)/../../../Classes/MainMenuScene.cpp \
	           $(LOCAL_PATH)/../../../Classes/WorldScene1.cpp \
	           $(LOCAL_PATH)/../../../Classes/Bullet.cpp \
	           $(LOCAL_PATH)/../../../Classes/Crystal.cpp \
	           $(LOCAL_PATH)/../../../Classes/Monster.cpp \
	           $(LOCAL_PATH)/../../../Classes/Objects.cpp \
	           $(LOCAL_PATH)/../../../Classes/Player.cpp \
	           $(LOCAL_PATH)/../../../Classes/Skill.cpp \
	           $(LOCAL_PATH)/../../../Classes/Tower.cpp \
	           $(LOCAL_PATH)/../../../Classes/UpgradeScene.cpp \
	           $(LOCAL_PATH)/../../../Classes/WorldMapScene.cpp \
	           $(LOCAL_PATH)/../../../Classes/ResourceManager.cpp \
	           $(LOCAL_PATH)/../../../Classes/Wave.cpp \
	           $(LOCAL_PATH)/../../../Classes/Soldier.cpp \
	           $(LOCAL_PATH)/../../../Classes/LogoScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
