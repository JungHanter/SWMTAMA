#include "Animal.h"
#include "UIManager.h"
cocos2d::CCTexture2D     *Animal::animatesPool[ANIMAL_TYPE_END][MOTION_END][SPRITE_FRAME];

Animal::Animal(ANIMALINFO _animalInfo)
{
    info.key = _animalInfo.key;
    info.level = _animalInfo.level;
    info.type = _animalInfo.type;
    info.name = _animalInfo.name;
}

Animal::Animal(void)
{
}

Animal::~Animal(void)
{
}

bool Animal::makeAnimateWithImage(const char* filename, MOTION motion)
{
    for(int i = 0; i < SPRITE_FRAME; i++)
    {
        //if sprite frame is over 10 it must be modified.
        string filename_divided = CCString::createWithFormat("characters/%s_0%d.png", filename, i+1)->getCString();
        CCTexture2D *pTexture	= CCTextureCache::sharedTextureCache()->addImage(filename_divided.data());
        animates[motion][i] = pTexture;
    }
	
	return true;
}

void Animal::loadAnimateWithImage(const char* filename, ANIMAL_TYPE type, int number, MOTION motion)
{
    //if sprite frame is over 10 it must be modified.
    string filename_divided = CCString::createWithFormat("characters/%s_0%d.png", filename, number+1)->getCString();
    CCLog("Tester1");
    CCTexture2D *pTexture	= CCTextureCache::sharedTextureCache()->addImage(filename_divided.data());
    CCLog("Tester2");
    animatesPool[type][motion][number] = pTexture;
}

bool Animal::initiate(ANIMALINFO animalInfo)
{
	pBody = CCSprite::create();

	pBody->setPosition(ccp(WINSIZE_X/2, WINSIZE_X/4));
	pBody->setScale(default_scale);
	pBody->setTag(animalInfo.key);

	makeAnimates();

	info = animalInfo;

	runActionWithMotion(STAND);

    
    CCSpriteFrame *frame;
    CCSprite *sprite;
    
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("happy.png");
    sprite = CCSprite::spriteWithSpriteFrame(frame);
    sprite->setTag(STATE_HAPPY);
    //sprite->setAnchorPoint(ccp(0.0f,-1.f));
    //sprite->setPosition(ccp(0, pBody->getContentSize().height/5));
    sprite->setScale(0.5f);
    sprite->setVisible(false);
    pBody->addChild(sprite);
    
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sick.png");
    sprite = CCSprite::spriteWithSpriteFrame(frame);
    sprite->setTag(STATE_UNHAPPY);
    //sprite->setAnchorPoint(ccp(0.0f,-1.f));
    //sprite->setPosition(ccp(0, pBody->getContentSize().height/5));
    sprite->setScale(0.5f);
    sprite->setVisible(false);
    pBody->addChild(sprite);
    
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_health.png");
    sprite = CCSprite::spriteWithSpriteFrame(frame);
    sprite->setTag(STATE_SICK);
    //sprite->setAnchorPoint(ccp(0.0f,-1.f));
    //sprite->setPosition(ccp(0, pBody->getContentSize().height/5));
    sprite->setScale(0.35f);
    sprite->setVisible(false);
    pBody->addChild(sprite);
    
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hungry.png");
    sprite = CCSprite::spriteWithSpriteFrame(frame);
    sprite->setTag(STATE_HUNGRY);
    //sprite->setAnchorPoint(ccp(0.0f,-1.f));
    //sprite->setPosition(ccp(0, pBody->getContentSize().height/5));
    sprite->setScale(0.5f);
    sprite->setVisible(false);
    pBody->addChild(sprite);
    
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sleepy.png");
    sprite = CCSprite::spriteWithSpriteFrame(frame);
    sprite->setTag(STATE_SLEEPY);
    //sprite->setAnchorPoint(ccp(0.0f,-1.f));
    //sprite->setPosition(ccp(0, pBody->getContentSize().height/5));
    sprite->setScale(0.5f);
    sprite->setVisible(false);
    pBody->addChild(sprite);
    
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("poop.png");
    sprite = CCSprite::spriteWithSpriteFrame(frame);
    sprite->setTag(STATE_POOP);
    //sprite->setAnchorPoint(ccp(0.0f,-1.f));
    //sprite->setPosition(ccp(0, pBody->getContentSize().height/5));
    sprite->setScale(2.f);
    sprite->setVisible(false);
    pBody->addChild(sprite);
    
    stateIndex = 0;
    timer = 0.f;
    
	return true;
}

void Animal::finishChk(cocos2d::CCNode *node)
{
	pBody->stopAllActions();

//#define REPLAY_LAST_MOTION
//#define ITERATE_MOTION
#define MOVE_WITH_AI
#ifdef REPLAY_LAST_MOTION
	switch( motionState.name )
	{
	case WALK:
		step = FORWARD_LEFT;
		runActionWithMotion( WALK, step );
		break;
	case WALK_BACK:
		step = BACK_LEFT;
		runActionWithMotion( WALK_BACK, step );
		break;
	case RUN:
		step = FORWARD_LEFT;
		runActionWithMotion( RUN, step );
		break;
	case RUN_BACK:
		step = BACK_LEFT;
		runActionWithMotion( RUN_BACK, step );
		break;
	case STAND:
		runActionWithMotion( STAND );
		break;
	case SIT:
		runActionWithMotion( SIT );
		break;
	case SLEEP:
		runActionWithMotion( SLEEP );
		break;
	case EAT:
		runActionWithMotion( EAT );
		break;
	case POOP:
		runActionWithMotion( POOP );
		break;
	case SICK:
		runActionWithMotion( SICK );
		break;
	}
#endif
#ifdef ITERATE_MOTION

	switch( motionState.name )
	{
	case WALK:
		step = BACK_LEFT;
		runActionWithMotion( WALK_BACK, step );
		break;
	case WALK_BACK:
		step = FORWARD_LEFT;
		runActionWithMotion( RUN, step );
		break;
	case RUN:
		step = BACK_LEFT;
		runActionWithMotion( RUN_BACK, step );
		break;
	case RUN_BACK:
		runActionWithMotion( STAND );
		break;
	case STAND:
		runActionWithMotion( SIT );
		break;
	case SIT:
		runActionWithMotion( SLEEP );
		break;
	case SLEEP:
		runActionWithMotion( EAT );
		break;
	case EAT:
		runActionWithMotion( POOP );
		break;
	case POOP:
		runActionWithMotion( SICK );
		break;
	case SICK:
		step = FORWARD_LEFT;
		runActionWithMotion( WALK, step );
		break;
	}
#endif
#ifdef MOVE_WITH_AI
	if( motionQueue.empty() )
	{
		runActionWithMotion(STAND);
		addMotion(WALK_LEFT, rand()%3+1, false);
		addMotion(WALK_RIGHT, rand()%3+1, false);
		addMotion(WALK_BACK_RIGHT, rand()%3+1,false);
		addMotion(WALK_BACK_LEFT, rand()%3+1, false);
		return;
	}
	MOTIONPACK *nextMotion = motionQueue.front();
	if( nextMotion == NULL ) return;

	while(nextMotion->num_of_repeat == 0)
	{
        if( nextMotion->name == POOP )
            pBody->getChildByTag(STATE_POOP)->setVisible(false);
		motionQueue.pop();
		if( motionQueue.empty() )
		{
			runActionWithMotion(STAND);
			return;
		}
		nextMotion = motionQueue.front();
	}
    motionState.isOrder = nextMotion->isOrder;
    if( nextMotion->name != SICK )
        nextMotion->num_of_repeat--;
	runActionWithMotion(nextMotion->name);
#endif
}

void Animal::addMotion(MOTION name, short num_of_repeat, bool isOrder, bool cleanQueue)
{
	MOTIONPACK *pack = new MOTIONPACK;

	if(name >= MOTION_END)
	{
		// Invalid Motion Name
		return;
	}

	if(num_of_repeat <= 0)
	{
		// Please set positive number of repeat
		return;
	}

	pack->name = name;
	pack->num_of_repeat = num_of_repeat;
    pack->isOrder = isOrder;
    
    if(cleanQueue)
    {
        if(!motionQueue.front()->isOrder)
            pBody->stopAllActions();
        cancelAllMotions();
    }
	motionQueue.push(pack);
}

void Animal::addMotion(MOTIONPACK pack, bool cleanQueue)
{
	addMotion(pack.name, pack.num_of_repeat, pack.isOrder, cleanQueue);
}

MOTION Animal::getDefaultMotion(int action)
{
    MOTION motion = MOTION_END;
    switch (action) {
        case ACTION_BASIC_COME: ;   break;
        case ACTION_BASIC_CURE: ;   break;
        case ACTION_BASIC_EAT: ;   break;
        case ACTION_BASIC_REST: ;   break;
        case ACTION_BASIC_RUN: ;   break;
        case ACTION_BASIC_SLEEP: ;   break;
        case ACTION_BASIC_STOP: ;   break;
        case ACTION_BASIC_WAKE: ;   break;
        case ACTION_BASIC_POOP: ;   break;
        case ACTION_TRAINING_CLEANPOOP: ;   break;
        case ACTION_TRAINING_ROPE: ;   break;
        case ACTION_TRAINING_RUNNING: ;   break;
        case ACTION_PLAYING_PLAY: ;   break;
        case ACTION_PLAYING_SWING: ;   break;
        case ACTION_EXTRA_DIE: ;   break;
    }
}

void Animal::doAction(int action, bool isOrder)
{
    //pBody->stopAllActions();
    cancelAllMotions();
    
    switch (action) {
        case ACTION_BASIC_COME:
            break;
        case ACTION_BASIC_CURE:
            cancelAllMotions(ACTION_BASIC_CURE);
            setStatus(STATUS_FULLNESS, 80);
            setStatus(STATUS_HEALTH, 70);
            setStatus(STATUS_JOY, 95);
            addStatus(STATUS_EXP, 10);
            break;
        case ACTION_BASIC_EAT:
            addMotion(EAT, 3, isOrder);
            addStatus(STATUS_FULLNESS, 20);
            addStatus(STATUS_POOP, 30);
            addStatus(STATUS_EXP, 10);
            break;
        case ACTION_BASIC_REST:
            addMotion(SIT, 3, isOrder);
            addStatus(STATUS_JOY, 10);
            addStatus(STATUS_HEALTH, 10);
            addStatus(STATUS_EXP, 10);
            break;
        case ACTION_BASIC_RUN:
            addMotion(RUN_LEFT, 3, isOrder);
            addStatus(STATUS_SLEEP, 10);
            addStatus(STATUS_HEALTH, 10);
            addStatus(STATUS_EXP, 10);
            break;
        case ACTION_BASIC_SLEEP:
            addMotion(SLEEP, 100, isOrder);
            addStatus(STATUS_HEALTH, 10);
            addStatus(STATUS_FULLNESS, -20);
            addStatus(STATUS_EXP, 10);
            break;
        case ACTION_BASIC_STOP:
            cancelAllMotions(true);
            addStatus(STATUS_EXP, 20);
            break;
        case ACTION_BASIC_WAKE:
            cancelAllMotions(true);
            addStatus(STATUS_EXP, 20);
            addStatus(STATUS_SLEEP, 60);
            break;
        case ACTION_BASIC_POOP:
            addMotion(POOP, 3, isOrder);
            addStatus(STATUS_EXP, 20);
            setStatus(STATUS_POOP, 0);
            break;
        case ACTION_TRAINING_CLEANPOOP:
            break;
        case ACTION_TRAINING_ROPE:
            addMotion(FUN_ROPE, 3, isOrder);
            addStatus(STATUS_JOY, 50);
            addStatus(STATUS_HEALTH, 30);
            addStatus(STATUS_FULLNESS, -20);
            addStatus(STATUS_EXP, 20);
            break;
        case ACTION_TRAINING_RUNNING:
            addMotion(FUN_RUNNING, 3, isOrder);
            addStatus(STATUS_JOY, 50);
            addStatus(STATUS_HEALTH, 30);
            addStatus(STATUS_FULLNESS, -20);
            addStatus(STATUS_EXP, 20);
            break;
        case ACTION_PLAYING_PLAY:
            addMotion(FUN_ROPE, 3, isOrder);
            addStatus(STATUS_JOY, 50);
            addStatus(STATUS_HEALTH, 30);
            addStatus(STATUS_FULLNESS, -20);
            addStatus(STATUS_EXP, 20);
            break;
        case ACTION_PLAYING_SWING:
            addMotion(FUN_SWING, 3, isOrder);
            addStatus(STATUS_JOY, 50);
            addStatus(STATUS_HEALTH, 30);
            addStatus(STATUS_FULLNESS, -20);
            addStatus(STATUS_EXP, 20);
            break;
        case ACTION_EXTRA_DIE:
           break;
        default:
            CCLog("Animal::doAction : wrong action input");
            break;
    }
}

void Animal::cancelAllMotions(int superFlag)
{
	while( !motionQueue.empty() )
	{
//        if(motionQueue.front()->name == SICK && superFlag == ACTION_BASIC_CURE)
//            break;
//        
//        if( motionQueue.front()->name != SICK )
//        {
//            if(motionQueue.front()->name == SICK && superFlag == ACTION_BASIC_CURE)
//        }
        if( superFlag != ACTION_BASIC_CURE && (superFlag == -1 || motionQueue.front()->isOrder))
            break;
		delete motionQueue.front();
		motionQueue.pop();
	}
}

void Animal::runActionWithMotion(MOTION motion)
{
    CCAnimation *animation	= CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
    
    for( int iFrame = 0; iFrame < SPRITE_FRAME; iFrame++ )
	{
        CCTexture2D *pTexture	= animates[motion][iFrame];
        CCSize		sizeTexture = pTexture->getContentSize();
		animation->addSpriteFrameWithTexture(pTexture, CCRectMake(0, 0, sizeTexture.width, sizeTexture.height));
	}
    
	CCAnimate			*animate	= CCAnimate::create(animation);
    
    CCFiniteTimeAction	*action;
	CCPoint				direction;

	animate->setDuration(duration[motion]);

	switch(motion)
	{
	case WALK_LEFT:			
	case RUN_LEFT:			
		direction = ccp(-1.f, -1.f);	break;
	case WALK_RIGHT:		
	case RUN_RIGHT:			
		direction = ccp( 1.f, -1.f);	break;
	case WALK_BACK_LEFT:
	case RUN_BACK_LEFT:
		direction = ccp(-1.f,  1.f);	break;
	case WALK_BACK_RIGHT:
	case RUN_BACK_RIGHT:
		direction = ccp( 1.f,  1.f);	break;
	}

	switch(motion)
	{
	case WALK_LEFT:
	case WALK_RIGHT:
	case WALK_BACK_LEFT:
	case WALK_BACK_RIGHT:
		{
			CCPoint walk = ccp(direction.x*walk_scale.x, direction.y*walk_scale.y);
			action = CCSequence::actions(	
				CCSpawn::actions(CCMoveBy::create(duration[motion], walk), animate, NULL), 
				CCCallFuncN::actionWithTarget(this, callfuncN_selector(Animal::finishChk)), NULL);
		}
		break;
	case RUN_LEFT:
	case RUN_RIGHT:
	case RUN_BACK_LEFT:
	case RUN_BACK_RIGHT:
		{
			CCPoint run = ccp(direction.x*run_scale.x, direction.y*run_scale.y);
			action = CCSequence::actions(	
				CCSpawn::actions(CCMoveBy::create(duration[motion], run), animate, NULL), 
				CCCallFuncN::actionWithTarget(this, callfuncN_selector(Animal::finishChk)), NULL);
		}
		break;
	case STAND:
	case SIT:
	case SLEEP:
	case EAT:
	case POOP:
	case SICK:
	case FUN_SWING:
	case FUN_RUNNING:
	case FUN_ROPE:
		action = CCSequence::actions(	
			animate, 
			CCCallFuncN::actionWithTarget(this, callfuncN_selector(Animal::finishChk)), NULL);
		break;
	}
	motionState.name = motion;
	pBody->runAction(action);
}

void Animal::addStatus(STATUS_TYPE type, int value)
{
    switch (type) {
        case STATUS_EXP:
            info.status.exp += value;
            if( info.status.exp > 100 )
                info.status.exp = 100;
            if( info.status.exp < 0 )
                info.status.exp = 0;
            break;
            
        case STATUS_FULLNESS:
            info.status.fullness += value;
            
            if( info.status.fullness > 100 )
                info.status.fullness = 100;
            if( info.status.fullness < 0 )
                info.status.fullness = 0;
            break;
            
        case STATUS_HEALTH:
            info.status.health += value;
            
            if( info.status.health > 100 )
                info.status.health = 100;
            if( info.status.health < 0 )
                info.status.health = 0;
            break;
            
        case STATUS_JOY:
            info.status.joy += value;
            
            if( info.status.joy > 100 )
                info.status.joy = 100;
            if( info.status.joy < 0 )
                info.status.joy = 0;
            break;
            
        case STATUS_POOP:
            info.status.poop += value;
            
            if( info.status.poop > 100 )
                info.status.poop = 100;
            if( info.status.poop < 0 )
                info.status.poop = 0;
            break;
            
        case STATUS_SLEEP:
            info.status.sleep += value;
            
            if( info.status.sleep > 100 )
                info.status.sleep = 100;
            if( info.status.sleep < 0 )
                info.status.sleep = 0;
            break;
    }
}

void Animal::setStatus(STATUS_TYPE type, int value)
{
    if( value > 100 || value < 0 ) return;
    switch (type) {
        case STATUS_EXP:
            info.status.exp = value;
            break;
            
        case STATUS_FULLNESS:
            info.status.fullness = value;
            break;
            
        case STATUS_HEALTH:
            info.status.health = value;
            break;
            
        case STATUS_JOY:
            info.status.joy = value;
            break;
            
        case STATUS_POOP:
            info.status.poop = value;
            break;
            
        case STATUS_SLEEP:
            info.status.sleep = value;
            break;
    }
}

int Animal::getStatus(STATUS_TYPE type)
{
    switch (type) {
        case STATUS_EXP:
            return info.status.exp;
            
        case STATUS_FULLNESS:
            return info.status.fullness;
            
        case STATUS_HEALTH:
            return info.status.health;
            
        case STATUS_JOY:
            return info.status.joy;
            
        case STATUS_POOP:
            return info.status.poop;
            
        case STATUS_SLEEP:
            return info.status.sleep;
    }
    
    return -1;
}

STATUSINFO Animal::getStatus()
{
    return info.status;
}


void Animal::frame(float dt)
{
    if( info.status.exp >= 100 )
    {
        info.level++;
        info.status.exp = 0;
    }
    state.timerHappy += dt;
    state.timerHungry += dt;
    state.timerSleepy += dt;
    if( state.timerHappy > 4.f )
    {
        state.timerHappy = 0.f;
        if( info.status.joy > 15 )
            info.status.joy -= rand()%10 + 5;
        else
        {
//            int chap = rand()%3;
//            if( chap == 0 )
//                doAction(ACTION_PLAYING_SWING, true);
//            else if( chap == 1 )
//                doAction(ACTION_TRAINING_RUNNING, true);
//            else
//                doAction(ACTION_TRAINING_ROPE, true);
        }
    }
    if( state.timerSleepy > 300.f )
    {
        state.timerSleepy = 0.f;
        if( info.status.sleep > 15 )
            info.status.sleep -= rand()%10 + 5;
        else
        {
            addMotion(SLEEP, 100, true);
        }
    }
    if( info.status.poop >= 100 )
    {
        doAction(ACTION_BASIC_POOP, true);
    }
    
    if ( info.status.fullness < 10 && state.timerHungry > 4.f)
    {
        state.timerHungry = 0.f;
        if( info.status.health > 20 )
            info.status.health -= rand()%10 + 5;
        else
        {
            addMotion(SICK, 1, true);
        }
    }
    
    state.isHappy = info.status.joy >= 90;
    state.isUnhappy = info.status.joy <= 20;
    state.isHungry = info.status.fullness <= 40;
    state.isSick = info.status.health <= 20;
    state.isSleepy = info.status.sleep <= 40;
    state.isPoop = info.status.poop >= 70;
    
    CCPoint point;
    point.x = pBody->getContentSize().width*0.5f;
    point.y = pBody->getContentSize().height + 30;
    pBody->getChildByTag(STATE_HAPPY)->setPosition(point);
    pBody->getChildByTag(STATE_UNHAPPY)->setPosition(point);
    pBody->getChildByTag(STATE_HUNGRY)->setPosition(point);
    pBody->getChildByTag(STATE_SICK)->setPosition(point);
    pBody->getChildByTag(STATE_SLEEPY)->setPosition(point);
    pBody->getChildByTag(STATE_POOP)->setPosition(point);
    
    timer += dt;
    
    
    if( stateIndex == 0 )
    {
        if( state.isHappy )
        {
            pBody->getChildByTag(STATE_HAPPY)->setVisible(true);
            pBody->getChildByTag(STATE_UNHAPPY)->setVisible(false);
            pBody->getChildByTag(STATE_HUNGRY)->setVisible(false);
            pBody->getChildByTag(STATE_SICK)->setVisible(false);
            pBody->getChildByTag(STATE_SLEEPY)->setVisible(false);
            pBody->getChildByTag(STATE_POOP)->setVisible(false);
        }
        else
        {
            stateIndex = (++stateIndex)%6;
            pBody->getChildByTag(STATE_HAPPY)->setVisible(false);
        }
    }
    else if( stateIndex == 1 )
    {
        if( state.isHungry )
        {
            pBody->getChildByTag(STATE_HAPPY)->setVisible(false);
            pBody->getChildByTag(STATE_UNHAPPY)->setVisible(false);
            pBody->getChildByTag(STATE_HUNGRY)->setVisible(true);
            pBody->getChildByTag(STATE_SICK)->setVisible(false);
            pBody->getChildByTag(STATE_SLEEPY)->setVisible(false);
            pBody->getChildByTag(STATE_POOP)->setVisible(false);
        }
        else
        {
            stateIndex = (++stateIndex)%6;
            pBody->getChildByTag(STATE_HUNGRY)->setVisible(false);
        }
    }
    else if( stateIndex == 2 )
    {
        if( state.isSick )
        {
            pBody->getChildByTag(STATE_HAPPY)->setVisible(false);
            pBody->getChildByTag(STATE_UNHAPPY)->setVisible(false);
            pBody->getChildByTag(STATE_HUNGRY)->setVisible(false);
            pBody->getChildByTag(STATE_SICK)->setVisible(true);
            pBody->getChildByTag(STATE_SLEEPY)->setVisible(false);
            pBody->getChildByTag(STATE_POOP)->setVisible(false);
        }
        else
        {
            stateIndex = (++stateIndex)%6;
            pBody->getChildByTag(STATE_SICK)->setVisible(false);
        }
    }
    else if( stateIndex == 3 )
    {
        if( state.isSleepy )
        {
            pBody->getChildByTag(STATE_HAPPY)->setVisible(false);
            pBody->getChildByTag(STATE_UNHAPPY)->setVisible(false);
            pBody->getChildByTag(STATE_HUNGRY)->setVisible(false);
            pBody->getChildByTag(STATE_SICK)->setVisible(false);
            pBody->getChildByTag(STATE_SLEEPY)->setVisible(true);
            pBody->getChildByTag(STATE_POOP)->setVisible(false);
        }
        else
        {
            stateIndex = (++stateIndex)%6;
            pBody->getChildByTag(STATE_SLEEPY)->setVisible(false);
        }
    }
    else if( stateIndex == 4 )
    {
        if( state.isUnhappy )
        {
            pBody->getChildByTag(STATE_HAPPY)->setVisible(false);
            pBody->getChildByTag(STATE_UNHAPPY)->setVisible(true);
            pBody->getChildByTag(STATE_HUNGRY)->setVisible(false);
            pBody->getChildByTag(STATE_SICK)->setVisible(false);
            pBody->getChildByTag(STATE_SLEEPY)->setVisible(false);
            pBody->getChildByTag(STATE_POOP)->setVisible(false);
        }
        else
        {
            stateIndex = (++stateIndex)%6;
            pBody->getChildByTag(STATE_UNHAPPY)->setVisible(false);
        }
    }
    else
    {
        if( state.isPoop )
        {
            pBody->getChildByTag(STATE_HAPPY)->setVisible(false);
            pBody->getChildByTag(STATE_UNHAPPY)->setVisible(false);
            pBody->getChildByTag(STATE_HUNGRY)->setVisible(false);
            pBody->getChildByTag(STATE_SICK)->setVisible(false);
            pBody->getChildByTag(STATE_SLEEPY)->setVisible(false);
            pBody->getChildByTag(STATE_POOP)->setVisible(true);
        }
        else
        {
            stateIndex = (++stateIndex)%6;
        }
    }

    if( timer >= 3.f )
    {
        timer = 0.f;
        stateIndex = (++stateIndex)%6;
    }
    
//    pBody->getChildByTag(STATE_HAPPY)->setVisible(state.isHappy);
//    pBody->getChildByTag(STATE_HUNGRY)->setVisible(state.isHungry);
//    pBody->getChildByTag(STATE_SICK)->setVisible(state.isSick);
//    pBody->getChildByTag(STATE_SLEEPY)->setVisible(state.isSleepy);
//    pBody->getChildByTag(STATE_POOP)->setVisible(state.isPoop);
}

CCSprite* Animal::getSprite()
{
	return pBody;
}

void Animal::setSprite(cocos2d::CCSprite *pBody)
{
	this->pBody = pBody;
}


MOTIONPACK Animal::getMotionState()
{
	return motionState;
}

ANIMALINFO Animal::getAnimalInfo()
{
	return info;
}