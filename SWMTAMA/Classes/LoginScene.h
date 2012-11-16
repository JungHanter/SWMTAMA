#pragma once
#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "BasisScene.h"
#include "Parameters.h"
#include "ActionList.h"

#define TAG_LOGINSCENE 101
#define TAG_LOGINLAYER LOGIN

enum LOGIN_INPUT { LOGIN_TF_ID=100, LOGIN_TF_PW };

class LoginScene : public BasisScene, public CCTextFieldDelegate
{
private:
    std::string buffer;
    cocos2d::CCLabelTTF *userID;
    cocos2d::CCLabelTTF *userPW;
    
    CCTextFieldTTF *tfID;
    CCTextFieldTTF *tfPW;
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
    CREATE_FUNC(LoginScene);
    void frame(float dt);
    
    void inputID();
    void inputPW();
    void testKeyboardResponse(float f);

public:
    virtual void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
    
public:
    void callTryLogin(cocos2d::CCObject *sender);
    
private:
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF* sender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * sender);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);
    virtual bool onTextFieldInsertText(CCTextFieldTTF* sender, const char* text, int nLen);
};

#endif