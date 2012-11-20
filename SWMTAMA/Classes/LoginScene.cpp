#include "LoginScene.h"
#include "InGameScene.h"
#include "SceneManager.h"
#include "LoadingScene.h"

using namespace cocos2d;
using namespace cocos2d::extension;

CCScene* LoginScene::scene()
{
    CCScene *scene = NULL;
	do
	{
		scene = CCScene::create();
        scene->setTag(TAG_LOGINSCENE);
		CC_BREAK_IF(!scene);
        
		LoginScene *layer = LoginScene::create();
		CC_BREAK_IF(!layer);
        
		layer->setTag(LOGIN);
		scene->addChild(layer);
	} while(0);
    
	return scene;
}

bool LoginScene::init()
{
    bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());
        
        CC_BREAK_IF( !initBackground(this, "title_login.png", CCSize(WINSIZE_X, WINSIZE_Y)) );
        
        SceneManager::sharedSceneManager()->setDataManager(this);
        
		CC_BREAK_IF( !pUI->loadUI(this, LOGIN) );
        
        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        
        userID = CCLabelTTF::create("", "Arial", 48);
        userID->setPosition(ccp(WINSIZE_X*0.875f, WINSIZE_Y*0.7f));
        userID->setColor(ccBLACK);
        addChild(userID);
        
        userPW = CCLabelTTF::create("", "Arial", 48);
        userPW->setPosition(ccp(WINSIZE_X*0.875f, WINSIZE_Y*0.55f));
        userPW->setColor(ccBLACK);
        userPW->setVisible(false);
        addChild(userPW);
        
        tfID = CCTextFieldTTF::textFieldWithPlaceHolder("", CCSizeMake(200, 20), kCCTextAlignmentLeft, "Arial", 12);
        tfID->setDelegate(this);
        tfID->setTag(LOGIN_TF_ID);
        addChild(tfID);
        
        tfPW = CCTextFieldTTF::textFieldWithPlaceHolder("", CCSizeMake(200, 20), kCCTextAlignmentLeft, "Arial", 12);
        tfPW->setDelegate(this);
        tfPW->setTag(LOGIN_TF_PW);
        addChild(tfPW);
        
        buffer = "";

        CCLog("LoginScene::init : start");
        
        //setScale(2.f);
        
        bRet = true;
    } while(0);
    
	return bRet;
}

void LoginScene::frame(float dt)
{
//    CCTextFieldTTF *textField = (CCTextFieldTTF*)(getChildByTag(888));
//    CCLabelTTF *text = (CCTextFieldTTF*)(getChildByTag(999));
//    text->setString(textField->getString());
}

void LoginScene::inputID()
{
    tfID->attachWithIME();
    CCLog("LoginScene::inputID : attach finished");
}

void LoginScene::inputPW()
{
    tfPW->attachWithIME();
    CCLog("LoginScene::inputPW : attach finished");
}

void LoginScene::testKeyboardResponse(float f)
{
    
}

void LoginScene::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
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
	CCLog("LoginScene::onHttpRequestCompleted : buffer=%s", s.data() );
    
    if(strcmp(response->getHttpRequest()->getTag(), "URL_LOGIN") == 0)
    {
        int delimIndex = s.find('|');
        string szAccountKey = s.substr(0, delimIndex);
        string szResult = s.substr(delimIndex+1);
        
        if( szResult.find("login") == 0 )
        {
            SceneManager::sharedSceneManager()->setUserAccountKey(atoi(szAccountKey.data()));
            SceneManager::sharedSceneManager()->setHostAccountKey(atoi(szAccountKey.data()));
            
            CCScene* pScene = LoadingScene::scene();
            pNetwork->postMessage(URL_RECEIVE_ANIMALS, CCString::createWithFormat("accountKey=%s", szAccountKey.data())->getCString(), (CCLayer*)(pScene->getChildByTag(LOADING)), callfuncND_selector(LoadingScene::onHttpRequestCompleted), "URL_RECEIVE_ANIMALS");
            
            CCDirector::sharedDirector()->replaceScene(pScene);
            return;
        }
        CCLog("%s Result=%s", szAccountKey.data(), szResult.data() );
    }
    else if(strcmp(response->getHttpRequest()->getTag(), "URL_CREATE_ID") == 0)
    {
        getChildByTag(LOGIN_CREATE_BLACKBOARD)->setVisible(true);
        getChildByTag(LOGIN_CREATE_FRAME_OK)->setVisible(true);
        getChildByTag(LOGIN_CREATE_TEXT_OK)->setVisible(true);
        getChildByTag(LOGIN_CREATE_TEXT)->setVisible(true);
    }
}

void LoginScene::callTryLogin(CCObject *sender)
{
    int tag = ((CCMenuItemSprite*)sender)->getTag();
    LoginScene *pLayer = ((LoginScene*)((CCMenuItemLabel*)sender)->getParent()->getParent());
    
    string body = "";
    body += "userid=";
    body += userID->getString();
    body += "&";
    body += "password=";
    body += userPW->getString();
    
    switch (tag) {
        case BTN_HOUSE_LOGIN:
            pLayer->getNetworkManager()->postMessage(URL_LOGIN, body.data(), this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_LOGIN");
            break;
            
        case BTN_HOUSE_CREATE:
            pLayer->getNetworkManager()->postMessage(URL_CREATE_ID, body.data(), this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_CREATE_ID");
            break;
    }
    CCLog("body : %s",body.data());
    
    
//    // URL CREATE ID
//    pLayer->getNetworkManager()->postMessage(URL_CREATE_ID, "userid=plulena&password=1234", this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_CREATE_ID");

//    // URL RECEIVE ANIMAL LIST
//    pLayer->getNetworkManager()->postMessage(URL_RECEIVE_ANIMALS, "accountKey=1", this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_RECEIVE_ANIMALS");
//    
//    // URL RECEIVE FRIEND LIST
//    pLayer->getNetworkManager()->postMessage(URL_RECEIVE_FRIENDS, "accountKey=1", this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_RECEIVE_FRIENDS");
//    
//    // URL ANIMAL MANAGE
//    pLayer->getNetworkManager()->postMessage(URL_ANIMAL_MANAGE, "level=3&sleep=80&poop=80&exp=80&fullness=80&health=80&joy=80&animalKey=1", this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_ANIMAL_MANAGE");
//    
//    // URL ADD FRIEND
//    pLayer->getNetworkManager()->postMessage(URL_ADD_FRIEND, "myaccountKey=1&newFriend=2", this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_ADD_FRIEND");
    
    CCLog("LoginScene::callTryLogin");
}

void LoginScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = static_cast<CCTouch*>(pTouches->anyObject());
    
    float scale = getScale();
    CCPoint point = touch->getLocation();
    CCPoint location = getPosition();
    point.x -= WINSIZE_X/2 + location.x;
    point.y -= WINSIZE_Y/2 + location.y;
    point.x /= scale;
    point.y /= scale;
    point.x += WINSIZE_X/2;
    point.y += WINSIZE_Y/2;
    
    
    CCLog("%f %f", point.x, point.y);
    
    if( CCRect::CCRectContainsPoint(getChildByTag(FRAME_LOGIN_ID)->boundingBox(), point) )
    {
        inputID();
    }
    
    if( CCRect::CCRectContainsPoint(getChildByTag(FRAME_LOGIN_PW)->boundingBox(), point) )
    {
        inputPW();
    }
    
//    CCPoint damage = getPosition();
//    
//    if( fabsf((touch->getLocation().y-375.f)/(touch->getLocation().x-640.f)) >= 750.f/1280 )
//    {
//        if( touch->getLocation().y > 375.f )
//            damage.y -= 10;
//        else
//            damage.y += 10;
//    }
//    else
//    {
//        if( touch->getLocation().x > 640.f )
//            damage.x -= 10;
//        else
//            damage.x += 10;
//    }
//    
//    setPosition(damage);
    
    
}

void LoginScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
//    float scale = getScale();
//    if( pTouches->count() > 1)
//    {
//        static float fPrevGap = 0.f;
//        CCSetIterator it = pTouches->begin();
//        CCTouch *touch1 = static_cast<CCTouch*>(*it++);
//        CCTouch *touch2 = static_cast<CCTouch*>(*it);
//        CCPoint point1 = touch1->getLocation();
//        CCPoint point2 = touch2->getLocation();
//        
//        float fGap = sqrtf((point2.x-point1.x)*(point2.x-point1.x)+(point2.y-point1.y)*(point2.y-point1.y));
//        if( fGap > fPrevGap )
//        {
//            if( scale < 2.f )
//                scale *= 1.03f;
//        }
//        else
//        {
//            //if( scale > 0.6f )
//                scale /= 1.03f;
//        }
//        fPrevGap = fGap;
//        
//        CCPoint location = getPosition();
//        float left      = (-WINSIZE_X/2-location.x)/scale + WINSIZE_X/2;
//        float top       = (WINSIZE_Y/2-location.y)/scale + WINSIZE_Y/2;
//        float right     = (WINSIZE_X/2-location.x)/scale + WINSIZE_X/2;
//        float bottom    = (-WINSIZE_Y/2-location.y)/scale + WINSIZE_Y/2;
//        
//        CCLog("[%4.f,%4.f,%4.f,%4.f]", left, top, right, bottom);
//        
//        
//        
//        // 백그라운드 받아와서 처리해야함. 원래는
//        if( !(left < -0.5f*WINSIZE_X ||
//              right > 1.5f*WINSIZE_X ||
//              bottom < -0.5f*WINSIZE_Y ||
//              top > 1.5f*WINSIZE_Y) )
//        {
//            setScale(scale);
//        }
//    }
//    else
//    {
//        CCTouch *touch = static_cast<CCTouch*>(pTouches->anyObject());
//        
//        CCPoint ptGap = touch->getLocation();
//        ptGap.x -= touch->getPreviousLocation().x;
//        ptGap.y -= touch->getPreviousLocation().y;
//        
//        CCPoint damage = getPosition();
//        
//        damage.x += ptGap.x;
//        damage.y += ptGap.y;
//        
//        //CCPoint location = getPosition();
//        float left      = (-WINSIZE_X/2-damage.x)/scale + WINSIZE_X/2;
//        float top       = (WINSIZE_Y/2-damage.y)/scale + WINSIZE_Y/2;
//        float right     = (WINSIZE_X/2-damage.x)/scale + WINSIZE_X/2;
//        float bottom    = (-WINSIZE_Y/2-damage.y)/scale + WINSIZE_Y/2;
//        
//        CCLog("[%4.f,%4.f,%4.f,%4.f]", left, top, right, bottom);
//        
//        
//        
//        // 백그라운드 받아와서 처리해야함. 원래는
//        if( !(left < -0.5f*WINSIZE_X ||
//              right > 1.5f*WINSIZE_X ||
//              bottom < -0.5f*WINSIZE_Y ||
//              top > 1.5f*WINSIZE_Y) )
//        {
//            setPosition(damage);
//        }
//    }
}

void LoginScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    //setScale(1.f);
}

bool LoginScene::onTextFieldAttachWithIME(CCTextFieldTTF* sender)
{
    switch (sender->getTag()) {
        case LOGIN_TF_ID:
            userID->setString("");
            break;
            
        case LOGIN_TF_PW:
            userPW->setString("");
            break;
    }
    CCLog("LoginScene::onTextFieldAttachWithIME");
    return false;
}

bool LoginScene::onTextFieldDetachWithIME(CCTextFieldTTF * sender)
{
    switch (sender->getTag()) {
        case LOGIN_TF_ID:
            break;
            
        case LOGIN_TF_PW:
            break;
    }
    CCLog("LoginScene::onTextFieldDetachWithIME");
    return false;
}

bool LoginScene::onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen)
{
    switch (pSender->getTag()) {
        case LOGIN_TF_ID:
            break;
            
        case LOGIN_TF_PW:
            break;
    }
    CCLog(CCString::createWithFormat("LoginScene::onTextFieldDeleteBackward : %s ", delText)->getCString());
    return false;
}

bool LoginScene::onTextFieldInsertText(CCTextFieldTTF* sender, const char* text, int nLen)
{
    switch (sender->getTag()) {
        case LOGIN_TF_ID:
            userID->setString(text);
            break;
            
        case LOGIN_TF_PW:
            userPW->setString(text);
            string s ="";
            for( int i = 0; i < strlen(text); i++)
                s += '*';
            ((CCLabelTTF*)getChildByTag(TEXT_PASSWORD))->setString(s.data());
            break;
    }
    
    CCLog(CCString::createWithFormat("LoginScene::onTextFieldInsertText : %s %d", text, nLen)->getCString());
    return true;
}
















