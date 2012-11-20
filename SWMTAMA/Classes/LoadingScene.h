#pragma once

#include "BasisScene.h"
using namespace cocos2d;

#define TAG_LOADINGSCENE 103

class LoadingScene : public BasisScene
{
private:
    cocos2d::CCLabelTTF      *labelLoading;
    static cocos2d::CCScene  *pScene;
    
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
    CREATE_FUNC(LoadingScene);
    void frame(float dt);
    static cocos2d::CCScene*   getLoadingScene();
    
public:
    virtual void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
    
public:
	LoadingScene(void);
	~LoadingScene(void);
};

