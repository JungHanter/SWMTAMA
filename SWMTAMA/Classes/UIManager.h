#pragma once

#include "GameStd.h"
#include "cocos2d.h"
#include "Animal.h"
#include "DataManager.h"

enum UI_LOGIN { LOGIN_START = 10000,
    BTN_HOUSE_LOGIN,
    BTN_HOUSE_CREATE,
    LOGIN_TEXT_ID,
    LOGIN_TEXT_PW,
    TEXT_PASSWORD,
    FRAME_LOGIN_ID,
    FRAME_LOGIN_PW,
    TEXT_LOGIN_ID,
    TEXT_LOGIN_PW,
    LOGIN_CREATE_BLACKBOARD,
    LOGIN_CREATE_FRAME_OK,
    LOGIN_CREATE_TEXT_OK,
    LOGIN_CREATE_TEXT, LOGIN_END };

enum UI_INGAME { INGAME_START = 20000,
	BTN_OPTION, 
	BTN_FRIENDS, 
	BTN_MULTI_PRACTICE,
    BTN_CREATE_ANIMAL,
    BTN_GO_HOME,
	TRAINING_BLACKBOARD,
	THINK_CLOUD, 
	ICON_MEAT, 
	ICON_BLACKBOARD,
	ICON_SWING,
	ICON_RUNNING,
    ICON_ROPE,
    ICON_QUESTION,
	SPEAKER_DEFAULT, 
	SPEAKER_1,
	SPEAKER_2,
	SPEAKER_3,
	SPEAKER_MUTE,
    MENU_TRAIN,
    TEXTBTN_NAME, 
	TRAIN_NAME,
	TRAIN_LEVEL,
	STATUS_BLACKBOARD,
    STATUS_TEXT1,
    STATUS_TEXT2,
    STATUS_TEXT3,
    STATUS_TEXT4,
    STATUS_TEXT5,
    STATUS_TEXT6,
    STATUS_PROGRESS_FRAME1,
    STATUS_PROGRESS_FRAME2,
    STATUS_PROGRESS_FRAME3,
    STATUS_PROGRESS_FRAME4,
    STATUS_PROGRESS_FRAME5,
    STATUS_PROGRESS_FRAME6,
    STATUS_PROGRESS_BAR1,
    STATUS_PROGRESS_BAR2,
    STATUS_PROGRESS_BAR3,
    STATUS_PROGRESS_BAR4,
    STATUS_PROGRESS_BAR5,
    STATUS_PROGRESS_BAR6,
    LAYER_CREATE,
    CREATE_BLACKBOARD,
    CREATE_TEXT,
    CREATE_OK,
    CREATE_CLOSE,
    CREATE_TEXT_OK,
    CREATE_TEXT_CLOSE,
    CREATE_PREV,
    CREATE_NEXT,
    CREATE_LION_IMG,
    CREATE_ELEPHANT_IMG,
    CREATE_MONKEY_IMG,
    CREATE_SQUIRREL_IMG,
    CREATE_FRAME_NAME,
    CREATE_LABEL_NAME,
    CREATE_TF_NAME,
    OPTION_BLACKBOARD,
    OPTION_FRAME_YES,
    OPTION_FRAME_NO,
    OPTION_TEXT_YES,
    OPTION_TEXT_NO,
    OPTION_TEXT_QUESTION, INGAME_END };

enum UI_FRIEND { FRIEND_START = 30000,
    THUMBNAIL,
    FRAME_NAME,
    FRAME_LEVEL,
    TEXT_NAME,
    TEXT_LEVEL,
    PREV,
    NEXT,
    HOME,
    BTN_ADD,
    BTN_HOME,
    TEXT_ADD,
    TEXT_HOME,
    IMG_THUMBNAIL,
    IMG_FRAME_THUMBNAIL,
    ADD_BLACKBOARD,
    ADD_TEXT, 
    ADD_FRAME_OK,
    ADD_FRAME_CANCEL,
    ADD_TEXT_OK,
    ADD_TEXT_CANCEL, 
    ADD_FRAME_FRIEND,
    ADD_LABEL_FRIEND,
    ADD_TF_FRIEND, FRIEND_END };

class UIManager
{
private:
	DataManager*	pData;
    ANIMAL_TYPE     create_animal_type;
    int             friendIndex;
    int             hostAccountKey;
    
public:
	static UIManager* create();
	bool init();
	bool loadUI(cocos2d::CCLayer* pLayer, LAYERS layerEnum, cocos2d::CCLayer* pUILayer = NULL);
	void setDataManager(DataManager* pDataManager);
	void frame(cocos2d::CCLayer* pLayer, float dt);
    void setSpeaker(cocos2d::CCLayer* pLayer, UI_INGAME speaker_only);
    void setQuestion(cocos2d::CCLayer* pLayer, int who);
    void setProgressBar(cocos2d::CCLayer* pLayer);
    void setCreateAnimalType(cocos2d::CCLayer* pLayer);
    
private:
    void callMenuTrain(cocos2d::CCObject *sender);
    
private:
    void createAnimal(cocos2d::CCLayer *pLayer);
    
public:
	void TouchesBegan(cocos2d::CCLayer* pLayer, cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void TouchesMoved(cocos2d::CCLayer* pLayer, cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void TouchesEnded(cocos2d::CCLayer* pLayer, cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

