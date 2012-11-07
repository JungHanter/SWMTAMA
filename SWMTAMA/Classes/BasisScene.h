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
};

