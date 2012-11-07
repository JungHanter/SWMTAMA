#pragma once
#ifndef __INGAME_SCENE_H__
#define __INGAME_SCENE_H__

#include "BasisScene.h"
#include "Parameters.h"
#include <jni.h>

#define TAG_INGAMESCENE 100
#define TAG_INGAMELAYER INGAME


class InGameScene : public BasisScene
{
	int accountKey;
	CCLabelTTF *debugLabel;
	bool istoucheDelegate;
	cocos2d::CCPoint lastestTouch;

public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	void frame(float dt);
	
	CREATE_FUNC(InGameScene);

private:
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

private:
	bool initTerrain(const char *filename, cocos2d::CCSize winSize);
	bool initBackground(const char *filename, cocos2d::CCSize winSize);


    
/** game <-> voiceRecognition **/
public:
    void initRecognition();
    static InGameScene* getGameLayer();
    
    //cpp->java
public:
    void startVoiceRecognition();
	void stopVoiceRecognition();
	void startTeachRecogntion();
	void stopTeachRecogntion();
	void teachSpeeching(int who, int action);
	void teachNameSpeeching(int who);
	void teachConfirm(bool isSave);
    
    //java->cpp
public:
    void callbackOnVoiceRecognitionResult(cocos2d::CCObject* paramObj);
	void callbackOnRecognitionReady();
	void callbackOnRecognitionIdle();
	void callbackOnRecognitionVolumeChanged(cocos2d::CCObject* paramObj);
	void callbackOnRecognitionError(cocos2d::CCObject* paramObj);
	void callbackOnTeachingReady();
	void callbackOnTeachingResult(cocos2d::CCObject* paramObj);
	void callbackOnTeachingVolumeChanged(cocos2d::CCObject* paramObj);
    void callbackSetLabel(CCObject* objLabel);
    
private:
    jobject recogManager;
/** end of game<->voiceRecognition **/
    
    
    
	//Temporary
private:
	void Debug(const char *string);
};

#endif