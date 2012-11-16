#include "InGameScene.h"

#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include <JniHelper.h>

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

CCLayer* InGameScene::pUILayer = NULL;

cocos2d::CCScene* InGameScene::scene()
{
	CCScene *scene = NULL;
	do
	{
		scene = CCScene::create();
        scene->setTag(TAG_INGAMESCENE);
		CC_BREAK_IF(!scene);

        pUILayer = CCLayer::create();
        CC_BREAK_IF(!pUILayer);
        pUILayer->setTag(TAG_INGAMEUILAYER);
        scene->addChild(pUILayer, 1000);
        
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

		CC_BREAK_IF( !initBackground(this, "background.jpg", winSize) );
		CC_BREAK_IF( !initTerrain("tamagotchi_testmap.tmx", winSize) );

		pData = DataManager::create();

        
        
		accountKey = 0;
		ANIMALINFO animalInfo1( 1, LION, 0, 0, "뽀삐" );
		pData->makeDataFromAnimalInfo(accountKey, animalInfo1);
		this->addChild(pData->getAnimalByAnimalKey(accountKey, animalInfo1.key)->getSprite());

        ANIMALINFO animalInfo2( 2, ELEPHANT, 0, 0, "애봉이" );
		pData->makeDataFromAnimalInfo(accountKey, animalInfo2);
		this->addChild(pData->getAnimalByAnimalKey(accountKey, animalInfo2.key)->getSprite());

        ANIMALINFO animalInfo3( 3, MONKEY, 0, 0, "초코" );
		pData->makeDataFromAnimalInfo(accountKey, animalInfo3);
		this->addChild(pData->getAnimalByAnimalKey(accountKey, animalInfo3.key)->getSprite());
        
		schedule(schedule_selector(InGameScene::frame), 1.f/60);
		
		this->setTouchEnabled(true);

		pUI = UIManager::create();
		pUI->init();
		pUI->setDataManager(pData);
		CC_BREAK_IF( !pUI->loadUI(this, INGAME, pUILayer) );
        
        pUI->setSpeaker(pUILayer, SPEAKER_MUTE);
        
		debugLabel = CCLabelTTF::create("Test Get", "Arial", 22);
		debugLabel->setPosition(ccp(WINSIZE_X / 2, WINSIZE_Y - 100));
		pUILayer->addChild(debugLabel);

        debugLabel2 = CCLabelTTF::create("Test Who", "Arial", 22);
		debugLabel2->setPosition(ccp(WINSIZE_X / 2, WINSIZE_Y - 150));
        debugLabel2->setTag(9999);
		pUILayer->addChild(debugLabel2);
        
        label_create_animal = (CCLabelTTF*)pUILayer->getChildByTag(CREATE_LABEL_NAME);
        tf_create_animal = (CCTextFieldTTF*)pUILayer->getChildByTag(CREATE_TF_NAME);
        
		istoucheDelegate = false;
		bRet = true;
        
        initRecognition();
        runAction(CCCallFunc::create(this, callfunc_selector(InGameScene::startVoiceRecognition)));
        CCLog("3");
	} while(0);

	return bRet;
}

void InGameScene::frame(float dt)
{
	if( istoucheDelegate && pData->getPointedAnimal(accountKey) != -1 )
	{
        float scale = getScale();
        CCPoint point = lastestTouch;
        CCPoint location = getPosition();
        point.x -= WINSIZE_X/2 + location.x;
        point.y -= WINSIZE_Y/2 + location.y;
        point.x /= scale;
        point.y /= scale;
        point.x += WINSIZE_X/2;
        point.y += WINSIZE_Y/2;
        
		Animal* animal = pData->getAnimalByAnimalKey(accountKey, pData->getPointedAnimal(accountKey));
		if(animal->getMotionState() != STAND )
		{
			animal->getSprite()->stopAllActions();
			animal->cancelAllMotions();
		}
		animal->runActionWithMotion(STAND);
		animal->getSprite()->setPosition(point);
	}
    if( getChildByTag(ICON_QUESTION)->isVisible() )
    {
        int accountKey = 0;
        int animalKey = pData->getLastPointedAnimal(accountKey);
        if( animalKey != -1 )
        {
            static float timer = 0.f;
            Animal *animal = pData->getAnimalByAnimalKey(accountKey, animalKey);
            CCPoint questionPos = animal->getSprite()->getPosition();
            questionPos.y += animal->getSprite()->getContentSize().height;
            getChildByTag(ICON_QUESTION)->setPosition(questionPos);
            if( timer > 2.f )
            {
                getChildByTag(ICON_QUESTION)->setVisible(false);
                timer = 0.f;
            }
            timer += dt;
        }
    }
    pData->frame(this, dt);
    ((CCLabelTTF*)(pUILayer->getChildByTag(9999)))->setString(CCString::createWithFormat("Last %d", pData->getLastPointedAnimal(0))->getCString());
	pUI->frame(this, dt);
}

void InGameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	istoucheDelegate = true;
	for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch *touch = static_cast<CCTouch*>(*it);
		lastestTouch = touch->getLocation();
        
        float scale = getScale();
        CCPoint point = touch->getLocation();
        CCPoint location = getPosition();
        point.x -= WINSIZE_X/2 + location.x;
        point.y -= WINSIZE_Y/2 + location.y;
        point.x /= scale;
        point.y /= scale;
        point.x += WINSIZE_X/2;
        point.y += WINSIZE_Y/2;
        
        // 터치된 동물을 찾는다
        if( !getChildByTag(THINK_CLOUD)->isVisible() || (getChildByTag(THINK_CLOUD)->isVisible() && !CCRect::CCRectContainsPoint( getChildByTag(THINK_CLOUD)->boundingBox(), point)) )
        {
            
            pData->setPointedAnimal( accountKey, pData->findAnimalRectContainsPoint(accountKey, point) );
        }
            
        
	}
	pUI->TouchesBegan(this, pTouches, pEvent);
}

void InGameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if( !getChildByTag(THINK_CLOUD)->isVisible() )
    {
        float scale = getScale();
        if( pTouches->count() > 1)
        {
            static float fPrevGap = 0.f;
            CCSetIterator it = pTouches->begin();
            CCTouch *touch1 = static_cast<CCTouch*>(*it++);
            CCTouch *touch2 = static_cast<CCTouch*>(*it);
            CCPoint point1 = touch1->getLocation();
            CCPoint point2 = touch2->getLocation();
            
            float fGap = sqrtf((point2.x-point1.x)*(point2.x-point1.x)+(point2.y-point1.y)*(point2.y-point1.y));
            if( fGap > fPrevGap )
            {
                if( scale < 2.f )
                    scale *= 1.03f;
            }
            else
            {
                //if( scale > 0.6f )
                scale /= 1.03f;
            }
            fPrevGap = fGap;
            
            CCPoint location = getPosition();
            if( isInBackground(location, scale) )
                setScale(scale);
        }
        else
        {
            CCTouch *touch = static_cast<CCTouch*>(pTouches->anyObject());
            
            CCPoint ptGap = touch->getLocation();
            ptGap.x -= touch->getPreviousLocation().x;
            ptGap.y -= touch->getPreviousLocation().y;
            
            CCPoint damage = getPosition();
            damage.x += ptGap.x;
            damage.y += ptGap.y;
            
            if( isInBackground(damage, scale) )
                setPosition(damage);
        }
    }
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
    CCTouch *touch = static_cast<CCTouch*>(pTouches->anyObject());

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

bool InGameScene::isInBackground(CCPoint location, float scale)
{
    float left      = (-WINSIZE_X/2-location.x)/scale + WINSIZE_X/2;
    float top       = (WINSIZE_Y/2-location.y)/scale + WINSIZE_Y/2;
    float right     = (WINSIZE_X/2-location.x)/scale + WINSIZE_X/2;
    float bottom    = (-WINSIZE_Y/2-location.y)/scale + WINSIZE_Y/2;
    
    // 백그라운드 받아와서 처리해야함. 원래는
    return !(left < -0.5f*WINSIZE_X || right > 1.5f*WINSIZE_X || bottom < -0.5f*WINSIZE_Y || top > 1.5f*WINSIZE_Y);
}

void InGameScene::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
    
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    //m_labelStatusCode->setString(statusString);
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
	std::string s = "";
    printf("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        CCLog("%c", (*buffer)[i]);
		s += (*buffer)[i];
    }
	CCLog("%s", s.data() );
    CCLog("\n");
}

bool InGameScene::onTextFieldAttachWithIME(CCTextFieldTTF* sender)
{
    return false;
}

bool InGameScene::onTextFieldDetachWithIME(CCTextFieldTTF * sender)
{
    return false;
}

bool InGameScene::onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen)
{
    
    return false;
}

bool InGameScene::onTextFieldInsertText(CCTextFieldTTF* sender, const char* text, int nLen)
{
    switch (sender->getTag()) {
        case CREATE_TF_NAME:
            if( strcmp(text,"\n") == 0 )
                label_create_animal->setString("ID");
            else
                label_create_animal->setString(text);
            break;
    }
    
    return true;
}

void InGameScene::Debug(const char *string)
{
    debugLabel->cleanup();
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
//hanter
void InGameScene::startVoiceRecognition() {
    JniMethodInfo info;
    if(JniHelper::getMethodInfo(info, "com.swm.vg.RecognitionManager", "startVoiceRecognition", "()V"))
    {
        CCLog("JNI--startVoiceRecognition");
        info.env->CallVoidMethod(recogManager, info.methodID);
    }
}

void InGameScene::stopVoiceRecognition() {
    JniMethodInfo info;
    if(JniHelper::getMethodInfo(info, "com.swm.vg.RecognitionManager", "stopVoiceRecognition", "()V"))
    {
        CCLog("JNI--stopVoiceRecognition");
        info.env->CallVoidMethod(recogManager, info.methodID);
    }
}

void InGameScene::startTeachRecogntion() {
    JniMethodInfo info;
    if(JniHelper::getMethodInfo(info, "com.swm.vg.RecognitionManager", "startTeachRecogntion", "()V"))
    {
        CCLog("JNI--startTeachRecogntion");
        info.env->CallVoidMethod(recogManager, info.methodID);
    }
    pUI->setSpeaker(pUILayer, SPEAKER_MUTE);
}

void InGameScene::stopTeachRecogntion() {
    JniMethodInfo info;
    if(JniHelper::getMethodInfo(info, "com.swm.vg.RecognitionManager", "stopTeachRecogntion", "()V"))
    {
        CCLog("JNI--stopTeachRecogntion");
        info.env->CallVoidMethod(recogManager, info.methodID);
    }
    pUI->setSpeaker(pUILayer, SPEAKER_MUTE);
}

void InGameScene::teachSpeeching(int who, int action) {
    //hanter important
    CCLog(CCString::createWithFormat("teach action : who=%d/action=%d", who, action)->getCString());
    JniMethodInfo info;
    if(JniHelper::getMethodInfo(info, "com.swm.vg.RecognitionManager", "teachSpeeching", "(II)V"))
    {
        CCLog("JNI--teachSpeeching");
        info.env->CallVoidMethod(recogManager, info.methodID, (jint)who, (jint)action);
    }
    pUI->setSpeaker(pUILayer, SPEAKER_MUTE);
}

void InGameScene::teachNameSpeeching(int who) {
    //hanter important
    CCLog(CCString::createWithFormat("teach name : who=%d", who)->getCString());
    JniMethodInfo info;
    if(JniHelper::getMethodInfo(info, "com.swm.vg.RecognitionManager", "teachNameSpeeching", "(I)V"))
    {
        CCLog("JNI--teachNameSpeeching");
        info.env->CallVoidMethod(recogManager, info.methodID, (jint)who);
    }
    pUI->setSpeaker(pUILayer, SPEAKER_MUTE);
}

void InGameScene::teachConfirm(bool isSave) {
    JniMethodInfo info;
    if(JniHelper::getMethodInfo(info, "com.swm.vg.RecognitionManager", "teachConfirm", "(Z)V"))
    {
        CCLog("JNI--teachConfirm");
        info.env->CallVoidMethod(recogManager, info.methodID, (jboolean)isSave);
    }
}


/*** java -> cpp callback function ***/
void InGameScene::callbackOnVoiceRecognitionResult(CCObject* paramObj) {
    CCLog("callback -- callbackOnVoiceRecognitionResult");
    Parameters* param = (Parameters*)paramObj;
    int who = param->arg1;
    int action = param->arg2;
    int extra = param->arg3;
    CCLog(CCString::createWithFormat("communication : who=%d/action=%d", who, action)->getCString());
    
    //hanter improtant
    //who부터 있는지 검사해야함
    if( who == -1 ) return;
    
    //    param->release();
    if(action == ACTION_EXTRA_UNKNOWN) {
        //question mark
        pUI->setQuestion(this, who);
    } else {
        pData->getAnimalByAnimalKey(accountKey, who)->doAction(action);
    }
}

void InGameScene::callbackOnRecognitionReady() {
    CCLog("callback -- callbackOnRecognitionReady(Mic on)");
    pUI->setSpeaker(pUILayer, SPEAKER_3);
}

void InGameScene::callbackOnRecognitionIdle() {
    CCLog("callback -- callbackOnRecognitionIdle(Mic off)");
    pUI->setSpeaker(pUILayer, SPEAKER_MUTE);
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
        CCLog(CCString::createWithFormat("natevie commu : who=%d/action=%d", (int)who, (int)action)->getCString());
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





