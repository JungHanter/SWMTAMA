#include "Animal.h"

Animal::Animal(ANIMALINFO _animalInfo)
{
    info.key = _animalInfo.key;
    info.level = _animalInfo.level;
    info.type = _animalInfo.type;
    info.name = new char[strlen(_animalInfo.name)+1];
    strcpy(info.name, _animalInfo.name);
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

bool Animal::initiate(ANIMALINFO animalInfo)
{
	pBody = CCSprite::create();

	pBody->setPosition(ccp(WINSIZE_X/2, WINSIZE_X/4));
	pBody->setScale(default_scale);
	pBody->setTag(animalInfo.key);

	makeAnimates();

	info = animalInfo;

	runActionWithMotion(STAND);

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
		motionQueue.pop();
		if( motionQueue.empty() )
		{
			runActionWithMotion(STAND);
			return;
		}
		nextMotion = motionQueue.front();
	}
    motionState.isOrder = nextMotion->isOrder;
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
            break;
        case ACTION_BASIC_EAT:
            addMotion(EAT, 5, isOrder);
            break;
        case ACTION_BASIC_REST:
            addMotion(SIT, 5, isOrder);
            break;
        case ACTION_BASIC_RUN:
            addMotion(RUN_LEFT, 5, isOrder);
            break;
        case ACTION_BASIC_SLEEP:
            addMotion(SLEEP, 10, isOrder);
            break;
        case ACTION_BASIC_STOP:
            break;
        case ACTION_BASIC_WAKE:
            break;
        case ACTION_BASIC_POOP:
            break;
        case ACTION_TRAINING_CLEANPOOP:
            break;
        case ACTION_TRAINING_ROPE:
            addMotion(FUN_ROPE, 5, isOrder);
            break;
        case ACTION_TRAINING_RUNNING:
            addMotion(FUN_RUNNING, 5, isOrder);
            break;
        case ACTION_PLAYING_PLAY:
            break;
        case ACTION_PLAYING_SWING:
            addMotion(FUN_SWING, 5, isOrder);
            break;
        case ACTION_EXTRA_DIE:
           break;
        default:
            CCLog("Animal::doAction : wrong action input");
            break;
    }
}

void Animal::cancelAllMotions()
{
	while( !motionQueue.empty() )
	{
        if( motionQueue.front()->isOrder )
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
            if( info.status.exp > 100 || info.status.exp < 0 ) info.status.exp -= value;
            break;
            
        case STATUS_FULLNESS:
            info.status.fullness += value;
            if( info.status.fullness > 100 || info.status.fullness < 0 ) info.status.fullness -= value;
            break;
            
        case STATUS_HEALTH:
            info.status.health += value;
            if( info.status.health > 100 || info.status.health < 0 ) info.status.health -= value;
            break;
            
        case STATUS_JOY:
            info.status.joy += value;
            if( info.status.joy > 100 || info.status.joy < 0 ) info.status.joy -= value;
            break;
            
        case STATUS_POOP:
            info.status.poop += value;
            if( info.status.poop > 100 || info.status.poop < 0 ) info.status.poop -= value;
            break;
            
        case STATUS_SLEEP:
            info.status.sleep += value;
            if( info.status.sleep > 100 || info.status.sleep < 0 ) info.status.sleep -= value;
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