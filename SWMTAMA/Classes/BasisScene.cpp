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

