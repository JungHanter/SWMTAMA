#include "UIManager.h"
#include "InGameScene.h"
#include "LoginScene.h"

using namespace cocos2d;
using namespace std;

UIManager* UIManager::create()
{
	return new UIManager;
}

bool UIManager::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI_default.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LOGIN_default.plist");
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
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("11624_491f048fdd143.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.25f, WINSIZE_Y*0.8f));
            sprite->setScaleX(0.5f);
            sprite->setScaleY(0.3f);
            sprite->setTag(FRAME_LOGIN_ID);
            pLayer->addChild(sprite);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("11624_491f048fdd143.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.25f, WINSIZE_Y*0.6f));
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            sprite->setScaleX(0.5f);
            sprite->setScaleY(0.3f);
            sprite->setTag(FRAME_LOGIN_PW);
            pLayer->addChild(sprite);
    
            menuRequest = CCMenu::create();
            menuRequest->setPosition(CCPointZero);
            pLayer->addChild(menuRequest);
            
            itemImage = CCMenuItemImage::create("House.png", "House.png", pLayer, menu_selector(LoginScene::callTryLogin));
            itemImage->setPosition(ccp(WINSIZE_X*0.75f, WINSIZE_Y*0.45f));
            itemImage->setScale(1.9f);
            itemImage->setTag(BTN_HOUSE);
            menuRequest->addChild(itemImage, UIORDER);
            
            break;
        case INGAME:
            // ***
            create_animal_type = LION;
            CCLog("text2");
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("option.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_OPTION_X, BUTTON_OPTION_Y));
            sprite->setTag(BTN_OPTION);
            pUILayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_FRIEND_X, BUTTON_FRIEND_Y));
            sprite->setTag(BTN_FRIENDS);
            pUILayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("multi_practice.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_MULTI_PRACTICE_X, BUTTON_MULTI_PRACTICE_Y));
            sprite->setTag(BTN_MULTI_PRACTICE);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("plus.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_CREATE_ANIMAL_X, BUTTON_CREATE_ANIMAL_Y));
            sprite->setTag(BTN_CREATE_ANIMAL);
            pUILayer->addChild(sprite, UIORDER);
            
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

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_blackboard.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(sprite->getContentSize().width/2, WINSIZE_Y/2));
            sprite->setTag(ICON_BLACKBOARD);
            sprite->setScale(1.6f);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-75);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_swing.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(sprite->getContentSize().width/2, WINSIZE_Y/2));
            sprite->setTag(ICON_SWING);
            sprite->setScale(0.8f);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-75);

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

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_3.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
            sprite->setTag(SPEAKER_3);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_x.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
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
            
            menuRequest = CCMenu::create();
            menuRequest->setPosition(CCPointZero);
            menuRequest->setTag(MENU_TRAIN);
            menuRequest->setVisible(false);
            pUILayer->addChild(menuRequest, UIORDER);
            
            char* trainList[] = {"이름 인지하기", "밥 먹기", "뛰기", "쉬기", "자기", "멈추기", "런닝머신 타기", "줄 넘기", "그네 타기"};
            int tagList[] = {TEXTBTN_NAME, ACTION_BASIC_EAT, ACTION_BASIC_RUN, ACTION_BASIC_REST, ACTION_BASIC_SLEEP, ACTION_BASIC_STOP, ACTION_TRAINING_RUNNING, ACTION_TRAINING_ROPE, ACTION_PLAYING_SWING};
            for( int i = 0; i < sizeof(trainList)/sizeof(char*); i++ )
            {
                CCLabelTTF *label = CCLabelTTF::create(trainList[i], "Arial", 36);
                CCMenuItemLabel *item = CCMenuItemLabel::create(label, pLayer, menu_selector(UIManager::callMenuTrain));
                item->setAnchorPoint(ccp(0, 0.5f));
                item->setTag(tagList[i]);
                item->setPosition(ccp(20, WINSIZE_Y*(0.7f-0.07f*i)));
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
            CCLog("text2");
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_lion.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.35f, WINSIZE_Y*0.6f));
            sprite->setScaleX(160.f/sprite->getContentSize().width);
            sprite->setScaleY(160.f/sprite->getContentSize().height);
            sprite->setTag(CREATE_LION_IMG);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_elephant.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.35f, WINSIZE_Y*0.6f));
            sprite->setScaleX(160.f/sprite->getContentSize().width);
            sprite->setScaleY(160.f/sprite->getContentSize().height);
            sprite->setTag(CREATE_ELEPHANT_IMG);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            CCLog("text2");
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_monkey.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.35f, WINSIZE_Y*0.6f));
            sprite->setScaleX(160.f/sprite->getContentSize().width);
            sprite->setScaleY(160.f/sprite->getContentSize().height);
            sprite->setTag(CREATE_MONKEY_IMG);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            CCLog("text3");
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_squirrel.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.35f, WINSIZE_Y*0.6f));
            sprite->setScaleX(160.f/sprite->getContentSize().width);
            sprite->setScaleY(160.f/sprite->getContentSize().height);
            sprite->setTag(CREATE_SQUIRREL_IMG);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("prev.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.32f, WINSIZE_Y*0.35f));
            sprite->setScale(1.5f);
            sprite->setTag(CREATE_PREV);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("next.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.38f, WINSIZE_Y*0.35f));
            sprite->setScale(1.5f);
            sprite->setTag(CREATE_NEXT);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.525f, WINSIZE_Y*0.3f));
            sprite->setScale(0.5f);
            sprite->setTag(CREATE_OK);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eraser.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.675f, WINSIZE_Y*0.3f));
            sprite->setScale(0.5f);
            sprite->setTag(CREATE_CLOSE);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("11624_491f048fdd143.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.6f, WINSIZE_Y*0.6f));
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            sprite->setScaleX(0.5f);
            sprite->setScaleY(0.3f);
            sprite->setTag(CREATE_FRAME_NAME);
            sprite->setVisible(false);
            pUILayer->addChild(sprite, UIORDER);
            
            cocos2d::CCLabelTTF *label_create_animal = CCLabelTTF::create("Input Name", "Arial", 48);
            label_create_animal->setPosition(ccp(WINSIZE_X*0.6f, WINSIZE_Y*0.6f));
            label_create_animal->setTag(CREATE_LABEL_NAME);
            label_create_animal->setVisible(false);
            pUILayer->addChild(label_create_animal, UIORDER);
            
            CCTextFieldTTF *tf_create_animal = CCTextFieldTTF::textFieldWithPlaceHolder("", CCSizeMake(200, 20), kCCTextAlignmentLeft, "Arial", 12);
            tf_create_animal->setDelegate((InGameScene*)pLayer);
            tf_create_animal->setTag(CREATE_TF_NAME);
            tf_create_animal->setVisible(false);
            pUILayer->addChild(tf_create_animal, UIORDER);
            
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
    int accountKey = 0;
    pData->setPointedAnimal(accountKey, who);
//    ((CCLabelTTF*)(pLayer->getChildByTag(9999)))->setString(CCString::createWithFormat("setQuestion : %d is chosen.", who)->getCString());
    CCLog(CCString::createWithFormat("setQuestion : %d is chosen.", who)->getCString());
    pLayer->getChildByTag(ICON_QUESTION)->setVisible(true);
}

void UIManager::setProgressBar(CCLayer* pLayer)
{
    int accountKey = 0;
    int animalKey = pData->getLastPointedAnimal(accountKey);
    if( animalKey < 0 ) return;
    Animal *animal = pData->getAnimalByAnimalKey(accountKey, animalKey);
    
    STATUSINFO status = animal->getStatus();
    // temp - static numbering
    float ratio[6] = { ((float)status.exp)/100, ((float)status.joy)/100, ((float)status.sleep)/100, ((float)status.fullness)/100, ((float)status.health)/100, ((float)status.poop)/100 };
    // temp - static numbering
    for( int i = 0; i < 6; i++ )
        pLayer->getChildByTag(MENU_TRAIN)->getChildByTag(STATUS_PROGRESS_BAR1+i)->setScaleX(0.25f*ratio[i]);
}

void UIManager::setCreateAnimalType(CCLayer* pLayer)
{
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
		if( pLayer->getChildByTag(THINK_CLOUD)->isVisible() )
		{
			static float ddt = 0;
			float theta = 0;
			int accountKey = 0;
			int animalKey = pData->getLastPointedAnimal(accountKey);
			if( animalKey < 0 ) break;
			Animal* animal = pData->getAnimalByAnimalKey(accountKey, animalKey);
			ddt += dt/20;
			CCPoint eps = animal->getSprite()->getPosition();
			eps.x += pLayer->getChildByTag(THINK_CLOUD)->getContentSize().width/2;
			eps.y += pLayer->getChildByTag(THINK_CLOUD)->getContentSize().height/2;
			pLayer->getChildByTag(THINK_CLOUD)->setPosition(eps);

			eps.x += 90.f*cosf((ddt+theta)*3.141592);
			eps.y += 60.f*sinf((ddt+theta)*3.141592);
			pLayer->getChildByTag(ICON_MEAT)->setPosition(eps);
			theta += 0.25f;

			eps.x += 90.f*cosf((ddt+theta)*3.141592) - 90.f*cosf((ddt+theta-0.25f)*3.141592);
			eps.y += 60.f*sinf((ddt+theta)*3.141592) - 60.f*sinf((ddt+theta-0.25f)*3.141592);
			pLayer->getChildByTag(ICON_BLACKBOARD)->setPosition(eps);
			theta += 0.25f;

			eps.x += 90.f*cosf((ddt+theta)*3.141592) - 90.f*cosf((ddt+theta-0.25f)*3.141592);
			eps.y += 60.f*sinf((ddt+theta)*3.141592) - 60.f*sinf((ddt+theta-0.25f)*3.141592);
			pLayer->getChildByTag(ICON_SWING)->setPosition(eps);
			theta += 0.25f;

			eps.x += 90.f*cosf((ddt+theta)*3.141592) - 90.f*cosf((ddt+theta-0.25f)*3.141592);
			eps.y += 60.f*sinf((ddt+theta)*3.141592) - 60.f*sinf((ddt+theta-0.25f)*3.141592);
			pLayer->getChildByTag(ICON_RUNNING)->setPosition(eps);
			theta += 0.25f;

			eps.x += 90.f*cosf((ddt+theta)*3.141592) - 90.f*cosf((ddt+theta-0.25f)*3.141592);
			eps.y += 60.f*sinf((ddt+theta)*3.141592) - 60.f*sinf((ddt+theta-0.25f)*3.141592);
			pLayer->getChildByTag(ICON_ROPE)->setPosition(eps);
			theta += 0.25f;
		}
        {
            CCLayer* pUILayer = (CCLayer*)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMEUILAYER));
            if( pUILayer->getChildByTag(MENU_TRAIN)->isVisible() )
            {
                setProgressBar(pUILayer);
            }
        }
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
		for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
		{
            CCLayer* pUILayer = (CCLayer*)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMEUILAYER));
			CCTouch *touch = static_cast<CCTouch*>(*it);
			if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(BTN_OPTION)->boundingBox(), touch->getLocation() ) )
				pUILayer->getChildByTag(BTN_OPTION)->setScale(1.1f);
			if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(BTN_FRIENDS)->boundingBox(), touch->getLocation() ) )
				pUILayer->getChildByTag(BTN_FRIENDS)->setScale(1.1f);
			if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(BTN_MULTI_PRACTICE)->boundingBox(), touch->getLocation() ) )
				pUILayer->getChildByTag(BTN_MULTI_PRACTICE)->setScale(1.1f);
		}
		break;
	}
}

void UIManager::callMenuTrain(CCObject *sender)
{
    int accountKey = 0;
    int actionTag = ((CCMenuItemLabel*)sender)->getTag();
//    InGameScene *pLayer = ((InGameScene*)((CCMenuItemLabel*)sender)->getParent()->getParent()->getParent()->getChildByTag(TAG_INGAMELAYER));
//    int who = pLayer->getDataManager()->getLastPointedAnimal(accountKey);
//    if( who == -1 )
//    {
//        CCLog("UIManager::callMenuTrain : Wrong Last Pointed Animal");
//        return;
//    }
//    
//    switch (actionTag) {
//        case TEXTBTN_NAME:
//            //hanter
//            pLayer->teachNameSpeeching(who);
//            break;
//            //hanter
//        default:
//            pLayer->teachSpeeching(who, actionTag);
//            break;
//    }
}

void UIManager::createAnimal(CCLayer *pLayer)
{
    int accountKey = 0;
    int animalKey = pData->getNewAnimalKey(accountKey);
    char s[256] = {0,};
    strcpy( s, ((CCLabelTTF*)(pLayer->getChildByTag(CREATE_LABEL_NAME)))->getString() );
    CCLog(CCString::createWithFormat("UIManager::createAnimal : %s", ((CCLabelTTF*)(pLayer->getChildByTag(CREATE_LABEL_NAME)))->getString())->getCString());
    ANIMALINFO animalInfo( animalKey, create_animal_type, 0, 0, s );
    pData->makeDataFromAnimalInfo(accountKey, animalInfo);
    CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMELAYER)->addChild(pData->getAnimalByAnimalKey(accountKey, animalInfo.key)->getSprite());
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
	case INGAME:
		for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
		{
			CCTouch *touch = static_cast<CCTouch*>(*it);
			CCLayer *pUILayer = (CCLayer*)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMEUILAYER));
            float scale = pLayer->getScale();
            CCPoint point = touch->getLocation();
            CCPoint location = pLayer->getPosition();
            point.x -= WINSIZE_X/2 + location.x;
            point.y -= WINSIZE_Y/2 + location.y;
            point.x /= scale;
            point.y /= scale;
            point.x += WINSIZE_X/2;
            point.y += WINSIZE_Y/2;
            
			int accountKey = 0;
			int animalKey = pData->findAnimalRectContainsPoint(accountKey, point);
            if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(BTN_CREATE_ANIMAL)->boundingBox(), touch->getLocation() ) )
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
                setCreateAnimalType(pUILayer);
            }
            if( pUILayer->getChildByTag(CREATE_BLACKBOARD)->isVisible() )
            {
                if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(CREATE_FRAME_NAME)->boundingBox(), touch->getLocation()) )
                {
                    ((CCTextFieldTTF*)(pUILayer->getChildByTag(CREATE_TF_NAME)))->attachWithIME();
                }
                if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(CREATE_OK)->boundingBox(), touch->getLocation() ) )
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
                    createAnimal(pUILayer);
                }
                if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(CREATE_CLOSE)->boundingBox(), touch->getLocation() ) )
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
                }
                if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(CREATE_NEXT)->boundingBox(), touch->getLocation() ) )
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
                if( CCRect::CCRectContainsPoint( pUILayer->getChildByTag(CREATE_PREV)->boundingBox(), touch->getLocation() ) )
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
            else
            {
                if( !CCRect::CCRectContainsPoint( pUILayer->getChildByTag(TRAINING_BLACKBOARD)->boundingBox(), touch->getLocation() ) && pUILayer->getChildByTag(TRAINING_BLACKBOARD)->isVisible() )
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
                if( pLayer->getChildByTag(THINK_CLOUD)->isVisible() &&
                    CCRect::CCRectContainsPoint( pLayer->getChildByTag(THINK_CLOUD)->boundingBox(), point ) )
                    animalKey = pData->getLastPointedAnimal(accountKey);
                if( animalKey < 0 )
                {
                    pLayer->getChildByTag(THINK_CLOUD)->setVisible(false);
                    pLayer->getChildByTag(ICON_MEAT)->setVisible(false);
                    pLayer->getChildByTag(ICON_BLACKBOARD)->setVisible(false);
                    pLayer->getChildByTag(ICON_SWING)->setVisible(false);
                    pLayer->getChildByTag(ICON_RUNNING)->setVisible(false);
                    pLayer->getChildByTag(ICON_ROPE)->setVisible(false);
                    continue;
                }
                Animal* animal = pData->getAnimalByAnimalKey(accountKey, animalKey);
                
                if( pLayer->getChildByTag(THINK_CLOUD)->isVisible() )
                {
                    if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(ICON_MEAT)->boundingBox(), point ) )
                    {
                        animal->cancelAllMotions();
                        animal->addMotion(EAT, 5);
                        animal->addStatus(STATUS_FULLNESS, 10);
                    }
                    if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(ICON_SWING)->boundingBox(), point ) )
                    {
                        animal->cancelAllMotions();
                        animal->addMotion(FUN_SWING, 5);
                        animal->addStatus(STATUS_FULLNESS, -5);
                        animal->addStatus(STATUS_JOY, 10);
                        animal->addStatus(STATUS_EXP, 30);
                    }
                    if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(ICON_RUNNING)->boundingBox(), point ) )
                    {
                        animal->cancelAllMotions();
                        animal->addMotion(FUN_RUNNING, 5);
                        animal->addStatus(STATUS_FULLNESS, -5);
                        animal->addStatus(STATUS_JOY, 10);
                        animal->addStatus(STATUS_EXP, 10);
                    }
                    if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(ICON_ROPE)->boundingBox(), point ) )
                    {
                        animal->cancelAllMotions();
                        animal->addMotion(FUN_ROPE, 5);
                        animal->addStatus(STATUS_FULLNESS, -5);
                        animal->addStatus(STATUS_JOY, 10);
                        animal->addStatus(STATUS_EXP, 10);
                    }
                    if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(ICON_BLACKBOARD)->boundingBox(), point ) )
                    {
                        //hanter
                        ((InGameScene*)pLayer)->stopVoiceRecognition();
                        
                        char szLevel[8];
                        sprintf( szLevel, "%d", animal->getAnimalInfo().level );
                        ((CCLabelTTF*)pUILayer->getChildByTag(TRAIN_NAME))->setString(animal->getAnimalInfo().name);
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

                if( CCRect::CCRectContainsPoint( animal->getSprite()->boundingBox(), point ) )
                {
                    pLayer->getChildByTag(THINK_CLOUD)->setVisible(true);
                    pLayer->getChildByTag(ICON_MEAT)->setVisible(true);
                    pLayer->getChildByTag(ICON_BLACKBOARD)->setVisible(true);
                    pLayer->getChildByTag(ICON_SWING)->setVisible(true);
                    pLayer->getChildByTag(ICON_RUNNING)->setVisible(true);
                    pLayer->getChildByTag(ICON_ROPE)->setVisible(true);
                }
                else
                {
                    pLayer->getChildByTag(THINK_CLOUD)->setVisible(false);
                    pLayer->getChildByTag(ICON_MEAT)->setVisible(false);
                    pLayer->getChildByTag(ICON_BLACKBOARD)->setVisible(false);
                    pLayer->getChildByTag(ICON_SWING)->setVisible(false);
                    pLayer->getChildByTag(ICON_RUNNING)->setVisible(false);
                    pLayer->getChildByTag(ICON_ROPE)->setVisible(false);
                }
            }
		}
        {
            CCLayer* pUILayer = (CCLayer*)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_INGAMEUILAYER));
            pUILayer->getChildByTag(BTN_OPTION)->setScale(1.f);
            pUILayer->getChildByTag(BTN_FRIENDS)->setScale(1.f);
            pUILayer->getChildByTag(BTN_MULTI_PRACTICE)->setScale(1.f);
        }
		break;
	}
}