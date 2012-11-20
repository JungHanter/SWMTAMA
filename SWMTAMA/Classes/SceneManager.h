#pragma once

#include "DataManager.h"
#include "UIManager.h"
#include "NetworkManager.h"
#include "BasisScene.h"

class SceneManager
{
private:
    static SceneManager* pSharedManager;
	DataManager*		pDataManager;
	UIManager*			pUIManager;
	NetworkManager*		pNetworkManager;

    int                 userAccountKey;
    int                 hostAccountKey;
    
private:
    void createDataManager();
    
public:
    void setDataManager(BasisScene* pScene);
    static SceneManager* create();
    static SceneManager* sharedSceneManager();
    void setUserAccountKey(int _userAccountKey);
    int getUserAccountKey();
    void setHostAccountKey(int _hostAccountKey);
    int getHostAccountKey();
    bool isFriendHome();
    
public:
	SceneManager(void);
	~SceneManager(void);
};

