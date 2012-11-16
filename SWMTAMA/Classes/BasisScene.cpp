#include "BasisScene.h"

void BasisScene::setDataManager(DataManager *_pData)
{
    pData = _pData;
}

void BasisScene::setUIManager(UIManager *_pUI)
{
    pUI = _pUI;
}

void BasisScene::setNetworkManager(NetworkManager *_pNetwork)
{
    pNetwork = _pNetwork;
}

void BasisScene::setManagers(DataManager *_pData, UIManager *_pUI, NetworkManager *_pNetwork)
{
    pData = _pData;
    pUI = _pUI;
    pNetwork = _pNetwork;
}


DataManager* BasisScene::getDataManager()
{
    return pData;
}


UIManager* BasisScene::getUIManager()
{
    return pUI;
}

NetworkManager* BasisScene::getNetworkManager()
{
    return pNetwork;
}

bool BasisScene::initBackground(CCLayer* pLayer, const char *filename, cocos2d::CCSize winSize)
{
	CCSprite*	pBackground		= CCSprite::create(filename);
    CCSize		sizeBackground	= pBackground->getContentSize();
    
	if( !pBackground ) return false;
    
//	pBackground->setScaleX(GAME_SCALE*WINSIZE_X/sizeBackground.width);
//	pBackground->setScaleY(GAME_SCALE*WINSIZE_Y/sizeBackground.height);
    pBackground->setScaleX(GAME_SCALE*WINSIZE_X/sizeBackground.width);
	pBackground->setScaleY(GAME_SCALE*WINSIZE_Y/sizeBackground.height);
	pBackground->setPosition(ccp(WINSIZE_X/2, WINSIZE_Y/2));
    
	pLayer->addChild(pBackground, 0 );
    
	return true;
}
