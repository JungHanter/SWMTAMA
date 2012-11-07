#include "InGameScene.h"

#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include <JniHelper.h>

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

cocos2d::CCScene* InGameScene::scene()
{
	CCScene *scene = NULL;
	do
	{
		scene = CCScene::create();
        scene->setTag(TAG_INGAMESCENE);
		CC_BREAK_IF(!scene);

		InGameScene *layer = InGameScene::create();
//        layer->setTag(TAG_INGAMELAYER);
		CC_BREAK_IF(!layer);

		layer->setTag(INGAME);
		scene->addChild(layer);
	} while(0);

	return scene;
}

bool InGameScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CC_BREAK_IF( !initBackground("background.jpg", winSize) );
		CC_BREAK_IF( !initTerrain("tamagotchi_testmap.tmx", winSize) );

		pData = DataManager::create();


		accountKey = 0;
		ANIMALINFO animalInfo;
		animalInfo.key = 0;
		animalInfo.type = LION;
		strcpy(animalInfo.level, "0  ");
		strcpy(animalInfo.name, "애봉이");
		pData->makeDataFromAnimalInfo(accountKey, animalInfo);
		this->addChild(pData->getAnimalByAnimalKey(accountKey, animalInfo.key)->getSprite());

		animalInfo.key = 1;
		animalInfo.type = ELEPHANT;
		strcpy(animalInfo.level, "0  ");
		strcpy(animalInfo.name, "애봉이");
		pData->makeDataFromAnimalInfo(accountKey, animalInfo);
		this->addChild(pData->getAnimalByAnimalKey(accountKey, animalInfo.key)->getSprite());

		schedule(schedule_selector(InGameScene::frame), 1.f/60);
		
		this->setTouchEnabled(true);

		pUI = UIManager::create();
		pUI->init();
		pUI->setDataManager(pData);
		CC_BREAK_IF( !pUI->loadUI(this, INGAME) );
        pUI->setSpeaker(this, SPEAKER_MUTE);
        
		debugLabel = CCLabelTTF::create("Test Get", "Arial", 22);
		debugLabel->setPosition(ccp(WINSIZE_X / 2, WINSIZE_Y - 100));
		addChild(debugLabel);

		istoucheDelegate = false;
		bRet = true;
        
        initRecognition();
        runAction(CCCallFunc::create(this, callfunc_selector(InGameScene::startVoiceRecognition)));
	} while(0);

	return bRet;
}

void InGameScene::frame(float dt)
{
	if( istoucheDelegate && pData->getPointedAnimal(accountKey) != -1 )
	{
		Animal* animal = pData->getAnimalByAnimalKey(accountKey, pData->getPointedAnimal(accountKey));
		if(animal->getMotionState() != STAND )
		{
			animal->getSprite()->stopAllActions();
			animal->cancelAllMotions();
		}
		animal->runActionWithMotion(STAND);
		animal->getSprite()->setPosition(lastestTouch);
	}
	char a[32];
	sprintf(a, "%d", pData->getPointedAnimal(accountKey));
//	Debug(a);
	pUI->frame(this, dt);
}

void InGameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	istoucheDelegate = true;
	for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch *touch = static_cast<CCTouch*>(*it);
		lastestTouch = touch->getLocation();
		pData->setPointedAnimal( accountKey, pData->findAnimalRectContainsPoint(accountKey, lastestTouch) );
	}
	pUI->TouchesBegan(this, pTouches, pEvent);
}

void InGameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch *touch = static_cast<CCTouch*>(*it);
		lastestTouch = touch->getLocation();
	}
	pUI->TouchesMoved(this, pTouches, pEvent);
}

void InGameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	istoucheDelegate = false;
	for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch *touch = static_cast<CCTouch*>(*it);
		lastestTouch = touch->getLocation();
	}
	pData->setPointedAnimal( accountKey, -1 );
	pUI->TouchesEnded(this, pTouches, pEvent);

}

bool InGameScene::initTerrain(const char *filename, cocos2d::CCSize winSize)
{
	CCTMXTiledMap*	pTerrain	= CCTMXTiledMap::tiledMapWithTMXFile(filename);
	CCSize			sizeTerrain = pTerrain->getContentSize();
	
	if( !pTerrain ) return false;

	pTerrain->setScaleX(GAME_SCALE*WINSIZE_X/sizeTerrain.width);
	pTerrain->setScaleY(GAME_SCALE*WINSIZE_X/sizeTerrain.width);
	pTerrain->setAnchorPoint(ccp(0.5f, 0.5f));
	pTerrain->setPosition(ccp(WINSIZE_X/2, winSize.height/2));
	this->addChild(pTerrain, 0.5);

	return true;
}

bool InGameScene::initBackground(const char *filename, cocos2d::CCSize winSize)
{
	CCSprite*	pBackground		= CCSprite::create(filename);
    CCSize		sizeBackground	= pBackground->getContentSize();

	if( !pBackground ) return false;

	pBackground->setScaleX(GAME_SCALE*WINSIZE_X/sizeBackground.width);
	pBackground->setScaleY(GAME_SCALE*WINSIZE_Y/sizeBackground.height);
	pBackground->setPosition(ccp(WINSIZE_X/2, winSize.height/2));

	this->addChild(pBackground, 0 );

	return true;
}

void InGameScene::Debug(const char *string)
{
	debugLabel->setString(string);
}



/**********   voice Recognition    **********/
void InGameScene::initRecognition() {
    JniMethodInfo info;
    if(JniHelper::getStaticMethodInfo(info, "com.swm.vg.RecognitionManager", "getNowManager", "()Ljava/lang/Object;"))
    {
        recogManager = info.env->CallStaticObjectMethod(info.classID, info.methodID);
    }
}

InGameScene* InGameScene::getGameLayer() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* pScene = pDirector->getRunningScene();
    int tag = pScene->getTag();
    if(tag == TAG_INGAMESCENE) {
        CCNode* pNode = pScene->getChildByTag(TAG_INGAMELAYER);
        if(pNode != NULL) {
            return (InGameScene*)pNode;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

/*** cpp -> java method call ***/
void InGameScene::startVoiceRecognition() {
    JniMethodInfo info;
    if(JniHelper::getMethodInfo(info, "com.swm.vg.RecognitionManager", "startVoiceRecognition", "()V"))
    {
        CCLog("JNI--startVoiceRecognition");
        info.env->CallVoidMethod(recogManager, info.methodID); // 호출합니다.
    }
}

void InGameScene::stopVoiceRecognition() {
    JniMethodInfo info;
    if(JniHelper::getMethodInfo(info, "com.swm.vg.RecognitionManager", "stopVoiceRecognition", "()V"))
    {
        CCLog("JNI--stopVoiceRecognition");
        info.env->CallVoidMethod(recogManager, info.methodID); // 호출합니다.
    }
}

void InGameScene::startTeachRecogntion() {
    
}

void InGameScene::stopTeachRecogntion() {
    
}

void InGameScene::teachSpeeching(int who, int action) {
    
}

void InGameScene::teachNameSpeeching(int who) {
    
}

void InGameScene::teachConfirm(bool isSave) {
    
}


/*** java -> cpp callback function ***/
void InGameScene::callbackOnVoiceRecognitionResult(CCObject* paramObj) {
    Parameters* param = (Parameters*)paramObj;
    int who = param->arg1;
    int action = param->arg2;
    int extra = param->arg3;
    
    //    param->release();
}

void InGameScene::callbackOnRecognitionReady() {
    CCLog("callback -- callbackOnRecognitionReady(Mic on)");
    pUI->setSpeaker(this, SPEAKER_3);
}

void InGameScene::callbackOnRecognitionIdle() {
    CCLog("callback -- callbackOnRecognitionIdle(Mic off)");
    pUI->setSpeaker(this, SPEAKER_MUTE);
}

void InGameScene::callbackOnRecognitionVolumeChanged(CCObject* paramObj) {
    CCLog("callback -- onRecognitionVolumeCahnaged");
    Parameters* param = (Parameters*)paramObj;
    int step = param->arg1;
    //    param->release();
}

void InGameScene::callbackOnRecognitionError(CCObject* paramObj) {
    Parameters* param = (Parameters*)paramObj;
    int error = param->arg1;
    
    //    param->release();
}

void InGameScene::callbackOnTeachingReady() {
    
}

void InGameScene::callbackOnTeachingResult(CCObject* paramObj) {
    Parameters* param = (Parameters*)paramObj;
    int resultCode = param->arg1;
    
    //    param->release();
}

void InGameScene::callbackOnTeachingVolumeChanged(CCObject* paramObj) {
    CCLog("callback -- callbackOnTeachingVolumeChanged");
    Parameters* param = (Parameters*)paramObj;
    int step = param->arg1;
    
//    setVolume(step);
    
    //    param->release();
}

void InGameScene::callbackSetLabel(CCObject* objLabel) {
    CCLog("callback -- callbackSetLabel");
    CCString* label = (CCString*)objLabel;
    
    Debug(label->getCString());
}


#ifndef __recognition
extern "C" {
#endif
    void Java_com_swm_vg_RecognitionManager_callbackOnVoiceRecognitionResult(JNIEnv* env, jobject thisObj, jint who, jint action, jint extra)
    {
        InGameScene* gameLayer = InGameScene::getGameLayer();
        if(gameLayer != NULL) {
            gameLayer->runAction(CCCallFuncO::create(gameLayer, callfuncO_selector(InGameScene::callbackOnVoiceRecognitionResult),
                                                     Parameters::create((int)who, (int)action, (int)extra)));
        }
    }
    
    void Java_com_swm_vg_RecognitionManager_callbackOnRecognitionReady(JNIEnv* env, jobject thisObj)
    {
        InGameScene* gameLayer = InGameScene::getGameLayer();
        if(gameLayer != NULL) {
            gameLayer->runAction(CCCallFunc::create(gameLayer, callfunc_selector(InGameScene::callbackOnRecognitionReady)));
        }
    }
    
    void Java_com_swm_vg_RecognitionManager_callbackOnRecognitionIdle(JNIEnv* env, jobject thisObj)
    {
        InGameScene* gameLayer = InGameScene::getGameLayer();
        if(gameLayer != NULL) {
            gameLayer->runAction(CCCallFunc::create(gameLayer, callfunc_selector(InGameScene::callbackOnRecognitionIdle)));
        }
    }
    
    void Java_com_swm_vg_RecognitionManager_callbackOnRecognitionVolumeChanged(JNIEnv* env, jobject thisObj, jint step)
    {
        InGameScene* gameLayer = InGameScene::getGameLayer();
        if(gameLayer != NULL) {
            gameLayer->runAction(CCCallFuncO::create(gameLayer, callfuncO_selector(InGameScene::callbackOnRecognitionVolumeChanged),
                                                     Parameters::create((int)step)));
        }
    }
    
    void Java_com_swm_vg_RecognitionManager_callbackOnRecognitionError(JNIEnv* env, jobject thisObj, jint error)
    {
        InGameScene* gameLayer = InGameScene::getGameLayer();
        if(gameLayer != NULL) {
            gameLayer->runAction(CCCallFuncO::create(gameLayer, callfuncO_selector(InGameScene::callbackOnRecognitionError),
                                                     Parameters::create((int)error)));
        }
    }
    
    void Java_com_swm_vg_RecognitionManager_callbackOnTeachingReady(JNIEnv* env, jobject thisObj)
    {
        InGameScene* gameLayer = InGameScene::getGameLayer();
        if(gameLayer != NULL) {
            gameLayer->runAction(CCCallFunc::create(gameLayer, callfunc_selector(InGameScene::callbackOnTeachingReady)));
        }
    }
    
    void Java_com_swm_vg_RecognitionManager_callbackOnTeachingResult(JNIEnv* env, jobject thisObj, jint resultCode)
    {
        InGameScene* gameLayer = InGameScene::getGameLayer();
        if(gameLayer != NULL) {
            gameLayer->runAction(CCCallFuncO::create(gameLayer, callfuncO_selector(InGameScene::callbackOnTeachingResult),
                                                     Parameters::create((int)resultCode)));
        }
    }
    
    void Java_com_swm_vg_RecognitionManager_callbackOnTeachingVolumeChanged(JNIEnv* env, jobject thisObj, jint step)
    {
        InGameScene* gameLayer = InGameScene::getGameLayer();
        if(gameLayer != NULL) {
            gameLayer->runAction(CCCallFuncO::create(gameLayer, callfuncO_selector(InGameScene::callbackOnTeachingVolumeChanged),
                                                     Parameters::create((int)step)));
        }
    }
    
    void Java_com_swm_vg_RecognitionManager_callbackSetLabel(JNIEnv* env, jobject thisObj, jstring str) {
        InGameScene* gameLayer = InGameScene::getGameLayer();
        if(gameLayer != NULL) {
            const char* label = JniHelper::jstring2string(str).c_str();
            //            gameLayer->setLabel(label);
            gameLayer->runAction(CCCallFuncO::create(gameLayer, callfuncO_selector(InGameScene::callbackSetLabel),
                                                     CCString::create(label)));
        }
    }
#ifndef __recognition
}
#endif





