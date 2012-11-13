#include "LoginScene.h"
#include "InGameScene.h"

using namespace cocos2d;

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
        
        CC_BREAK_IF( !initBackground("greenhill.png", CCSize(WINSIZE_X, WINSIZE_Y)) );
        
        pUI = UIManager::create();
		pUI->init();
		pUI->setDataManager(pData);
		CC_BREAK_IF( !pUI->loadUI(this, LOGIN) );
        
        pNetwork = NetworkManager::create();
        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        
        userID = CCLabelTTF::create("ID", "Arial", 48);
        userID->setPosition(ccp(WINSIZE_X*0.75f, WINSIZE_Y*0.4f));
        addChild(userID);
        
        userPW = CCLabelTTF::create("PASSWORD", "Arial", 48);
        userPW->setPosition(ccp(WINSIZE_X*0.75f, WINSIZE_Y*0.20f));
        addChild(userPW);
        
        tfID = CCTextFieldTTF::textFieldWithPlaceHolder("", CCSizeMake(200, 20), kCCTextAlignmentLeft, "Arial", 12);
        tfID->setDelegate(this);
        tfID->setTag(LOGIN_TF_ID);
        addChild(tfID);
        
        tfPW = CCTextFieldTTF::textFieldWithPlaceHolder("", CCSizeMake(200, 20), kCCTextAlignmentLeft, "Arial", 12);
        tfPW->setDelegate(this);
        tfPW->setTag(LOGIN_TF_PW);
        addChild(tfPW);
        
        CCLog("LoginScene::init : start");
        
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
    userID->setString(s.data());
    
    CCDirector::sharedDirector()->replaceScene(InGameScene::scene());
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
    
    CCLog("LoginScene::callTryLogin");
}

void LoginScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = static_cast<CCTouch*>(pTouches->anyObject());
    
    if( CCRect::CCRectContainsPoint(userID->boundingBox(), touch->getLocation()) )
    {
        inputID();
    }
    
    if( CCRect::CCRectContainsPoint(userPW->boundingBox(), touch->getLocation()) )
    {
        inputPW();
    }
}

bool LoginScene::onTextFieldAttachWithIME(CCTextFieldTTF* sender)
{
    return false;
}

bool LoginScene::onTextFieldDetachWithIME(CCTextFieldTTF * sender)
{
    return false;
}

bool LoginScene::onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen)
{
    
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
                userPW->setString("PASSWORD");
            else
                userPW->setString(text);
            break;
    }
    
    CCLog(CCString::createWithFormat("LoginScene::onTextFieldInsertText : %s ", text)->getCString());
    return true;
}
















