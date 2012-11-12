#include "Animal.h"

Animal::Animal(ANIMALINFO _animalInfo)
{
    info.exp = _animalInfo.exp;
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
	CCTexture2D *pTexture	= CCTextureCache::sharedTextureCache()->addImage(filename);
	//CCSize		sizeTexture = pTexture->getContentSize();
	//
	//CCAnimation *animation	= CCAnimation::create();
	//animation->setDelayPerUnit(0.1f);

	//sizeTexture.width /= SPRITE_FRAME;
	//for( int iFrame = 0; iFrame < SPRITE_FRAME; iFrame++ )
	//{		
	//	animation->addSpriteFrameWithTexture(pTexture, CCRectMake(
	//		sizeTexture.width*iFrame, 
	//		sizeTexture.height*0, 
	//		sizeTexture.width, 
	//		sizeTexture.height));
	//}

	//CCAnimate			*animate	= CCAnimate::create(animation);
	////CCAction		*temp		= CCActionEase::create(animate);

	//animate->setDuration(duration[motion]);
	animates[motion] = pTexture;
	
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
	switch( motionState )
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

	switch( motionState )
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
		addMotion(WALK_LEFT, rand()%3+1);
		addMotion(WALK_RIGHT, rand()%3+1);
		addMotion(WALK_BACK_RIGHT, rand()%3+1);
		addMotion(WALK_BACK_LEFT, rand()%3+1);
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
	nextMotion->num_of_repeat--;
	runActionWithMotion(nextMotion->name);
#endif
}

void Animal::addMotion(MOTION name, short num_of_repeat, bool cleanQueue)
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

    if(cleanQueue)
    {
        pBody->stopAllActions();
        cancelAllMotions();
    }
	motionQueue.push(pack);
}

void Animal::addMotion(MOTIONPACK pack, bool cleanQueue)
{
	addMotion(pack.name, pack.num_of_repeat, cleanQueue);
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

void Animal::doAction(int action, int num_of_repeat)
{
    //pBody->stopAllActions();
    cancelAllMotions();
    
    switch (action) {
        case ACTION_BASIC_COME:
            break;
        case ACTION_BASIC_CURE:
            break;
        case ACTION_BASIC_EAT:
            addMotion(EAT, 5);
            break;
        case ACTION_BASIC_REST:
            addMotion(SIT, 5);
            break;
        case ACTION_BASIC_RUN:
            addMotion(RUN_LEFT, 5);
            break;
        case ACTION_BASIC_SLEEP:
            addMotion(SLEEP, 10);
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
            addMotion(FUN_ROPE, 5);
            break;
        case ACTION_TRAINING_RUNNING:
            addMotion(FUN_RUNNING, 5);
            break;
        case ACTION_PLAYING_PLAY:
            break;
        case ACTION_PLAYING_SWING:
            addMotion(FUN_SWING, 5);
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
		delete motionQueue.front();
		motionQueue.pop();
	}
}

void Animal::runActionWithMotion(MOTION motion)
{
	CCTexture2D *pTexture	= animates[motion];
	CCSize		sizeTexture = pTexture->getContentSize();
	
	CCAnimation *animation	= CCAnimation::create();
	animation->setDelayPerUnit(0.1f);

	sizeTexture.width /= SPRITE_FRAME;
	for( int iFrame = 0; iFrame < SPRITE_FRAME; iFrame++ )
	{		
		animation->addSpriteFrameWithTexture(pTexture, CCRectMake(
			sizeTexture.width*iFrame, 
			sizeTexture.height*0, 
			sizeTexture.width, 
			sizeTexture.height));
	}
    
	CCAnimate			*animate	= CCAnimate::create(animation);//CCAnimate::create(animates[motion]->animation());
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
	motionState = motion;
	pBody->runAction(action);
}

CCSprite* Animal::getSprite()
{
	return pBody;
}

void Animal::setSprite(cocos2d::CCSprite *pBody)
{
	this->pBody = pBody;
}

void Animal::gainExp(unsigned int exp)
{
	info.exp += exp;
}

MOTION Animal::getMotionState()
{
	return motionState;
}

ANIMALINFO Animal::getAnimalInfo()
{
	return info;
}