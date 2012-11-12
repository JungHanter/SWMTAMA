#pragma once

#include "GameStd.h"
#include "cocos2d.h"
#include "Animal.h"
#include "DataManager.h"

enum UI_INGAME { INGAME_START = 10000, 
	BTN_OPTION, 
	BTN_FRIENDS, 
	BTN_MULTI_PRACTICE, 
	BLACKBOARD, 
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
	TRAIN_LEVEL, INGAME_END };

class UIManager
{
private:
	DataManager*	pData;
    
public:
	static UIManager* create();
	bool init();
	bool loadUI(cocos2d::CCLayer* pLayer, LAYERS layerEnum);
	void setDataManager(DataManager* pDataManager);
	void frame(cocos2d::CCLayer* pLayer, float dt);
    void setSpeaker(cocos2d::CCLayer* pLayer, UI_INGAME speaker_only);
    void setQuestion(cocos2d::CCLayer* pLayer, int who);

private:
    void callMenuTrain(cocos2d::CCObject *sender);
    
public:
	void TouchesBegan(cocos2d::CCLayer* pLayer, cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void TouchesMoved(cocos2d::CCLayer* pLayer, cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void TouchesEnded(cocos2d::CCLayer* pLayer, cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

