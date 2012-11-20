#include "SceneManager.h"

SceneManager* SceneManager::pSharedManager = NULL;

void SceneManager::createDataManager()
{
    pUIManager      = UIManager::create();
    pDataManager    = DataManager::create();
    pNetworkManager = NetworkManager::create();
    pUIManager->init();
    pUIManager->setDataManager(pDataManager);
    
    userAccountKey = 0;
    hostAccountKey = 0;
}

SceneManager* SceneManager::create()
{
    pSharedManager = new SceneManager;
    return pSharedManager;
}

void SceneManager::setDataManager(BasisScene* pScene)
{
    pScene->setUIManager(pUIManager);
    pScene->setDataManager(pDataManager);
    pScene->setNetworkManager(pNetworkManager);
}

SceneManager* SceneManager::sharedSceneManager()
{
    return pSharedManager;
}

void SceneManager::setUserAccountKey(int _userAccountKey)
{
    userAccountKey = _userAccountKey;
}

int SceneManager::getUserAccountKey()
{
    return userAccountKey;
}

void SceneManager::setHostAccountKey(int _hostAccountKey)
{
    hostAccountKey = _hostAccountKey;
}

int SceneManager::getHostAccountKey()
{
    return hostAccountKey;
}

bool SceneManager::isFriendHome()
{
    return userAccountKey != hostAccountKey;
}

SceneManager::SceneManager(void)
{
    createDataManager();
}


SceneManager::~SceneManager(void)
{
}
