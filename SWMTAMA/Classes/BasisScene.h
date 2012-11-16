#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "DataManager.h"
#include "UIManager.h"
#include "NetworkManager.h"

class BasisScene : public cocos2d::CCLayer
{
protected:
	DataManager*		pData;
	UIManager*			pUI;
	NetworkManager*		pNetwork;

protected:
    virtual void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data) {}
    
public:
    void setDataManager(DataManager *_pData);
    void setUIManager(UIManager *_pUI);
    void setNetworkManager(NetworkManager *_pNetwork);
    void setManagers(DataManager *_pData, UIManager *_pUI, NetworkManager *_pNetwork);
    DataManager* getDataManager();
    UIManager* getUIManager();
    NetworkManager* getNetworkManager();
    bool initBackground(cocos2d::CCLayer* pLayer, const char *filename, cocos2d::CCSize winSize);
};

