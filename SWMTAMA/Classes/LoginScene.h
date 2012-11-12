#pragma once
#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "BasisScene.h"
#include "Parameters.h"
#include "ActionList.h"

#define TAG_LOGINSCENE 101
#define TAG_LOGINLAYER LOGIN

class LoginScene : public BasisScene, public CCTextFieldDelegate
{
private:
    cocos2d::CCLabelTTF *userID;
    CCTextFieldTTF *textField;
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
    CREATE_FUNC(LoginScene);
    void frame(float dt);
    
    void testKeyboard();
    void testKeyboardResponse(float f);
    
private:
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF* sender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * sender);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);
    virtual bool onTextFieldInsertText(CCTextFieldTTF* sender, const char* text, int nLen);
};

#endif