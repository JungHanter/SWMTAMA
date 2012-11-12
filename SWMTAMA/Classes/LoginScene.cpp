#include "LoginScene.h"

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
        
        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        
        userID = CCLabelTTF::create("Click this text", "Arial", 48);
        userID->setPosition(ccp(WINSIZE_X/2, WINSIZE_Y-100));
        addChild(userID);
        
        textField = CCTextFieldTTF::textFieldWithPlaceHolder("", CCSizeMake(200, 20), kCCTextAlignmentLeft, "Arial", 12);
        textField->setDelegate(this);
        addChild(textField);
        
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

void LoginScene::testKeyboard()
{
    textField->attachWithIME();
    CCLog("LoginScene::testKeyboard : attach finished");
}

void LoginScene::testKeyboardResponse(float f)
{
    
}

void LoginScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = static_cast<CCTouch*>(pTouches->anyObject());
    
    if( CCRect::CCRectContainsPoint(userID->boundingBox(), touch->getLocation()) )
    {
        testKeyboard();
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
    userID->setString(text);
    CCLog("LoginScene::testKeyboard : set Label finished");
    return true;
}
















