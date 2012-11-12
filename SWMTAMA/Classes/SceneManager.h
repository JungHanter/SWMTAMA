#pragma once

#include "DataManager.h"
#include "UIManager.h"
#include "NetworkManager.h"

class SceneManager
{
private:
	DataManager*		pDataManager;
	UIManager*			pUIManager;
	NetworkManager*		pNetworkManager;

public:
	SceneManager(void);
	~SceneManager(void);
};

