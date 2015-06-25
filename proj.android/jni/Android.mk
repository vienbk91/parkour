LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/bowman/BowManMainScene.cpp \
                   ../../Classes/bowman/BowManMenuScene.cpp \
                   ../../Classes/bowman/BowManPlayGameScene.cpp \
                   ../../Classes/bowman/BowManHightScore.cpp \
                   ../../Classes/bowman/BowManSelectMap.cpp \
                   ../../Classes/bowman/BowManStoryScene.cpp \
                   ../../Classes/bowman/MyBodyParser.cpp \
				   ../../Classes/bowman/CustomFollow.cpp \
                   ../../Classes/bowman/BowManLevelTwo.cpp \
                   ../../Classes/bowman/SqlUtils.cpp \
                   ../../Classes/uiTest/ListViewGameScene.cpp \
                   ../../Classes/uiTest/ScrollViewScene.cpp \
                   ../../Classes/uiTest/LoadingScene.cpp \
                   ../../Classes/uiTest/UIDialog.cpp \
				   ../../Classes/uiTest/PageViewTest.cpp \
                   ../../Classes/parkour/Coin.cpp \
                   ../../Classes/parkour/Rock.cpp \
                   ../../Classes/parkour/Global.cpp \
                   ../../Classes/parkour/BackgroundLayer.cpp \
                   ../../Classes/parkour/RunnerSprite.cpp \
                   ../../Classes/parkour/ParkourGameOver.cpp \
                   ../../Classes/parkour/ParkourMenu.cpp \
                   ../../Classes/parkour/PlayScene.cpp \
                   ../../Classes/enemyKill/EnemyKillScene.cpp \
                   ../../Classes/enemyKill/EnemyKillGameOver.cpp \
                   ../../Classes/sqlTest/RegisterFormScene.cpp \
                   ../../Classes/sqlTest/TestSQLite.cpp \
                   ../../Classes/box2DTest/Box2DTest.cpp \
                   ../../Classes/sqlite/sqlite3.c \
                   ../../Classes/soundTest/SoundTest.cpp \
				   ../../Classes/httpRequest/HttpRequestTest.cpp \
				   ../../Classes/cocosStudioTest/CocosStudioTest.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
