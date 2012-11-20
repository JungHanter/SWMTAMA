#include "LoadingScene.h"
#include "InGameScene.h"
#include "SceneManager.h"

using namespace cocos2d;

CCScene*   LoadingScene::pScene = NULL;

cocos2d::CCScene* LoadingScene::scene()
{
    CCScene *scene = NULL;
	do
	{
		scene = CCScene::create();
        scene->setTag(TAG_LOADINGSCENE);
		CC_BREAK_IF(!scene);
        
		LoadingScene *layer = LoadingScene::create();
		CC_BREAK_IF(!layer);
        
		layer->setTag(LOADING);
		scene->addChild(layer);
	} while(0);
    
	return scene;
}

bool LoadingScene::init()
{
    bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());
        
        CC_BREAK_IF( !initBackground(this, "title_loading.png", CCSize(WINSIZE_X, WINSIZE_Y)) );
        
        SceneManager::sharedSceneManager()->setDataManager(this);
        
        //schedule(schedule_selector(LoadingScene::frame));
        
		CC_BREAK_IF( !pUI->loadUI(this, LOADING) );
        
        CCLog("LoadingScene::init : start");
        
        
        labelLoading = CCLabelTTF::create("Loading...", "Arial", 72);
        labelLoading->setPosition(ccp(WINSIZE_X, WINSIZE_Y*0.1f));
        labelLoading->setAnchorPoint(ccp(1.0f, 0.5f));
        addChild(labelLoading);
        
        bRet = true;
    } while(0);
    
	return bRet;
}

void LoadingScene::frame(float dt)
{
    static int labelCounter = 0;
    static int frameCounter = 0;
    int percent;
    
    if( labelCounter >= 4*17 )
    {
        CCDirector::sharedDirector()->replaceScene(InGameScene::scene());
        return;
    }
    
    MOTION loadingMotion[] = {
        WALK_LEFT,
        WALK_RIGHT,
        WALK_BACK_LEFT,
        WALK_BACK_RIGHT,
        RUN_LEFT,
        RUN_RIGHT,
        RUN_BACK_LEFT,
        RUN_BACK_RIGHT,
        STAND,
        SIT,
        SLEEP,
        EAT,
        POOP,
        SICK,
        FUN_SWING,
        FUN_RUNNING,
        FUN_ROPE };
    
    string loadingLabel[] = {
        "LION_WALK_LEFT",
        "LION_WALK_RIGHT",
        "LION_WALK_BACK_LEFT",
        "LION_WALK_BACK_RIGHT",
        "LION_RUN_LEFT",
        "LION_RUN_RIGHT", 
        "LION_RUN_BACK_LEFT", 
        "LION_RUN_BACK_RIGHT", 
        "LION_STAND", 
        "LION_SIT", 
        "LION_SLEEP",
        "LION_EAT", 
        "LION_POOP", 
        "LION_SICK", 
        "LION_SWING", 
        "LION_RUNNING", 
        "LION_ROPE",
            
        "ELEPHANT_WALK_LEFT", 
        "ELEPHANT_WALK_RIGHT",
        "ELEPHANT_WALK_BACK_LEFT", 
        "ELEPHANT_WALK_BACK_RIGHT",
        "ELEPHANT_RUN_LEFT", 
        "ELEPHANT_RUN_RIGHT", 
        "ELEPHANT_RUN_BACK_LEFT", 
        "ELEPHANT_RUN_BACK_RIGHT",
        "ELEPHANT_STAND", 
        "ELEPHANT_SIT", 
        "ELEPHANT_SLEEP", 
        "ELEPHANT_EAT", 
        "ELEPHANT_POOP", 
        "ELEPHANT_SICK", 
        "ELEPHANT_SWING", 
        "ELEPHANT_RUNNING", 
        "ELEPHANT_ROPE",
            
        "MONKEY_WALK_LEFT", 
        "MONKEY_WALK_RIGHT", 
        "MONKEY_WALK_BACK_LEFT", 
        "MONKEY_WALK_BACK_RIGHT",
        "MONKEY_RUN_LEFT", 
        "MONKEY_RUN_RIGHT", 
        "MONKEY_RUN_BACK_LEFT",
        "MONKEY_RUN_BACK_RIGHT", 
        "MONKEY_STAND", 
        "MONKEY_SIT", 
        "MONKEY_SLEEP", 
        "MONKEY_EAT", 
        "MONKEY_POOP",
        "MONKEY_SICK", 
        "MONKEY_SWING", 
        "MONKEY_RUNNING", 
        "MONKEY_ROPE",
        
        "SQUIRREL_WALK_LEFT",
        "SQUIRREL_WALK_RIGHT",
        "SQUIRREL_WALK_BACK_LEFT",
        "SQUIRREL_WALK_BACK_RIGHT",
        "SQUIRREL_RUN_LEFT",
        "SQUIRREL_RUN_RIGHT",
        "SQUIRREL_RUN_BACK_LEFT",
        "SQUIRREL_RUN_BACK_RIGHT",
        "SQUIRREL_STAND",
        "SQUIRREL_SIT",
        "SQUIRREL_SLEEP",
        "SQUIRREL_EAT",
        "SQUIRREL_POOP",
        "SQUIRREL_SICK",
        "SQUIRREL_SWING",
        "SQUIRREL_RUNNING",
        "SQUIRREL_ROPE" };
    
    CCLog("Index test : %s, %d, %d, %d", loadingLabel[labelCounter].data(), (ANIMAL_TYPE)(labelCounter/17), frameCounter%8, loadingMotion[labelCounter%17]);
    
    //Animal::loadAnimateWithImage(loadingLabel[labelCounter].data(), (ANIMAL_TYPE)(labelCounter/17), frameCounter%8, loadingMotion[labelCounter%17]);
    
    labelCounter = (frameCounter++)/8;
    percent = frameCounter;
    
//    if (labelCounter < 17)
//        labelLoading->setString(CCString::createWithFormat("메마른 땅에 풀을 심는 중...%d", percent)->getCString());
//    else if (labelCounter < 34)
//        labelLoading->setString(CCString::createWithFormat("동물들의 상태를 점검하는 중...%d", percent)->getCString());
//    else if (labelCounter < 51)
//        labelLoading->setString(CCString::createWithFormat("농장에 동물들을 배치하는 중...%d", percent)->getCString());
//    else// if (labelCounter < 68)
//        labelLoading->setString(CCString::createWithFormat("농장 문을 여는 중...%d", percent)->getCString());
}

CCScene*   LoadingScene::getLoadingScene()
{
    return pScene;
}

void LoadingScene::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
{
    CCLog("LoadingScene::onHttpRequestCompleted");
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
	std::string s;
    bool isDataStarted = false;
    for (unsigned int i = 0; i < buffer->size(); i++)
	{
        if( isDataStarted == false && !isspace((*buffer)[i]) )
            isDataStarted = true;
        if( isDataStarted == false) continue;
        
        s += (*buffer)[i];
    }
	CCLog("LoadingScene::onHttpRequestCompleted : buffer=%s", s.data() );
    
    if(strcmp(response->getHttpRequest()->getTag(), "URL_RECEIVE_ANIMALS") == 0)
    {
        labelLoading->setString("동물들과 교감하는중...");
        vector<ANIMALINFO> animalList;
        
        CCLog("URL_RECEIVE_ANIMALS: it comes %d", s.length());
        
        bool isAlreadyExist = false;
        map<int, Animal*>* pList = pData->getAnimalsByAccount(SceneManager::sharedSceneManager()->getUserAccountKey());
        if( pList != NULL )
            isAlreadyExist = true;
        while (s.length() != 0)
        {
            int delimIndex = s.find('|');
            string oneAnimalData;
            
            if( delimIndex != -1 )
            {
                oneAnimalData = s.substr(0, delimIndex);
                s = s.substr(delimIndex+1);
            }
            else
            {
                oneAnimalData = s;
                s = "";
            }
            
            ANIMALINFO info;
            info.name               = oneAnimalData.substr(0, oneAnimalData.find(" ") );
            oneAnimalData = oneAnimalData.substr(oneAnimalData.find(" ")+1);
            info.key                = atoi(oneAnimalData.substr(0, oneAnimalData.find(" ") ).data());
            oneAnimalData = oneAnimalData.substr(oneAnimalData.find(" ")+1);
            info.type               = (ANIMAL_TYPE)atoi(oneAnimalData.substr(0, oneAnimalData.find(" ") ).data());
            oneAnimalData = oneAnimalData.substr(oneAnimalData.find(" ")+1);
            info.level              = atoi(oneAnimalData.substr(0, oneAnimalData.find(" ") ).data());
            oneAnimalData = oneAnimalData.substr(oneAnimalData.find(" ")+1);
            info.status.sleep       = atoi(oneAnimalData.substr(0, oneAnimalData.find(" ") ).data());
            oneAnimalData = oneAnimalData.substr(oneAnimalData.find(" ")+1);
            info.status.poop        = atoi(oneAnimalData.substr(0, oneAnimalData.find(" ") ).data());
            oneAnimalData = oneAnimalData.substr(oneAnimalData.find(" ")+1);
            info.status.exp         = atoi(oneAnimalData.substr(0, oneAnimalData.find(" ") ).data());
            oneAnimalData = oneAnimalData.substr(oneAnimalData.find(" ")+1);
            info.status.fullness    = atoi(oneAnimalData.substr(0, oneAnimalData.find(" ") ).data());
            oneAnimalData = oneAnimalData.substr(oneAnimalData.find(" ")+1);
            info.status.health      = atoi(oneAnimalData.substr(0, oneAnimalData.find(" ") ).data());
            oneAnimalData = oneAnimalData.substr(oneAnimalData.find(" ")+1);
            info.status.joy         = atoi(oneAnimalData.data());
            
            CCLog("URL_RECEIVE_ANIMALS : %s %d %d %d %d %d %d %d %d %d", info.name.c_str(), info.key, info.type, info.level, info.status.sleep, info.status.poop, info.status.exp, info.status.fullness, info.status.health, info.status.joy );
            
            pData->makeDataFromAnimalInfo(SceneManager::sharedSceneManager()->getHostAccountKey(), info);
            //            char name[32] = "께이";
            //            char strMB[256] = {0,};
            //            wchar_t strUnicode[256] = {0,};
            //            memcpy(strUnicode, info.name.data(), info.name.size());
            //            wcstombs(strMB, info.name.data(), 256);
            //
            //
            //            for(int i = 0; i < info.name.size(); i++ )
            //            {
            //                CCLog("URL_RECEIVE_ANIMALS : name %d, %d, %d", name[i], strUnicode[i], strMB[i] );
            //            }
            
        }
        
        if( SceneManager::sharedSceneManager()->isFriendHome() )
        {
            InGameScene* pInGameLayer = ((InGameScene*)InGameScene::getInGameScene()->getChildByTag(INGAME));
            pInGameLayer->resetScene(SceneManager::sharedSceneManager()->getHostAccountKey());
            CCDirector::sharedDirector()->popScene();
        }
        else
        {
            if( isAlreadyExist )
            {
                CCDirector::sharedDirector()->popScene();
                CCScene* pScene = InGameScene::getInGameScene();
                ((InGameScene*)(pScene->getChildByTag(INGAME)))->resetScene(SceneManager::sharedSceneManager()->getUserAccountKey());
            }
            else
                CCDirector::sharedDirector()->replaceScene(InGameScene::scene());
        }
    }
}

LoadingScene::LoadingScene(void)
{
}


LoadingScene::~LoadingScene(void)
{
}
