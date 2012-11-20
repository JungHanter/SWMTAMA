#include "FriendScene.h"
#include "SceneManager.h"

CCScene* FriendScene::pScene = NULL;
cocos2d::CCScene* FriendScene::scene()
{
    CCScene *scene = NULL;
	do
	{
		scene = CCScene::create();
        scene->setTag(TAG_FRIENDSCENE);
		CC_BREAK_IF(!scene);
        
		FriendScene *layer = FriendScene::create();
		CC_BREAK_IF(!layer);
        
		layer->setTag(FRIEND);
		scene->addChild(layer);
        
        pScene = scene;
	} while(0);
    
	return scene;
}

bool FriendScene::init()
{
    bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());
        
        CC_BREAK_IF( !initBackground(this, "title_loading.png", CCSize(WINSIZE_X, WINSIZE_Y)) );
        
        SceneManager::sharedSceneManager()->setDataManager(this);
        
		CC_BREAK_IF( !pUI->loadUI(this, FRIEND) );
        
        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        
        CCLog("FriendScene::init : start");
    
        label_add_friend = (CCLabelTTF*)getChildByTag(ADD_LABEL_FRIEND);
        tf_add_friend = (CCTextFieldTTF*)getChildByTag(ADD_TF_FRIEND);
        
        pNetwork->postMessage(URL_RECEIVE_FRIENDS, CCString::createWithFormat("accountKey=%d", SceneManager::sharedSceneManager()->getUserAccountKey())->getCString(), this, callfuncND_selector(FriendScene::onHttpRequestCompleted), "URL_RECEIVE_FRIENDS");
        
        bRet = true;
    } while(0);
    
	return bRet;
}

void FriendScene::frame(float dt)
{
    pUI->frame(this, dt);
}

void FriendScene::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
{
    CCLog("LoginScene::onHttpRequestCompleted");
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
	CCLog("FriendScene::onHttpRequestCompleted : buffer=%s", s.data() );
    
    if(strcmp(response->getHttpRequest()->getTag(), "URL_ADD_FRIEND") == 0)
    {
        pNetwork->postMessage(URL_RECEIVE_FRIENDS, CCString::createWithFormat("accountKey=%d", SceneManager::sharedSceneManager()->getUserAccountKey())->getCString(), this, callfuncND_selector(FriendScene::onHttpRequestCompleted), "URL_RECEIVE_FRIENDS");
    }
    else if(strcmp(response->getHttpRequest()->getTag(), "URL_RECEIVE_FRIENDS") == 0)
    {
        pData->deleteFriend();
        
        getChildByTag(ADD_BLACKBOARD)->setVisible(false);
        getChildByTag(ADD_FRAME_OK)->setVisible(false);
        getChildByTag(ADD_FRAME_CANCEL)->setVisible(false);
        getChildByTag(ADD_TEXT_OK)->setVisible(false);
        getChildByTag(ADD_TEXT_CANCEL)->setVisible(false);
        getChildByTag(ADD_FRAME_FRIEND)->setVisible(false);
        getChildByTag(ADD_LABEL_FRIEND)->setVisible(false);
        getChildByTag(ADD_TF_FRIEND)->setVisible(false);
        
        while (s.length() != 0)
        {
            int delimIndex = s.find('|');
            string oneFriendData;
            
            if( delimIndex != -1 )
            {
                oneFriendData = s.substr(0, delimIndex);
                s = s.substr(delimIndex+1);
            }
            else
            {
                oneFriendData = s;
                s = "";
            }
            
            int accountKey = atoi(oneFriendData.substr(0, oneFriendData.find(" ")).data());
            oneFriendData = oneFriendData.substr(oneFriendData.find(" ")+1);
            string ID = oneFriendData;
            pData->addFriend(accountKey, ID);
            
            CCLog("URL_RECEIVE_FRIENDS : %d %s", accountKey, ID.data());
        }
        // Friend List 갱신 -> Friend List 구조체 필요
        // 로딩씬 넣기
        // 로딩하며 데이터 로드 완료해두기
        // 똥싸기 및 행동정의 제대로 해두기
        // queue리스트 업데이트 하기
        // 단체 가르치기 업데이트
        
        if( pData->getFriendList()->size() != 0 )
        {
            string ID = pData->getFriendList()->at(0).second;
            ((CCLabelTTF*)(getChildByTag(TEXT_NAME)))->setString(ID.data());
        }
    }
}

cocos2d::CCScene* FriendScene::getFriendScene()
{
    return pScene;
}

void FriendScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    pUI->TouchesBegan(this, pTouches, pEvent);
}

void FriendScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    pUI->TouchesMoved(this, pTouches, pEvent);
}

void FriendScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    pUI->TouchesEnded(this, pTouches, pEvent);
}

bool FriendScene::onTextFieldAttachWithIME(CCTextFieldTTF* sender)
{
    return false;
}

bool FriendScene::onTextFieldDetachWithIME(CCTextFieldTTF * sender)
{
    return false;
}

bool FriendScene::onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen)
{
    
    return false;
}

bool FriendScene::onTextFieldInsertText(CCTextFieldTTF* sender, const char* text, int nLen)
{
    switch (sender->getTag()) {
        case ADD_TF_FRIEND:
            if( strcmp(text,"\n") == 0 )
                label_add_friend->setString("Input ID");
            else
                label_add_friend->setString(text);
            break;
    }
    
    return true;
}

FriendScene::FriendScene(void)
{
    
}

FriendScene::~FriendScene(void)
{
    
}