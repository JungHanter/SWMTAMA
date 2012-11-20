#include "UIManager.h"
#include "InGameScene.h"
#include "LoginScene.h"
#include "LoadingScene.h"
#include "FriendScene.h"
#include "SceneManager.h"

using namespace cocos2d;
using namespace std;

UIManager* UIManager::create()
{
	return new UIManager;
}

bool UIManager::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI1_default.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI2_default.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI3_default.plist");
	return true;
}

bool UIManager::loadUI(cocos2d::CCLayer* pLayer, LAYERS layerEnum, cocos2d::CCLayer* pUILayer)
{
    CCMenu          *menuRequest;
	CCSpriteFrame	*frame;
	CCSprite		*sprite;
	CCLabelTTF		*label;
	CCPoint         point;
    CCMenuItemImage *itemImage;
    const int       UIORDER = 1000;

    CCLog("text0");
	int tag;
	switch(layerEnum)
	{
        case LOGIN:
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("input_frame.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.875f, WINSIZE_Y*0.7f));
            sprite->setScale(1.5f);
            sprite->setTag(FRAME_LOGIN_ID);
            pLayer->addChild(sprite);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("input_frame.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.875f, WINSIZE_Y*0.55f));
            sprite->setScale(1.5f);
            sprite->setTag(FRAME_LOGIN_PW);
            pLayer->addChild(sprite);
    
            label      = CCLabelTTF::create("ID", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.625f, WINSIZE_Y*0.7f));
            label->setAnchorPoint(ccp(0.f, 0.5f));
            label->setTag(LOGIN_TEXT_ID);
            label->setColor(ccBLACK);
            pLayer->addChild(label);
            
            label      = CCLabelTTF::create("PASSWORD", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.625f, WINSIZE_Y*0.55f));
            label->setAnchorPoint(ccp(0.f, 0.5f));
            label->setTag(LOGIN_TEXT_PW);
            label->setColor(ccBLACK);
            pLayer->addChild(label);
            
            label      = CCLabelTTF::create("", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.875f, WINSIZE_Y*0.55f));
            label->setTag(TEXT_PASSWORD);
            label->setColor(ccBLACK);
            pLayer->addChild(label);
            
            menuRequest = CCMenu::create();
            menuRequest->setPosition(CCPointZero);
            pLayer->addChild(menuRequest);
            
        {
            CCMenuItemSprite *itemSprite;
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("House_Login.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            itemSprite = CCMenuItemSprite::create(sprite, sprite, pLayer, menu_selector(LoginScene::callTryLogin));
            itemSprite->setPosition(ccp(WINSIZE_X*0.75f, WINSIZE_Y*0.25f));
            itemSprite->setScale(0.5f);
            itemSprite->setTag(BTN_HOUSE_LOGIN);
            menuRequest->addChild(itemSprite, UIORDER);
            
            
            frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("House_Create.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            itemSprite = CCMenuItemSprite::create(sprite, sprite, pLayer, menu_selector(LoginScene::callTryLogin));
            itemSprite->setPosition(ccp(WINSIZE_X*0.25f, WINSIZE_Y*0.25f));
            itemSprite->setScale(0.5f);
            itemSprite->setTag(BTN_HOUSE_CREATE);
            menuRequest->addChild(itemSprite, UIORDER);
            
            CCSprite    *pSprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blackboard.png"));
            pSprite->setPosition(ccp(WINSIZE_X*0.5f, WINSIZE_Y*0.5f));
            pSprite->setScaleX(WINSIZE_X*0.5f/pSprite->getContentSize().width);
            pSprite->setScaleY(WINSIZE_Y*0.5f/pSprite->getContentSize().height);
            pSprite->setTag(LOGIN_CREATE_BLACKBOARD);
            pSprite->setVisible(false);
            pLayer->addChild(pSprite, UIORDER-50);
            
            pSprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png"));
            pSprite->setPosition(ccp(WINSIZE_X*0.675f, WINSIZE_Y*0.3f));
            pSprite->setTag(LOGIN_CREATE_FRAME_OK);
            pSprite->setVisible(false);
            pLayer->addChild(pSprite, UIORDER-30);
            
            label      = CCLabelTTF::create("OK", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.675f, WINSIZE_Y*0.3f));
            label->setTag(LOGIN_CREATE_TEXT_OK);
            label->setVisible(false);
            pLayer->addChild(label, UIORDER);
            
            label      = CCLabelTTF::create("아이디 생성이 완료됐습니다!", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.5f, WINSIZE_Y*0.5f));
            label->setTag(LOGIN_CREATE_TEXT);
            label->setVisible(false);
            pLayer->addChild(label, UIORDER);
        }
            break;
        case FRIEND:
        {
            friendIndex = 0;
            CCSprite    *sprite = NULL;
            CCLabelTTF  *label = NULL;

            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_lion.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.2f, WINSIZE_Y*0.7f));
            sprite->setTag(THUMBNAIL);
            sprite->setVisible(false);
            pLayer->addChild(sprite);

            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("input_frame.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.2f, WINSIZE_Y*0.3f));
            sprite->setScale(1.5f);
            sprite->setTag(FRAME_NAME);
            pLayer->addChild(sprite);

//            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("input_frame.png"));
//            sprite->setPosition(ccp(WINSIZE_X*0.2f, WINSIZE_Y*0.3f));
//            sprite->setScaleX(0.5f);
//            sprite->setScaleY(0.3f);
//            sprite->setTag(FRAME_LEVEL);
//            pLayer->addChild(sprite);

            label      = CCLabelTTF::create("NAME", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.2f, WINSIZE_Y*0.3f));
            label->setTag(TEXT_NAME);
            label->setColor(ccBLACK);
            pLayer->addChild(label);

//            label      = CCLabelTTF::create("LEVEL", "Arial", 36);
//            label->setPosition(ccp(WINSIZE_X*0.2f, WINSIZE_Y*0.3f));
//            label->setTag(TEXT_LEVEL);
//            pLayer->addChild(label);

            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("prev.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.15f, WINSIZE_Y*0.15f));
            sprite->setScale(1.5f);
            sprite->setTag(PREV);
            pLayer->addChild(sprite);

            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("next.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.25f, WINSIZE_Y*0.15f));
            sprite->setScale(1.5f);
            sprite->setTag(NEXT);
            pLayer->addChild(sprite);

            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("House_Visit.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.55f, WINSIZE_Y*0.45f));
            sprite->setTag(HOME);
            pLayer->addChild(sprite);

            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.85f, WINSIZE_Y*0.35f));
            sprite->setScale(1.5f);
            sprite->setTag(BTN_ADD);
            pLayer->addChild(sprite);

            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.85f, WINSIZE_Y*0.15f));
            sprite->setScale(1.5f);
            sprite->setTag(BTN_HOME);
            pLayer->addChild(sprite);

            label      = CCLabelTTF::create("ADD FRIEND", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.85f, WINSIZE_Y*0.35f));
            label->setTag(TEXT_ADD);
            pLayer->addChild(label);

            label      = CCLabelTTF::create("GO HOME", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.85f, WINSIZE_Y*0.15f));
            label->setTag(TEXT_HOME);
            pLayer->addChild(label);

            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("default_image.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.2f, WINSIZE_Y*0.45f));
            sprite->setAnchorPoint(ccp(0.5f,0.f));
            sprite->setScale(0.8f);
            sprite->setTag(IMG_THUMBNAIL);
            pLayer->addChild(sprite);
            
            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("frame.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.2f, WINSIZE_Y*0.4f));
            sprite->setAnchorPoint(ccp(0.5f,0.f));
            sprite->setScale(1.f);
            sprite->setTag(IMG_FRAME_THUMBNAIL);
            pLayer->addChild(sprite);
            
            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blackboard.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.5f, WINSIZE_Y*0.5f));
            sprite->setScaleX(WINSIZE_X*0.5f/sprite->getContentSize().width);
            sprite->setScaleY(WINSIZE_Y*0.5f/sprite->getContentSize().height);
            sprite->setTag(ADD_BLACKBOARD);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-50);

            label   = CCLabelTTF::create("친구 추가하기", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.275f, WINSIZE_Y*0.675f));
            label->setAnchorPoint(ccp(0.f, 0.5f));
            label->setTag(ADD_TEXT);
            label->setVisible(false);
            pLayer->addChild(label, UIORDER);
            
            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.475f, WINSIZE_Y*0.3f));
            sprite->setTag(ADD_FRAME_OK);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-30);

            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.625f, WINSIZE_Y*0.3f));
            sprite->setTag(ADD_FRAME_CANCEL);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-30);
            
            label      = CCLabelTTF::create("OK", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.475f, WINSIZE_Y*0.3f));
            label->setTag(ADD_TEXT_OK);
            label->setVisible(false);
            pLayer->addChild(label, UIORDER);
            
            label      = CCLabelTTF::create("CANCEL", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.625f, WINSIZE_Y*0.3f));
            label->setTag(ADD_TEXT_CANCEL);
            label->setVisible(false);
            pLayer->addChild(label, UIORDER);
            
            sprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("input_frame.png"));
            sprite->setPosition(ccp(WINSIZE_X*0.5f, WINSIZE_Y*0.5f));
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            sprite->setScale(1.5f);
            sprite->setTag(ADD_FRAME_FRIEND);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER);
            
            cocos2d::CCLabelTTF *label_add_friend = CCLabelTTF::create("Input ID", "Arial", 36);
            label_add_friend->setPosition(ccp(WINSIZE_X*0.5f, WINSIZE_Y*0.5f));
            label_add_friend->setTag(ADD_LABEL_FRIEND);
            label_add_friend->setColor(ccBLACK);
            label_add_friend->setVisible(false);
            pLayer->addChild(label_add_friend, UIORDER);
            
            CCTextFieldTTF *tf_add_friend = CCTextFieldTTF::textFieldWithPlaceHolder("", CCSizeMake(200, 20), kCCTextAlignmentCenter, "Arial", 12);
            tf_add_friend->setPosition(ccp(WINSIZE_X*0.5f, WINSIZE_Y*0.5f));
            tf_add_friend->setDelegate((FriendScene*)pLayer);
            tf_add_friend->setTag(ADD_TF_FRIEND);
            tf_add_friend->setVisible(false);
            pLayer->addChild(tf_add_friend, UIORDER);
            
        }
            break;
            
        case INGAME:
            // ***
            create_animal_type = LION;
            hostAccountKey = SceneManager::sharedSceneManager()->getHostAccountKey();
            CCLog("text2");
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("option.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_OPTION_X, BUTTON_OPTION_Y));
            sprite->setScale(0.9f);
            sprite->setTag(BTN_OPTION);
            pUILayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_FRIEND_X, BUTTON_FRIEND_Y));
            sprite->setScale(0.9f);
            sprite->setTag(BTN_FRIENDS);
            pUILayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("House_Home.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_FRIEND_X, BUTTON_FRIEND_Y));
            sprite->setScale(0.25f);
            sprite->setTag(BTN_GO_HOME);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("teach.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_MULTI_PRACTICE_X, BUTTON_MULTI_PRACTICE_Y));
            sprite->setScale(1.6f);
            sprite->setTag(BTN_MULTI_PRACTICE);
            if( SceneManager::sharedSceneManager()->isFriendHome() )
                sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("create.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_CREATE_ANIMAL_X, BUTTON_CREATE_ANIMAL_Y));
            sprite->setScale(0.9f);
            sprite->setTag(BTN_CREATE_ANIMAL);
            if( SceneManager::sharedSceneManager()->isFriendHome() )
                sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            CCLog("*");
            // Blackboard
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blackboard.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(sprite->getContentSize().width/2, WINSIZE_Y/2));
            sprite->setTag(TRAINING_BLACKBOARD);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER-50);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("think.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(sprite->getContentSize().width/2, WINSIZE_Y/2));
            sprite->setTag(THINK_CLOUD);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-100);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_meat.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(sprite->getContentSize().width/2, WINSIZE_Y/2));
            sprite->setScale(16.f/15);
            sprite->setTag(ICON_MEAT);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-75);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("attachment.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(sprite->getContentSize().width/2, WINSIZE_Y/2));
            sprite->setTag(ICON_BLACKBOARD);
            sprite->setScale(0.9f);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-75);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_swing.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(sprite->getContentSize().width/2, WINSIZE_Y/2));
            sprite->setTag(ICON_SWING);
            sprite->setScale(0.8f);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-75);
CCLog("**");
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_running.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(sprite->getContentSize().width/2, WINSIZE_Y/2));
            sprite->setTag(ICON_RUNNING);
            sprite->setScale(0.8f);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-75);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_rope.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(sprite->getContentSize().width/2, WINSIZE_Y/2));
            sprite->setTag(ICON_ROPE);
            sprite->setScale(0.8f);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-75);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_0.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
            sprite->setTag(SPEAKER_DEFAULT);
            pUILayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_1.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
            sprite->setTag(SPEAKER_1);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_2.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
            sprite->setTag(SPEAKER_2);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
CCLog("***");
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_3.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
            sprite->setScale(0.5f);
            sprite->setTag(SPEAKER_3);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_x.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
            sprite->setScale(0.5f);
            sprite->setTag(SPEAKER_MUTE);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            CCLog("text1");
            label = CCLabelTTF::create(" Name", "", 60);
            label->setAnchorPoint(ccp(0, 0.5f));
            label->setPosition(ccp(20, WINSIZE_Y*0.9f));
            label->setTag(TRAIN_NAME);
            label->setVisible(false);
            pUILayer->addChild(label, UIORDER);

            label = CCLabelTTF::create("LEVEL  ", "", 36);
            label->setAnchorPoint(ccp(1, 0.5f));
            label->setPosition(ccp(WINSIZE_X/4 - 40, WINSIZE_Y*0.8f));
            label->setTag(TRAIN_LEVEL);
            label->setVisible(false);
            pUILayer->addChild(label, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("question.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setScale(0.5f);
            sprite->setAnchorPoint(ccp(1, 0.5f));
            //sprite->setPosition(ccp(0, WINSIZE_Y*0.63f));
            sprite->setTag(ICON_QUESTION);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-100);
            CCLog("****");
            menuRequest = CCMenu::create();
            menuRequest->setPosition(CCPointZero);
            menuRequest->setTag(MENU_TRAIN);
            menuRequest->setVisible(false);
            pUILayer->addChild(menuRequest, UIORDER);
            
            char* trainList[] = {"이름 인지하기", "다가오기", "밥 먹기", "약 먹기", "뛰기", "쉬기", "자기", "멈추기", "잠에서 깨기", "런닝머신 타기", "줄 넘기", "그네 타기"};
            int tagList[] = {TEXTBTN_NAME, ACTION_BASIC_COME, ACTION_BASIC_EAT, ACTION_BASIC_CURE, ACTION_BASIC_RUN, ACTION_BASIC_REST, ACTION_BASIC_SLEEP, ACTION_BASIC_STOP, ACTION_BASIC_WAKE, ACTION_TRAINING_RUNNING, ACTION_TRAINING_ROPE, ACTION_PLAYING_SWING};
            for( int i = 0; i < sizeof(trainList)/sizeof(char*); i++ )
            {
                CCLabelTTF *label = CCLabelTTF::create(trainList[i], "Arial", 30);
                CCMenuItemLabel *item = CCMenuItemLabel::create(label, pLayer, menu_selector(UIManager::callMenuTrain));
                item->setAnchorPoint(ccp(0, 0.5f));
                item->setTag(tagList[i]);
                item->setPosition(ccp(20, WINSIZE_Y*(0.72f-0.06f*i)));
                menuRequest->addChild(item, UIORDER);
            }
            
            char *statusList[] = {"경험치", "행복", "잠", "배부름", "건강", "똥"};
            
        {
            CCSprite    *pSprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blackboard.png"));
            CCMenuItemSprite *itemSprite = CCMenuItemSprite::create(pSprite, pSprite);
            itemSprite->setPosition(ccp(WINSIZE_X*0.625f, WINSIZE_Y*0.075f));
            itemSprite->setScaleX(WINSIZE_X*0.75f/itemSprite->getContentSize().width);
            itemSprite->setScaleY(WINSIZE_Y*0.15f/itemSprite->getContentSize().height);
            itemSprite->setTag(STATUS_BLACKBOARD);
            menuRequest->addChild(itemSprite, UIORDER-50);
        }
            for( int i = 0; i < 6; i++ )
            {
                CCLabelTTF  *label      = CCLabelTTF::create(statusList[i], "Arial", 36);
                CCMenuItemLabel *itemLabel = CCMenuItemLabel::create(label);
                itemLabel->setAnchorPoint(ccp(0, 0.5f));
                itemLabel->setPosition(ccp((WINSIZE_X/4)*(i%3+1) + 60, WINSIZE_Y*0.05f*(2-i/3)));
                itemLabel->setTag(STATUS_TEXT1+i);
                menuRequest->addChild(itemLabel, UIORDER);
                
                CCSprite    *pSprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("progressbar_frame.png"));
                CCMenuItemSprite *itemSprite = CCMenuItemSprite::create(pSprite, pSprite);
                itemSprite->setScale(0.25f);
                itemSprite->setAnchorPoint(ccp(0, 0.5f));
                itemSprite->setPosition(ccp((WINSIZE_X/4)*(i%3+1) + 160, WINSIZE_Y*0.05f*(2-i/3)));
                itemSprite->setTag(STATUS_PROGRESS_FRAME1+i);
                menuRequest->addChild(itemSprite, UIORDER);
                
                pSprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("progressbar.png"));
                itemSprite = CCMenuItemSprite::create(pSprite, pSprite);
                itemSprite->setScale(0.25f);
                itemSprite->setAnchorPoint(ccp(0, 0.5f));
                itemSprite->setPosition(ccp((WINSIZE_X/4)*(i%3+1) + 161, WINSIZE_Y*0.05f*(2-i/3)));
                itemSprite->setTag(STATUS_PROGRESS_BAR1+i);
                menuRequest->addChild(itemSprite, UIORDER);
            }
            CCLog("*****");
//            CCLog("text1.5");
//            CCMenu *pLayerCreate = CCMenu::create();
//            CCLog("text1.5");
//            pLayerCreate->setTag(LAYER_CREATE);
//            pLayerCreate->setVisible(false);
//            CCLog("text1.5");
//            pLayer->addChild(pLayerCreate);
//            
//            CCLog("text2");
            
        {
            CCSprite    *pSprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blackboard.png"));
            pSprite->setPosition(ccp(WINSIZE_X*0.5f, WINSIZE_Y*0.5f));
            pSprite->setScaleX(WINSIZE_X*0.5f/pSprite->getContentSize().width);
            pSprite->setScaleY(WINSIZE_Y*0.5f/pSprite->getContentSize().height);
            pSprite->setTag(CREATE_BLACKBOARD);
            pSprite->setVisible(false);
            pUILayer->addChild(pSprite, UIORDER-50);
        }
            
            label   = CCLabelTTF::create("동물 추가하기", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.275f, WINSIZE_Y*0.675f));
            label->setAnchorPoint(ccp(0.f, 0.5f));
            label->setTag(CREATE_TEXT);
            label->setVisible(false);
            pUILayer->addChild(label, UIORDER);
            
            CCLog("text2");
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_lion.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.35f, WINSIZE_Y*0.55f));
            sprite->setScaleX(160.f/sprite->getContentSize().width);
            sprite->setScaleY(160.f/sprite->getContentSize().height);
            sprite->setTag(CREATE_LION_IMG);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_elephant.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.35f, WINSIZE_Y*0.55f));
            sprite->setScaleX(160.f/sprite->getContentSize().width);
            sprite->setScaleY(160.f/sprite->getContentSize().height);
            sprite->setTag(CREATE_ELEPHANT_IMG);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_monkey.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.35f, WINSIZE_Y*0.55f));
            sprite->setScaleX(160.f/sprite->getContentSize().width);
            sprite->setScaleY(160.f/sprite->getContentSize().height);
            sprite->setTag(CREATE_MONKEY_IMG);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_squirrel.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.35f, WINSIZE_Y*0.55f));
            sprite->setScaleX(160.f/sprite->getContentSize().width);
            sprite->setScaleY(160.f/sprite->getContentSize().height);
            sprite->setTag(CREATE_SQUIRREL_IMG);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            CCLog("******");
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("prev.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.32f, WINSIZE_Y*0.4f));
            sprite->setScale(1.5f);
            sprite->setTag(CREATE_PREV);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("next.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.38f, WINSIZE_Y*0.4f));
            sprite->setScale(1.5f);
            sprite->setTag(CREATE_NEXT);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.475f, WINSIZE_Y*0.3f));
            sprite->setTag(CREATE_OK);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.625f, WINSIZE_Y*0.3f));
            sprite->setTag(CREATE_CLOSE);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            label   = CCLabelTTF::create("OK", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.475f, WINSIZE_Y*0.3f));
            label->setTag(CREATE_TEXT_OK);
            label->setVisible(false);
            pUILayer->addChild(label, UIORDER);
            
            label   = CCLabelTTF::create("CLOSE", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.625f, WINSIZE_Y*0.3f));
            label->setTag(CREATE_TEXT_CLOSE);
            label->setVisible(false);
            pUILayer->addChild(label, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("input_frame.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.6f, WINSIZE_Y*0.55f));
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            sprite->setScale(1.5f);
            sprite->setTag(CREATE_FRAME_NAME);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            cocos2d::CCLabelTTF *label_create_animal = CCLabelTTF::create("Input Name", "Arial", 32);
            label_create_animal->setPosition(ccp(WINSIZE_X*0.6f, WINSIZE_Y*0.55f));
            label_create_animal->setTag(CREATE_LABEL_NAME);
            label_create_animal->setVisible(false);
            label_create_animal->setColor(ccBLACK);
            pUILayer->addChild(label_create_animal, UIORDER);
            
            CCTextFieldTTF *tf_create_animal = CCTextFieldTTF::textFieldWithPlaceHolder("", CCSizeMake(200, 20), kCCTextAlignmentLeft, "Arial", 12);
            tf_create_animal->setDelegate((InGameScene*)pLayer);
            tf_create_animal->setTag(CREATE_TF_NAME);
            tf_create_animal->setVisible(false);
            pUILayer->addChild(tf_create_animal, UIORDER);
            
            
        {
            CCSprite    *pSprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blackboard.png"));
            pSprite->setPosition(ccp(WINSIZE_X*0.5f, WINSIZE_Y*0.5f));
            pSprite->setScaleX(WINSIZE_X*0.5f/pSprite->getContentSize().width);
            pSprite->setScaleY(WINSIZE_Y*0.5f/pSprite->getContentSize().height);
            pSprite->setTag(OPTION_BLACKBOARD);
            pSprite->setVisible(false);
            pUILayer->addChild(pSprite, UIORDER-50);
            
            pSprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png"));
            pSprite->setPosition(ccp(WINSIZE_X*0.525f, WINSIZE_Y*0.3f));
            pSprite->setScale(0.5f);
            pSprite->setTag(OPTION_FRAME_YES);
            pSprite->setVisible(false);
            pUILayer->addChild(pSprite, UIORDER-30);
            
            pSprite    = CCSprite::spriteWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png"));
            pSprite->setPosition(ccp(WINSIZE_X*0.675f, WINSIZE_Y*0.3f));
            pSprite->setScale(0.5f);
            pSprite->setTag(OPTION_FRAME_NO);
            pSprite->setVisible(false);
            pUILayer->addChild(pSprite, UIORDER-30);
            
            CCLabelTTF  *label      = CCLabelTTF::create("YES", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.525f, WINSIZE_Y*0.3f));
            label->setTag(OPTION_TEXT_YES);
            label->setVisible(false);
            pUILayer->addChild(label, UIORDER);
            
            label      = CCLabelTTF::create("NO", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.675f, WINSIZE_Y*0.3f));
            label->setTag(OPTION_TEXT_NO);
            label->setVisible(false);
            pUILayer->addChild(label, UIORDER);
            
            label      = CCLabelTTF::create("게임을 종료하시겠습니까?", "Arial", 36);
            label->setPosition(ccp(WINSIZE_X*0.5f, WINSIZE_Y*0.5f));
            label->setTag(OPTION_TEXT_QUESTION);
            label->setVisible(false);
            pUILayer->addChild(label, UIORDER);
        }
            CCLog("********");
            CCLog("text1");
            break;
	}
	return true;
}

void UIManager::setDataManager(DataManager* pDataManager)
{
	pData = pDataManager;
}

void UIManager::setQuestion(cocos2d::CCLayer *pLayer, int who)
{
    //pData->setPointedAnimal(hostAccountKey, who);
    pLayer->getChildByTag(ICON_QUESTION)->setVisible(true);
    
    CCLog(CCString::createWithFormat("setQuestion : %d is chosen.", who)->getCString());
}

void UIManager::setProgressBar(CCLayer* pLayer)
{
    if( SceneManager::sharedSceneManager()->isFriendHome() )
    {
        CCLog("UIManager::setProgressBar : invalid access");
        return;
    }
    ANIMALINDEX index = pData->getLastPointedAnimal();
    if( index.animalKey < 0 ) return;
    Animal *animal = pData->getAnimalByAnimalKey(index);
    
    STATUSINFO status = animal->getStatus();
    // temp - static numbering
    float ratio[6] = { ((float)status.exp)/100, ((float)status.joy)/100, ((float)status.sleep)/100, ((float)status.fullness)/100, ((float)status.health)/100, ((float)status.poop)/100 };
    // temp - static numbering
    for( int i = 0; i < 6; i++ )
        pLayer->getChildByTag(MENU_TRAIN)->getChildByTag(STATUS_PROGRESS_BAR1+i)->setScaleX(0.25f*ratio[i]);
}

void UIManager::setCreateAnimalType(CCLayer* pLayer)
{
    if( SceneManager::sharedSceneManager()->isFriendHome() )
    {
        CCLog("UIManager::setCreateAnimalType : invalid access");
        return;
    }
    switch (create_animal_type) {
        case LION:
            pLayer->getChildByTag(CREATE_LION_IMG)->setVisible(true);
            pLayer->getChildByTag(CREATE_ELEPHANT_IMG)->setVisible(false);
            pLayer->getChildByTag(CREATE_MONKEY_IMG)->setVisible(false);
            pLayer->getChildByTag(CREATE_SQUIRREL_IMG)->setVisible(false);
            break;
            
        case ELEPHANT:
            pLayer->getChildByTag(CREATE_LION_IMG)->setVisible(false);
            pLayer->getChildByTag(CREATE_ELEPHANT_IMG)->setVisible(true);
            pLayer->getChildByTag(CREATE_MONKEY_IMG)->setVisible(false);
            pLayer->getChildByTag(CREATE_SQUIRREL_IMG)->setVisible(false);
            break;
            
        case MONKEY:
            pLayer->getChildByTag(CREATE_LION_IMG)->setVisible(false);
            pLayer->getChildByTag(CREATE_ELEPHANT_IMG)->setVisible(false);
            pLayer->getChildByTag(CREATE_MONKEY_IMG)->setVisible(true);
            pLayer->getChildByTag(CREATE_SQUIRREL_IMG)->setVisible(false);
            break;
            
        case SQUIRREL:
            pLayer->getChildByTag(CREATE_LION_IMG)->setVisible(false);
            pLayer->getChildByTag(CREATE_ELEPHANT_IMG)->setVisible(false);
            pLayer->getChildByTag(CREATE_MONKEY_IMG)->setVisible(false);
            pLayer->getChildByTag(CREATE_SQUIRREL_IMG)->setVisible(true);
            break;
    }
    
}

void UIManager::frame(CCLayer* pLayer, float dt)
{
	switch(pLayer->getTag())
	{
	case INGAME:
        //if( SceneManager::sharedSceneManager()->isFriendHome() == false )
        //{
            if( pLayer->getChildByTag(THINK_CLOUD)->isVisible() )
            {
                static float ddt = 0;
                float theta = 0;
                ANIMALINDEX index = pData->getLastPointedAnimal();
                if( index.animalKey < 0 ) break;
                Animal* animal = pData->getAnimalByAnimalKey(index);
                ddt += dt/20;
                CCPoint eps = animal->getSprite()->getPosition();
                eps.x += pLayer->getChildByTag(THINK_CLOUD)->getContentSize().width/2;
                eps.y += pLayer->getChildByTag(THINK_CLOUD)->getContentSize().height/2;
                pLayer->getChildByTag(THINK_CLOUD)->setPosition(eps);

                eps.x += 90.f*cosf((ddt+theta)*3.141592);
                eps.y += 60.f*sinf((ddt+theta)*3.141592);
                pLayer->getChildByTag(ICON_BLACKBOARD)->setPosition(eps);
                theta += 0.33f;

                eps.x += 90.f*cosf((ddt+theta)*3.141592) - 90.f*cosf((ddt+theta-0.33f)*3.141592);
                eps.y += 60.f*sinf((ddt+theta)*3.141592) - 60.f*sinf((ddt+theta-0.33f)*3.141592);
                pLayer->getChildByTag(ICON_MEAT)->setPosition(eps);
                theta += 0.33f;

                eps.x += 90.f*cosf((ddt+theta)*3.141592) - 90.f*cosf((ddt+theta-0.33f)*3.141592);
                eps.y += 60.f*sinf((ddt+theta)*3.141592) - 60.f*sinf((ddt+theta-0.33f)*3.141592);
                pLayer->getChildByTag(ICON_SWING)->setPosition(eps);
                theta += 0.33f;

                eps.x += 90.f*cosf((ddt+theta)*3.141592) - 90.f*cosf((ddt+theta-0.33f)*3.141592);
                eps.y += 60.f*sinf((ddt+theta)*3.141592) - 60.f*sinf((ddt+theta-0.33f)*3.141592);
                pLayer->getChildByTag(ICON_RUNNING)->setPosition(eps);
                theta += 0.33f;

                eps.x += 90.f*cosf((ddt+theta)*3.141592) - 90.f*cosf((ddt+theta-0.33f)*3.141592);
                eps.y += 60.f*sinf((ddt+theta)*3.141592) - 60.f*sinf((ddt+theta-0.33f)*3.141592);
                pLayer->getChildByTag(ICON_ROPE)->setPosition(eps);
                theta += 0.33f;
            }
            {
                CCLayer* pUILayer = (CCLayer*)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMEUILAYER));
                if( pUILayer->getChildByTag(MENU_TRAIN)->isVisible() )
                {
                    setProgressBar(pUILayer);
                }
            }
        //}
		break;
	}
    
}

void UIManager::setSpeaker(CCLayer* pLayer, UI_INGAME speaker_only)
{
	pLayer->getChildByTag(SPEAKER_DEFAULT)->setVisible(speaker_only == SPEAKER_DEFAULT);
	pLayer->getChildByTag(SPEAKER_1)->setVisible(speaker_only == SPEAKER_1);
	pLayer->getChildByTag(SPEAKER_2)->setVisible(speaker_only == SPEAKER_2);
	pLayer->getChildByTag(SPEAKER_3)->setVisible(speaker_only == SPEAKER_3);
	pLayer->getChildByTag(SPEAKER_MUTE)->setVisible(speaker_only == SPEAKER_MUTE);
}

void UIManager::TouchesBegan(CCLayer* pLayer, CCSet *pTouches, CCEvent *pEvent)
{
	switch(pLayer->getTag())
	{
	case INGAME:
        // 오른쪽의 버튼 4개 선택시 스케일링 지원 - 옵션, 친구, 다중훈련, 동물 생성
		for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
		{
            CCLayer* pUILayer = (CCLayer*)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMEUILAYER));
			CCTouch *touch = static_cast<CCTouch*>(*it);
			if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(BTN_OPTION)->boundingBox(), touch->getLocation() ) )
				pUILayer->getChildByTag(BTN_OPTION)->setScale(0.99f);
			if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(BTN_FRIENDS)->boundingBox(), touch->getLocation() ) )
				pUILayer->getChildByTag(BTN_FRIENDS)->setScale(0.99f);
            // 다중 교육과 동물 생성은 친구집에서는 꺼줄 수도 있겠다.
			if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(BTN_MULTI_PRACTICE)->boundingBox(), touch->getLocation() ) )
				pUILayer->getChildByTag(BTN_MULTI_PRACTICE)->setScale(1.76f);
            if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(BTN_CREATE_ANIMAL)->boundingBox(), touch->getLocation() ) )
				pUILayer->getChildByTag(BTN_CREATE_ANIMAL)->setScale(0.99f);
		}
		break;
	}
}

void UIManager::callMenuTrain(CCObject *sender)
{
    if( SceneManager::sharedSceneManager()->isFriendHome() )
    {
        CCLog("UIManager::callMenuTrain : invalid access");
        return;
    }
    
    int actionTag = ((CCMenuItemLabel*)sender)->getTag();
    InGameScene *pLayer = ((InGameScene*)((CCMenuItemLabel*)sender)->getParent()->getParent()->getParent()->getChildByTag(TAG_INGAMELAYER));
    int who = pLayer->getDataManager()->getLastPointedAnimal().animalKey;
    if( who == -1 )
    {
        CCLog("UIManager::callMenuTrain : Wrong Last Pointed Animal");
        return;
    }
    
    switch (actionTag) {
        case TEXTBTN_NAME:
            //hanter
            pLayer->teachNameSpeeching(who);
            break;
            
        default:
            //hanter
            pLayer->teachSpeeching(who, actionTag);
            break;
    }
}

void UIManager::createAnimal(CCLayer *pLayer)
{
    if( SceneManager::sharedSceneManager()->isFriendHome() )
    {
        CCLog("UIManager::createAnimal : invalid access");
        return;
    }
    
    char animalName[256] = {0,};
    strcpy( animalName, ((CCLabelTTF*)(pLayer->getChildByTag(CREATE_LABEL_NAME)))->getString() );
    //hanter
    InGameScene *pMainLayer = (InGameScene*)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMELAYER));
    int animalKey = pMainLayer->makeAnimal(animalName);
    
    ANIMALINFO animalInfo( animalKey, create_animal_type, 0, 0, animalName );
    pData->makeDataFromAnimalInfo(hostAccountKey, animalInfo);
    CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMELAYER)->addChild(pData->getAnimalByAnimalKey(ANIMALINDEX(hostAccountKey, animalInfo.key))->getSprite());
    
    // URL CREATE ANIMAL
    pMainLayer->getNetworkManager()->postMessage(URL_CREATE_ANIMAL, CCString::createWithFormat("animalname=%s&accountKey=%d&animalKey=%d&animaltype=%d", animalName, hostAccountKey, animalKey, animalInfo.type)->getCString(), pMainLayer, callfuncND_selector(InGameScene::onHttpRequestCompleted), "URL_CREATE_ANIMAL");
    
    CCLog(CCString::createWithFormat("UIManager::createAnimal : %s", ((CCLabelTTF*)(pLayer->getChildByTag(CREATE_LABEL_NAME)))->getString())->getCString());
}

void UIManager::TouchesMoved(CCLayer* pLayer, CCSet *pTouches, CCEvent *pEvent)
{    
	switch(pLayer->getTag())
	{
	case INGAME:
		break;
	}
}

void UIManager::TouchesEnded(CCLayer* pLayer, CCSet *pTouches, CCEvent *pEvent)
{
	static int count;
    
	switch(pLayer->getTag())
	{
        case LOGIN:
        {
            CCTouch *touch = ((CCTouch*)pTouches->anyObject());
            if( pLayer->getChildByTag(LOGIN_CREATE_FRAME_OK)->isVisible() && pLayer->getChildByTag(LOGIN_CREATE_FRAME_OK)->boundingBox().containsPoint(touch->getLocation()) )
            {
                pLayer->getChildByTag(LOGIN_CREATE_BLACKBOARD)->setVisible(false);
                pLayer->getChildByTag(LOGIN_CREATE_FRAME_OK)->setVisible(false);
                pLayer->getChildByTag(LOGIN_CREATE_TEXT_OK)->setVisible(false);
                pLayer->getChildByTag(LOGIN_CREATE_TEXT)->setVisible(false);
            }
            break;
        }
        case FRIEND:
        {
            CCTouch *touch = ((CCTouch*)pTouches->anyObject());
            if( pLayer->getChildByTag(BTN_ADD)->boundingBox().containsPoint(touch->getLocation()) )
            {
                ((CCLabelTTF*)(pLayer->getChildByTag(ADD_LABEL_FRIEND)))->setString("Input ID");
                pLayer->getChildByTag(ADD_BLACKBOARD)->setVisible(true);
                pLayer->getChildByTag(ADD_TEXT)->setVisible(true);
                pLayer->getChildByTag(ADD_FRAME_OK)->setVisible(true);
                pLayer->getChildByTag(ADD_FRAME_CANCEL)->setVisible(true);
                pLayer->getChildByTag(ADD_TEXT_OK)->setVisible(true);
                pLayer->getChildByTag(ADD_TEXT_CANCEL)->setVisible(true);
                pLayer->getChildByTag(ADD_FRAME_FRIEND)->setVisible(true);
                pLayer->getChildByTag(ADD_LABEL_FRIEND)->setVisible(true);
                pLayer->getChildByTag(ADD_TF_FRIEND)->setVisible(true);
            }
            else if( pLayer->getChildByTag(ADD_FRAME_FRIEND)->isVisible() && pLayer->getChildByTag(ADD_FRAME_FRIEND)->boundingBox().containsPoint(touch->getLocation()) )
            {
                ((CCTextFieldTTF*)pLayer->getChildByTag(ADD_TF_FRIEND))->attachWithIME();
            }
            else if( pLayer->getChildByTag(ADD_TEXT_OK)->isVisible() && pLayer->getChildByTag(ADD_TEXT_OK)->boundingBox().containsPoint(touch->getLocation()) )
            {
                int myaccounyKey = SceneManager::sharedSceneManager()->getUserAccountKey();
                string newFriend = ((CCLabelTTF*)(pLayer->getChildByTag(ADD_LABEL_FRIEND)))->getString();
                ((FriendScene*)pLayer)->getNetworkManager()->postMessage(URL_ADD_FRIEND, CCString::createWithFormat("myaccountKey=%d&newFriend=%s",myaccounyKey, newFriend.data())->getCString(), pLayer, callfuncND_selector(FriendScene::onHttpRequestCompleted), "URL_ADD_FRIEND");
            }
            else if( pLayer->getChildByTag(ADD_TEXT_CANCEL)->isVisible() && pLayer->getChildByTag(ADD_TEXT_CANCEL)->boundingBox().containsPoint(touch->getLocation()) )
            {
                pLayer->getChildByTag(ADD_BLACKBOARD)->setVisible(false);
                pLayer->getChildByTag(ADD_TEXT)->setVisible(false);
                pLayer->getChildByTag(ADD_FRAME_OK)->setVisible(false);
                pLayer->getChildByTag(ADD_FRAME_CANCEL)->setVisible(false);
                pLayer->getChildByTag(ADD_TEXT_OK)->setVisible(false);
                pLayer->getChildByTag(ADD_TEXT_CANCEL)->setVisible(false);
                pLayer->getChildByTag(ADD_FRAME_FRIEND)->setVisible(false);
                pLayer->getChildByTag(ADD_LABEL_FRIEND)->setVisible(false);
                pLayer->getChildByTag(ADD_TF_FRIEND)->setVisible(false);
            }
            else if( pLayer->getChildByTag(NEXT)->boundingBox().containsPoint(touch->getLocation()) )
            {
                vector< pair<int, string> >* pFriendList = pData->getFriendList();
                if( pFriendList->size() > 0 )
                {
                    if( ++friendIndex >= pFriendList->size() )
                        friendIndex = 0;
                }
                pair<int, string> friendInfo = (*pFriendList)[friendIndex];
                ((CCLabelTTF*)(pLayer->getChildByTag(TEXT_NAME)))->setString(friendInfo.second.data());
                CCLog("UIManager::TouchesEnded : %d", friendIndex);
            }
            else if( pLayer->getChildByTag(PREV)->isVisible() && pLayer->getChildByTag(PREV)->boundingBox().containsPoint(touch->getLocation()) )
            {
                vector< pair<int, string> >* pFriendList = pData->getFriendList();
                if( pFriendList->size() > 0 )
                {
                    if( --friendIndex < 0 )
                        friendIndex = pFriendList->size()-1;
                }
                pair<int, string> friendInfo = (*pFriendList)[friendIndex];
                ((CCLabelTTF*)(pLayer->getChildByTag(TEXT_NAME)))->setString(friendInfo.second.data());
                CCLog("UIManager::TouchesEnded : %d", friendIndex);
            }
            else if( pLayer->getChildByTag(HOME)->isVisible() && pLayer->getChildByTag(HOME)->boundingBox().containsPoint(touch->getLocation()) )
            {
                pair<int, string> friendInfo = (*(pData->getFriendList()))[friendIndex];
                
//                CCScene* pInGameScene = InGameScene::getInGameScene();
//                if( !pInGameScene )
//                    CCLog("UIManager::TouchesEnded : HOME SO DANGER");
//                
//                pInGameLayer->resetScene(friendInfo.first);
                
                CCScene *pLoadingScene = LoadingScene::scene();
                CCDirector::sharedDirector()->popScene();
                CCDirector::sharedDirector()->pushScene(pLoadingScene);
                SceneManager::sharedSceneManager()->setHostAccountKey(friendInfo.first);
                hostAccountKey = friendInfo.first;
                ((LoadingScene*)pLayer)->getNetworkManager()->postMessage(URL_RECEIVE_ANIMALS, CCString::createWithFormat("accountKey=%d", friendInfo.first)->getCString(), (CCLayer*)(pLoadingScene->getChildByTag(LOADING)), callfuncND_selector(LoadingScene::onHttpRequestCompleted), "URL_RECEIVE_ANIMALS");
                
                
//                InGameScene* pInGameLayer = ((InGameScene*)InGameScene::getInGameScene()->getChildByTag(INGAME));
//                pInGameLayer->resetScene(friendInfo.first);
                
                CCLog("UIManager::TouchesEnded : HOME OK");
            }
            else if( pLayer->getChildByTag(BTN_HOME)->isVisible() && pLayer->getChildByTag(BTN_HOME)->boundingBox().containsPoint(touch->getLocation()) )
            {
//                CCScene* pInGameScene = InGameScene::getInGameScene();
//                InGameScene* pInGameLayer = ((InGameScene*)pInGameLayer->getChildByTag(INGAME));
//                pInGameLayer->resetScene(SceneManager::sharedSceneManager()->getUserAccountKey());
//                CCDirector::sharedDirector()->replaceScene(pInGameScene);
                CCDirector::sharedDirector()->popScene();
                InGameScene* pInGameLayer = ((InGameScene*)InGameScene::getInGameScene()->getChildByTag(INGAME));
                pInGameLayer->startVoiceRecognition();
                CCLog("UIManager::TouchesEnded : BTN_HOME OK");
            }
        }
            break;
	case INGAME:
		for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
		{
			CCTouch *touch = static_cast<CCTouch*>(*it);
			CCLayer *pUILayer = (CCLayer*)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMEUILAYER));
            
            // 0. pointed animal을 찾기위한 사전 작업
            // 은 getLastPointedAnimal로 의미가 없으며
            // 이후에 화면 스케일을 조정한 경우 터치 좌표를 구하기 위해 point를 연산한다.
            float scale = pLayer->getScale();
            CCPoint point = touch->getLocation();
            CCPoint location = pLayer->getPosition();
            point.x -= WINSIZE_X/2 + location.x;
            point.y -= WINSIZE_Y/2 + location.y;
            point.x /= scale;
            point.y /= scale;
            point.x += WINSIZE_X/2;
            point.y += WINSIZE_Y/2;
			ANIMALINDEX index = pData->getLastPointedAnimal();
            
            CCLog("TEMP5: %d, %d", index.accountKey, index.animalKey );
            
            // 1. 오른쪽 네 개 버튼에 대한 로직 제공
            if( pUILayer->getChildByTag(BTN_CREATE_ANIMAL)->isVisible() && pUILayer->getChildByTag(BTN_CREATE_ANIMAL)->boundingBox().containsPoint(touch->getLocation()) )
            {
                create_animal_type = LION;
                ((CCLabelTTF*)(pUILayer->getChildByTag(CREATE_LABEL_NAME)))->setString("Input Name");
                pUILayer->getChildByTag(CREATE_BLACKBOARD)->setVisible(true);
                pUILayer->getChildByTag(CREATE_OK)->setVisible(true);
                pUILayer->getChildByTag(CREATE_CLOSE)->setVisible(true);
                pUILayer->getChildByTag(CREATE_PREV)->setVisible(true);
                pUILayer->getChildByTag(CREATE_NEXT)->setVisible(true);
                pUILayer->getChildByTag(CREATE_FRAME_NAME)->setVisible(true);
                pUILayer->getChildByTag(CREATE_LABEL_NAME)->setVisible(true);
                pUILayer->getChildByTag(CREATE_TF_NAME)->setVisible(true);
                pUILayer->getChildByTag(CREATE_TEXT)->setVisible(true);
                pUILayer->getChildByTag(CREATE_TEXT_OK)->setVisible(true);
                pUILayer->getChildByTag(CREATE_TEXT_CLOSE)->setVisible(true);
                setCreateAnimalType(pUILayer);
            }
            else if( pUILayer->getChildByTag(BTN_MULTI_PRACTICE)->isVisible() && pUILayer->getChildByTag(BTN_MULTI_PRACTICE)->boundingBox().containsPoint(touch->getLocation()) )
            {
                
            }
            else if( pUILayer->getChildByTag(BTN_FRIENDS)->isVisible() && pUILayer->getChildByTag(BTN_FRIENDS)->boundingBox().containsPoint(touch->getLocation()) )
            {
                CCScene* pScene = FriendScene::getFriendScene();
                if( pScene == NULL )
                    pScene = FriendScene::scene();
                ((InGameScene*)pLayer)->stopVoiceRecognition();
                CCDirector::sharedDirector()->pushScene(pScene);
                
                
                return;
            }
            else if( pUILayer->getChildByTag(BTN_GO_HOME)->isVisible() && pUILayer->getChildByTag(BTN_GO_HOME)->boundingBox().containsPoint(touch->getLocation()) )
            {
                CCScene* pLoadingScene = LoadingScene::getLoadingScene();
                if( pLoadingScene == NULL )
                    pLoadingScene = LoadingScene::scene();
                pUILayer->getChildByTag(BTN_GO_HOME)->setVisible(false);
                pUILayer->getChildByTag(BTN_FRIENDS)->setVisible(true);
                SceneManager::sharedSceneManager()->setHostAccountKey(SceneManager::sharedSceneManager()->getUserAccountKey());
                ((LoadingScene*)pLayer)->getNetworkManager()->postMessage(URL_RECEIVE_ANIMALS, CCString::createWithFormat("accountKey=%d", SceneManager::sharedSceneManager()->getUserAccountKey())->getCString(), (CCLayer*)(pLoadingScene->getChildByTag(LOADING)), callfuncND_selector(LoadingScene::onHttpRequestCompleted), "URL_RECEIVE_ANIMALS");
                CCDirector::sharedDirector()->pushScene(pLoadingScene);
                return;
            }
            else if( pUILayer->getChildByTag(BTN_OPTION)->boundingBox().containsPoint(touch->getLocation()) )
            {
                pUILayer->getChildByTag(OPTION_BLACKBOARD)->setVisible(true);
                pUILayer->getChildByTag(OPTION_FRAME_YES)->setVisible(true);
                pUILayer->getChildByTag(OPTION_FRAME_NO)->setVisible(true);
                pUILayer->getChildByTag(OPTION_TEXT_YES)->setVisible(true);
                pUILayer->getChildByTag(OPTION_TEXT_NO)->setVisible(true);
                pUILayer->getChildByTag(OPTION_TEXT_QUESTION)->setVisible(true);
            }
            
            // 2. 캐릭터 생성 창 로직
            // 2-1. 캐릭터 생성 창이 보일 때 - 버튼이나 이름 입력 등의 프레임 처리
            if( pUILayer->getChildByTag(CREATE_BLACKBOARD)->isVisible() )
            {
                if( SceneManager::sharedSceneManager()->isFriendHome() == false )
                {
                    if( pUILayer->getChildByTag(CREATE_FRAME_NAME)->boundingBox().containsPoint(touch->getLocation()) )
                    {
                        ((CCTextFieldTTF*)(pUILayer->getChildByTag(CREATE_TF_NAME)))->attachWithIME();
                    }
                    if( pUILayer->getChildByTag(CREATE_OK)->boundingBox().containsPoint(touch->getLocation()) )
                    {
                        pUILayer->getChildByTag(CREATE_BLACKBOARD)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_OK)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_CLOSE)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_PREV)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_NEXT)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_LION_IMG)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_ELEPHANT_IMG)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_MONKEY_IMG)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_SQUIRREL_IMG)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_FRAME_NAME)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_LABEL_NAME)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_TF_NAME)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_TEXT)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_TEXT_OK)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_TEXT_CLOSE)->setVisible(false);
                        createAnimal(pUILayer);
                    }
                    if( pUILayer->getChildByTag(CREATE_CLOSE)->boundingBox().containsPoint(touch->getLocation()) )
                    {
                        pUILayer->getChildByTag(CREATE_BLACKBOARD)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_OK)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_CLOSE)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_PREV)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_NEXT)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_LION_IMG)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_ELEPHANT_IMG)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_MONKEY_IMG)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_SQUIRREL_IMG)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_FRAME_NAME)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_LABEL_NAME)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_TF_NAME)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_TEXT)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_TEXT_OK)->setVisible(false);
                        pUILayer->getChildByTag(CREATE_TEXT_CLOSE)->setVisible(false);
                    }
                    if( pUILayer->getChildByTag(CREATE_NEXT)->boundingBox().containsPoint(touch->getLocation()) )
                    {
                        CCLOG("No problem!");
                        switch (create_animal_type) {
                            case LION:
                                create_animal_type = ELEPHANT;
                                break;
                            
                            case ELEPHANT:
                                create_animal_type = MONKEY;
                                break;
                                
                            case MONKEY:
                                create_animal_type = SQUIRREL;
                                break;
                                
                            case SQUIRREL:
                                create_animal_type = LION;
                                break;
                        }
                        
                        setCreateAnimalType(pUILayer);
                    }
                    if( pUILayer->getChildByTag(CREATE_PREV)->boundingBox().containsPoint(touch->getLocation()) )
                    {
                        switch (create_animal_type) {
                            case LION:
                                create_animal_type = SQUIRREL;
                                break;
                                
                            case ELEPHANT:
                                create_animal_type = LION;
                                break;
                                
                            case MONKEY:
                                create_animal_type = ELEPHANT;
                                break;
                                
                            case SQUIRREL:
                                create_animal_type = MONKEY;
                                break;
                        }
                        setCreateAnimalType(pUILayer);
                    }
                }
            }
            else if( pUILayer->getChildByTag(OPTION_BLACKBOARD)->isVisible() )
            {
                if( pUILayer->getChildByTag(OPTION_FRAME_YES)->boundingBox().containsPoint(touch->getLocation()) )
                {
                    pUILayer->getChildByTag(OPTION_BLACKBOARD)->setVisible(false);
                    pUILayer->getChildByTag(OPTION_FRAME_YES)->setVisible(false);
                    pUILayer->getChildByTag(OPTION_FRAME_NO)->setVisible(false);
                    pUILayer->getChildByTag(OPTION_TEXT_YES)->setVisible(false);
                    pUILayer->getChildByTag(OPTION_TEXT_NO)->setVisible(false);
                    pUILayer->getChildByTag(OPTION_TEXT_QUESTION)->setVisible(false);
                    CCDirector::sharedDirector()->end();
                }
                if( pUILayer->getChildByTag(OPTION_FRAME_NO)->boundingBox().containsPoint(touch->getLocation()) )
                {
                    pUILayer->getChildByTag(OPTION_BLACKBOARD)->setVisible(false);
                    pUILayer->getChildByTag(OPTION_FRAME_YES)->setVisible(false);
                    pUILayer->getChildByTag(OPTION_FRAME_NO)->setVisible(false);
                    pUILayer->getChildByTag(OPTION_TEXT_YES)->setVisible(false);
                    pUILayer->getChildByTag(OPTION_TEXT_NO)->setVisible(false);
                    pUILayer->getChildByTag(OPTION_TEXT_QUESTION)->setVisible(false);
                }
            }
            // 2-3. 캐릭터 생성창이 보이지 않을 때, 즉 일반적인 로직... 근데 이 로직 별론데,,, 고칩시다.
            else
            {
                // 트레이닝 보드가 보이는데 트레이닝 보드 외부를 눌렀으면 트레이닝 보드를 꺼주세요.
                if( pUILayer->getChildByTag(TRAINING_BLACKBOARD)->isVisible() && !pUILayer->getChildByTag(TRAINING_BLACKBOARD)->boundingBox().containsPoint(touch->getLocation()) )
                {
                    if ( SceneManager::sharedSceneManager()->isFriendHome() == false )
                    {
                        //hanter
                        ((InGameScene*)pLayer)->stopTeachRecogntion();
                        
                        pUILayer->getChildByTag(TRAINING_BLACKBOARD)->setVisible(false);
                        pUILayer->getChildByTag(TRAIN_NAME)->setVisible(false);
                        pUILayer->getChildByTag(TRAIN_LEVEL)->setVisible(false);
                        pUILayer->getChildByTag(MENU_TRAIN)->setVisible(false);
                        pUILayer->getChildByTag(SPEAKER_3)->setPosition(SPEAKER_X, SPEAKER_Y);
                        pUILayer->getChildByTag(SPEAKER_MUTE)->setPosition(SPEAKER_X, SPEAKER_Y);
                        ((InGameScene*)pLayer)->startVoiceRecognition();
                    }
                }
                
                // 생각 구름이 보일 때, 즉 생각 구름에 대한 로직 처리
                if( index.animalKey < 0 )
                {
                    pLayer->getChildByTag(THINK_CLOUD)->setVisible(false);
                    pLayer->getChildByTag(ICON_MEAT)->setVisible(false);
                    pLayer->getChildByTag(ICON_BLACKBOARD)->setVisible(false);
                    pLayer->getChildByTag(ICON_SWING)->setVisible(false);
                    pLayer->getChildByTag(ICON_RUNNING)->setVisible(false);
                    pLayer->getChildByTag(ICON_ROPE)->setVisible(false);
                    continue;
                }
                Animal* animal = pData->getAnimalByAnimalKey(index);
                if( pLayer->getChildByTag(THINK_CLOUD)->isVisible() )
                {
                    if( pLayer->getChildByTag(ICON_MEAT)->boundingBox().containsPoint(point) )
                    {
                        animal->cancelAllMotions(0);
                        animal->addMotion(EAT, 5, true);
                        animal->addStatus(STATUS_FULLNESS, 20);
                        animal->addStatus(STATUS_POOP, 30);
                        animal->addStatus(STATUS_EXP, 10);
                    }
                    if( pLayer->getChildByTag(ICON_SWING)->boundingBox().containsPoint(point) )
                    {
                        animal->cancelAllMotions(0);
                        animal->addMotion(FUN_SWING, 5, true);
                        animal->addStatus(STATUS_JOY, 30);
                        animal->addStatus(STATUS_FULLNESS, -20);
                        animal->addStatus(STATUS_EXP, 20);
                    }
                    if( pLayer->getChildByTag(ICON_RUNNING)->boundingBox().containsPoint(point) )
                    {
                        animal->cancelAllMotions(0);
                        animal->addMotion(FUN_RUNNING, 5, true);
                        animal->addStatus(STATUS_JOY, 30);
                        animal->addStatus(STATUS_FULLNESS, -20);
                        animal->addStatus(STATUS_EXP, 20);
                    }
                    if( pLayer->getChildByTag(ICON_ROPE)->boundingBox().containsPoint(point) )
                    {
                        animal->cancelAllMotions(0);
                        animal->addMotion(FUN_ROPE, 5, true);
                        animal->addStatus(STATUS_JOY, 30);
                        animal->addStatus(STATUS_FULLNESS, -20);
                        animal->addStatus(STATUS_EXP, 20);
                    }
                    if( SceneManager::sharedSceneManager()->isFriendHome() == false )
                    {
                        if( pLayer->getChildByTag(ICON_BLACKBOARD)->boundingBox().containsPoint(point) )
                        {
                            //hanter
                            ((InGameScene*)pLayer)->stopVoiceRecognition();
                            
                            char szLevel[8];
                            sprintf( szLevel, "%d", animal->getAnimalInfo().level );
                            ((CCLabelTTF*)pUILayer->getChildByTag(TRAIN_NAME))->setString(animal->getAnimalInfo().name.data());
                            ((CCLabelTTF*)pUILayer->getChildByTag(TRAIN_LEVEL))->setString(szLevel);

                            pUILayer->getChildByTag(TRAINING_BLACKBOARD)->setVisible(!pUILayer->getChildByTag(TRAINING_BLACKBOARD)->isVisible());
                            pUILayer->getChildByTag(TRAIN_NAME)->setVisible(!pUILayer->getChildByTag(TRAIN_NAME)->isVisible());
                            pUILayer->getChildByTag(TRAIN_LEVEL)->setVisible(!pUILayer->getChildByTag(TRAIN_LEVEL)->isVisible());
                            pUILayer->getChildByTag(MENU_TRAIN)->setVisible(!pUILayer->getChildByTag(MENU_TRAIN)->isVisible());
                            pUILayer->getChildByTag(SPEAKER_3)->setPosition(SPEAKER_X, SPEAKER_Y+WINSIZE_Y*0.15f);
                            pUILayer->getChildByTag(SPEAKER_MUTE)->setPosition(SPEAKER_X, SPEAKER_Y+WINSIZE_Y*0.15f);
                            
                            ((InGameScene*)pLayer)->startTeachRecogntion();
                        }
                    }
                }

                if( animal->getSprite()->boundingBox().containsPoint(point) )
                {
                    pLayer->getChildByTag(THINK_CLOUD)->setVisible(true);
                    pLayer->getChildByTag(ICON_MEAT)->setVisible(true);
                    if( SceneManager::sharedSceneManager()->isFriendHome() == false )
                        pLayer->getChildByTag(ICON_BLACKBOARD)->setVisible(true);
                    pLayer->getChildByTag(ICON_SWING)->setVisible(true);
                    pLayer->getChildByTag(ICON_RUNNING)->setVisible(true);
                    pLayer->getChildByTag(ICON_ROPE)->setVisible(true);
                }
                else
                {
                    pLayer->getChildByTag(THINK_CLOUD)->setVisible(false);
                    pLayer->getChildByTag(ICON_MEAT)->setVisible(false);
                    if( SceneManager::sharedSceneManager()->isFriendHome() == false )
                        pLayer->getChildByTag(ICON_BLACKBOARD)->setVisible(false);
                    pLayer->getChildByTag(ICON_SWING)->setVisible(false);
                    pLayer->getChildByTag(ICON_RUNNING)->setVisible(false);
                    pLayer->getChildByTag(ICON_ROPE)->setVisible(false);
                }
            }
		}
        {
            CCLayer* pUILayer = (CCLayer*)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMEUILAYER));
            pUILayer->getChildByTag(BTN_OPTION)->setScale(0.9f);
            pUILayer->getChildByTag(BTN_FRIENDS)->setScale(0.9f);
            pUILayer->getChildByTag(BTN_MULTI_PRACTICE)->setScale(1.6f);
            pUILayer->getChildByTag(BTN_CREATE_ANIMAL)->setScale(0.9f);
        }
		break;
	}
}