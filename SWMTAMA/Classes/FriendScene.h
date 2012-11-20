#pragma once

#ifndef __FRIEND_SCENE__
#define __FFIEND_SCENE__

#include "BasisScene.h"

#define TAG_FRIENDSCENE 102

class FriendScene : public BasisScene, public CCTextFieldDelegate
{
private:
    cocos2d::CCLabelTTF *label_add_friend;
    CCTextFieldTTF *tf_add_friend;
    
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
    CREATE_FUNC(FriendScene);
    void frame(float dt);
    static cocos2d::CCScene* pScene;
    
public:
    virtual void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
    static cocos2d::CCScene* getFriendScene();
    
private:
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF* sender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * sender);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);
    virtual bool onTextFieldInsertText(CCTextFieldTTF* sender, const char* text, int nLen);
    
public:
	FriendScene(void);
	~FriendScene(void);
};

#endif /* defined(__SWMTAMA__FriendScene__) */
