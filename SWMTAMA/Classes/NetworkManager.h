#pragma once

#ifndef __NETWORK_MANAGER_H__
#define __NETWORK_MANAGER_H__

#include "cocos2d.h"
#include "../extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define URL_CREATE_ID           "http://swmtama.appspot.com/create_id.jsp"
#define URL_LOGIN				"http://swmtama.appspot.com/login.jsp"
#define URL_CREATE_ANIMAL       "http://swmtama.appspot.com/create_animal.jsp"
#define URL_ANIMAL_MANAGE       "http://swmtama.appspot.com/animal_manage.jsp"

//#define URL_REQUEST_FRIEND		"http://swmtama.appspot.com/req_FriendList.jsp"
//#define URL_REQUEST_THUMBNAIL	"http://swmtama.appspot.com/req_Thumbnail.jsp"
//#define URL_SEND_ACTION			"http://swmtama.appspot.com/send_act.jsp"
//#define URL_CHECK_ACTION		"http://swmtama.appspot.com/check_act.jsp"
//#define URL_REQUEST_BREED		"http://swmtama.appspot.com/req_breed.jsp"
//#define URL_CHECK_BREED			"http://swmtama.appspot.com/check_breed.jsp"
//#define URL_ANSWER_BREED		"http://swmtama.appspot.com/answer_breed.jsp"
//#define URL_RESPOND_BREED		"http://swmtama.appspot.com/resp_breed.jsp"

class NetworkManager : public cocos2d::CCLayer
{
public:

	void toExtensionsMainLayer(cocos2d::CCObject *sender);

	// Menu Callbacks
	void onMenuGetTestClicked(cocos2d::CCObject *sender);
	void onMenuPostTestClicked(cocos2d::CCObject *sender);
	void onMenuPostBinaryTestClicked(cocos2d::CCObject *sender);
	void send();

	// HTTP Response Callback
	void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);

	// Modules
	void postMessage(const char* url, const char* postData, CCLayer* pLayer, SEL_CallFuncND func, const char* tag = NULL);
    
public:
	static NetworkManager* create();

private:
	cocos2d::CCLabelTTF* m_labelStatusCode;

public:
	NetworkManager(void);
	~NetworkManager(void);
};

void runHttpClientTest();

#endif

