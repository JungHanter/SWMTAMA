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

public:
    void setDataManager(DataManager *_pData);
    void setUIManager(UIManager *_pUI);
    void setNetworkManager(NetworkManager *_pNetwork);
    void setManagers(DataManager *_pData, UIManager *_pUI, NetworkManager *_pNetwork);
    DataManager* getDataManager();
    UIManager* getUIManager();
    NetworkManager* getNetworkManager();
};

