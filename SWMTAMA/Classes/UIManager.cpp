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

bool UIManager::loadUI(cocos2d::CCLayer* pLayer, LAYERS layerEnum)
{
    CCMenu          *menuRequest;
	CCSpriteFrame	*frame;
	CCSprite		*sprite;
	CCLabelTTF		*label;
	CCPoint         point;
    CCMenuItemImage *itemImage;
    const int       UIORDER = 1000;

	int tag;
	switch(layerEnum)
	{
        case LOGIN:
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("11624_491f048fdd143.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.75f, WINSIZE_Y*0.4f));
            sprite->setScaleX(0.5f);
            sprite->setScaleY(0.3f);
            sprite->setTag(FRAME_LOGIN_ID);
            pLayer->addChild(sprite);
            
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("11624_491f048fdd143.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(WINSIZE_X*0.75f, WINSIZE_Y*0.20f));
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            sprite->setScaleX(0.5f);
            sprite->setScaleY(0.3f);
            sprite->setTag(FRAME_LOGIN_PW);
            pLayer->addChild(sprite);
    
            menuRequest = CCMenu::create();
            menuRequest->setPosition(CCPointZero);
            pLayer->addChild(menuRequest);
            
            itemImage = CCMenuItemImage::create("House.png", "House.png", pLayer, menu_selector(LoginScene::callTryLogin));
            itemImage->setPosition(ccp(WINSIZE_X*0.25f, WINSIZE_Y*0.45f));
            itemImage->setScale(1.9f);
            itemImage->setTag(BTN_HOUSE);
            menuRequest->addChild(itemImage, UIORDER);
            
            break;
        case INGAME:
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("option.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_OPTION_X, BUTTON_OPTION_Y));
            sprite->setTag(BTN_OPTION);
            pLayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("friends.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_FRIEND_X, BUTTON_FRIEND_Y));
            sprite->setTag(BTN_FRIENDS);
            pLayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("multi_practice.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_MULTI_PRACTICE_X, BUTTON_MULTI_PRACTICE_Y));
            sprite->setTag(BTN_MULTI_PRACTICE);
            pLayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("create_animal.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(BUTTON_MULTI_PRACTICE_X, BUTTON_MULTI_PRACTICE_Y));
            sprite->setTag(BTN_MULTI_PRACTICE);
            pLayer->addChild(sprite, UIORDER);
            
            // Blackboard
            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blackboard.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(sprite->getContentSize().width/2, WINSIZE_Y/2));
            sprite->setTag(BLACKBOARD);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER-50);

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
            pLayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_1.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
            sprite->setTag(SPEAKER_1);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_2.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
            sprite->setTag(SPEAKER_2);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_3.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
            sprite->setTag(SPEAKER_3);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER);

            frame	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("speaker_x.png");
            sprite	= CCSprite::spriteWithSpriteFrame(frame);
            sprite->setPosition(ccp(SPEAKER_X, SPEAKER_Y));
            sprite->setTag(SPEAKER_MUTE);
            sprite->setVisible(false);
            pLayer->addChild(sprite, UIORDER);

            label = CCLabelTTF::create(" Name", "", 60);
            label->setAnchorPoint(ccp(0, 0.5f));
            label->setPosition(ccp(20, WINSIZE_Y*0.9f));
            label->setTag(TRAIN_NAME);
            label->setVisible(false);
            pLayer->addChild(label, UIORDER);

            label = CCLabelTTF::create("LEVEL  ", "", 36);
            label->setAnchorPoint(ccp(1, 0.5f));
            label->setPosition(ccp(WINSIZE_X/4, WINSIZE_Y*0.8f));
            label->setTag(TRAIN_LEVEL);
            label->setVisible(false);
            pLayer->addChild(label, UIORDER);
            
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
            pLayer->addChild(menuRequest, UIORDER);
            
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
			ddt += dt/2;
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
			CCTouch *touch = static_cast<CCTouch*>(*it);
		
			if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(BTN_OPTION)->boundingBox(), touch->getLocation() ) )
				pLayer->getChildByTag(BTN_OPTION)->setScale(1.1f);
			if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(BTN_FRIENDS)->boundingBox(), touch->getLocation() ) )
				pLayer->getChildByTag(BTN_FRIENDS)->setScale(1.1f);
			if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(BTN_MULTI_PRACTICE)->boundingBox(), touch->getLocation() ) )
				pLayer->getChildByTag(BTN_MULTI_PRACTICE)->setScale(1.1f);
		}
		break;
	}
}

void UIManager::callMenuTrain(CCObject *sender)
{
    int accountKey = 0;
    int actionTag = ((CCMenuItemLabel*)sender)->getTag();
    InGameScene *pLayer = ((InGameScene*)((CCMenuItemLabel*)sender)->getParent()->getParent());
    int who = pLayer->getDataManager()->getLastPointedAnimal(accountKey);
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
            //hanter
        default:
            pLayer->teachSpeeching(who, actionTag);
            break;
    }
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
//	switch( (count++)%5 )
//	{
//	case 0:		setSpeaker(pLayer, SPEAKER_DEFAULT);	break;
//	case 1:		setSpeaker(pLayer, SPEAKER_1);			break;
//	case 2:		setSpeaker(pLayer, SPEAKER_2);			break;
//	case 3:		setSpeaker(pLayer, SPEAKER_3);			break;
//	case 4:		setSpeaker(pLayer, SPEAKER_MUTE);		break;
//	}
	switch(pLayer->getTag())
	{
	case INGAME:
		for( CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
		{
			CCTouch *touch = static_cast<CCTouch*>(*it);
			
			int accountKey = 0;
			int animalKey = pData->findAnimalRectContainsPoint(accountKey, touch->getLocation());
			if( !CCRect::CCRectContainsPoint( pLayer->getChildByTag(BLACKBOARD)->boundingBox(), touch->getLocation() ) &&
				pLayer->getChildByTag(BLACKBOARD)->isVisible() )
			{
                //hanter
                ((InGameScene*)pLayer)->stopTeachRecogntion();
                
				pLayer->getChildByTag(BLACKBOARD)->setVisible(false);
				pLayer->getChildByTag(TRAIN_NAME)->setVisible(false);
				pLayer->getChildByTag(TRAIN_LEVEL)->setVisible(false);
				pLayer->getChildByTag(MENU_TRAIN)->setVisible(false);
                
                ((InGameScene*)pLayer)->startVoiceRecognition();
			}
			if( pLayer->getChildByTag(THINK_CLOUD)->isVisible() &&
				CCRect::CCRectContainsPoint( pLayer->getChildByTag(THINK_CLOUD)->boundingBox(), touch->getLocation() ) )
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
				if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(ICON_MEAT)->boundingBox(), touch->getLocation() ) )
				{
					animal->cancelAllMotions();
					animal->addMotion(EAT, 5);
				}
				if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(ICON_SWING)->boundingBox(), touch->getLocation() ) )
				{
					animal->cancelAllMotions();
					animal->addMotion(FUN_SWING, 5);
				}
				if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(ICON_RUNNING)->boundingBox(), touch->getLocation() ) )
				{
					animal->cancelAllMotions();
					animal->addMotion(FUN_RUNNING, 5);
				}
				if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(ICON_ROPE)->boundingBox(), touch->getLocation() ) )
				{
					animal->cancelAllMotions();
					animal->addMotion(FUN_ROPE, 5);
				}
				if( CCRect::CCRectContainsPoint( pLayer->getChildByTag(ICON_BLACKBOARD)->boundingBox(), touch->getLocation() ) )
				{
                    //hanter
                    ((InGameScene*)pLayer)->stopVoiceRecognition();
                    
                    char szLevel[8];
                    sprintf( szLevel, "%d", animal->getAnimalInfo().level );
					((CCLabelTTF*)pLayer->getChildByTag(TRAIN_NAME))->setString(animal->getAnimalInfo().name);
					((CCLabelTTF*)pLayer->getChildByTag(TRAIN_LEVEL))->setString(szLevel);

					pLayer->getChildByTag(BLACKBOARD)->setVisible(!pLayer->getChildByTag(BLACKBOARD)->isVisible());
					pLayer->getChildByTag(TRAIN_NAME)->setVisible(!pLayer->getChildByTag(TRAIN_NAME)->isVisible());
					pLayer->getChildByTag(TRAIN_LEVEL)->setVisible(!pLayer->getChildByTag(TRAIN_LEVEL)->isVisible());
					pLayer->getChildByTag(MENU_TRAIN)->setVisible(!pLayer->getChildByTag(MENU_TRAIN)->isVisible());
                    
                    ((InGameScene*)pLayer)->startTeachRecogntion();
				}
			}

			if( CCRect::CCRectContainsPoint( animal->getSprite()->boundingBox(), touch->getLocation() ) )
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
		pLayer->getChildByTag(BTN_OPTION)->setScale(1.f);
		pLayer->getChildByTag(BTN_FRIENDS)->setScale(1.f);
		pLayer->getChildByTag(BTN_MULTI_PRACTICE)->setScale(1.f);
		break;
	}
}