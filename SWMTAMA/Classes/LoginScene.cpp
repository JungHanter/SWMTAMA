#include "LoginScene.h"
#include "InGameScene.h"

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
        
        CC_BREAK_IF( !initBackground(this, "greenhill.png", CCSize(WINSIZE_X, WINSIZE_Y)) );
        
        pUI = UIManager::create();
		pUI->init();
		pUI->setDataManager(pData);
		CC_BREAK_IF( !pUI->loadUI(this, LOGIN) );
        
        pNetwork = NetworkManager::create();
        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        
        userID = CCLabelTTF::create("", "Arial", 48);
        userID->setPosition(ccp(WINSIZE_X*0.25f, WINSIZE_Y*0.8f));
        addChild(userID);
        
        userPW = CCLabelTTF::create("", "Arial", 48);
        userPW->setPosition(ccp(WINSIZE_X*0.25f, WINSIZE_Y*0.6f));
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
	std::string s = "";
    for (unsigned int i = 0; i < buffer->size(); i++)
		s += (*buffer)[i];
	CCLog("%s", s.data() );
    
    if( strcmp(response->getHttpRequest()->getTag(), "URL_LOGIN") == 0)
    {
        int delimIndex = s.find('|');
        string szAccountKey = s.substr(0, delimIndex);
        string szResult = s.substr(delimIndex+1);
        
        CCLog("%s Result=%s", szAccountKey.data(), szResult.data() );
        if( szResult.find("login") == 0 )
        {
            CCDirector::sharedDirector()->replaceScene(InGameScene::scene());
        }
    }
}

void LoginScene::callTryLogin(CCObject *sender)
{
    LoginScene *pLayer = ((LoginScene*)((CCMenuItemLabel*)sender)->getParent()->getParent());
    
    string body = "";
    body += "userid=";
    body += userID->getString();
    body += "&";
    body += "password=";
    body += userPW->getString();
    
    pLayer->getNetworkManager()->postMessage(URL_LOGIN, body.data(), this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_LOGIN");
    
//    pLayer->getNetworkManager()->postMessage(URL_CREATE_ANIMAL, "accountKey=0&animalKey=0&name=뽀비", this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_CREATE_ANIMAL");
//
//    pLayer->getNetworkManager()->postMessage(URL_ANIMAL_MANAGE, "sleep=80&poop=80&exp=80&fullness=80&health=80&joy=80&animalKey=100", this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_ANIMAL_MANAGE");
//    // success, fail
//    
//    pLayer->getNetworkManager()->postMessage(URL_CREATE_ID, "userid=1&password=1", this, callfuncND_selector(LoginScene::onHttpRequestCompleted), "URL_CREATE_ID");
//    // accountKey
    
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
            if( strcmp(text,"\n") == 0 )
                userID->setString("ID");
            else
                userID->setString(text);
            break;
            
        case LOGIN_TF_PW:
            if( strcmp(text,"\n") == 0 )
                userPW->setString("ID");
            else
                userPW->setString(text);
            break;
    }
    
    CCLog(CCString::createWithFormat("LoginScene::onTextFieldInsertText : %s %d", text, nLen)->getCString());
    return true;
}
















