#pragma once

#include "GameStd.h"
#include "cocos2d.h"
#include <queue>
using namespace cocos2d;
using namespace std;

#define SPRITE_FRAME	8
enum	ANIMAL_TYPE		{ LION, ELEPHANT, MONKEY, SQUIRREL };
enum	MOTION			{ WALK_LEFT, WALK_RIGHT, WALK_BACK_LEFT, WALK_BACK_RIGHT, RUN_LEFT, RUN_RIGHT, RUN_BACK_LEFT, RUN_BACK_RIGHT, STAND, SIT, SLEEP, EAT, POOP, SICK, FUN_SWING, FUN_RUNNING, FUN_ROPE, MOTION_END };
enum	MOTION_WAY		{ ITERATIVE };

const float				duration[MOTION_END]	= { 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f };
const float				default_scale			= 0.8f;
const cocos2d::CCPoint	walk_scale				= cocos2d::CCPoint(TILESIZE_X/2, TILESIZE_Y/2);
const cocos2d::CCPoint	run_scale				= cocos2d::CCPoint(TILESIZE_X, TILESIZE_Y);

struct ANIMALINFO
{
	int				key;
	ANIMAL_TYPE		type;
	char			level[32];
	int				exp;
	char			name[32];
	ANIMALINFO() :  exp(0) {}
};

struct MOTIONPACK
{
	MOTION		name;
	short		num_of_repeat;

};

class Animal : public CCObject
{
protected:
	ANIMALINFO				info;
	CCSprite*				pBody;
	MOTION					motionState;
	cocos2d::CCTexture2D	*animates[MOTION_END];
	queue<MOTIONPACK*>		motionQueue;

protected:
	virtual bool makeAnimateWithImage(const char* filename, MOTION motion);
	virtual bool makeAnimates() = 0;
	virtual bool initiate(ANIMALINFO animalInfo);
	virtual void finishChk(cocos2d::CCNode *node);

public:
	void addMotion(MOTION name, short num_of_repeat, bool cleanQueue = false);
	void addMotion(MOTIONPACK pack, bool cleanQueue = false);
	void cancelAllMotions();
	virtual void runActionWithMotion(MOTION motion);
	

public:
	cocos2d::CCSprite* getSprite();
	void setSprite(cocos2d::CCSprite *pBody);
	void gainExp(unsigned int exp);
	MOTION getMotionState();
	ANIMALINFO getAnimalInfo();

public:
	Animal(void);
	~Animal(void);
};

