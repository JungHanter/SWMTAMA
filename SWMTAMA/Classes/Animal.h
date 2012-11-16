#pragma once

#include "GameStd.h"
#include "cocos2d.h"
#include <queue>
#include "ActionList.h"
using namespace cocos2d;
using namespace std;

#define SPRITE_FRAME	8
enum	ANIMAL_TYPE		{ LION, ELEPHANT, MONKEY, SQUIRREL };
enum	MOTION			{ WALK_LEFT, WALK_RIGHT, WALK_BACK_LEFT, WALK_BACK_RIGHT, RUN_LEFT, RUN_RIGHT, RUN_BACK_LEFT, RUN_BACK_RIGHT, STAND, SIT, SLEEP, EAT, POOP, SICK, FUN_SWING, FUN_RUNNING, FUN_ROPE, MOTION_END };
enum	MOTION_WAY		{ ITERATIVE };
enum    STATUS_TYPE     { STATUS_SLEEP, STATUS_EXP, STATUS_FULLNESS, STATUS_POOP, STATUS_HEALTH, STATUS_JOY };

const float				duration[MOTION_END]	= { 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f };
const float				default_scale			= 0.8f;
const cocos2d::CCPoint	walk_scale				= cocos2d::CCPoint(TILESIZE_X/2, TILESIZE_Y/2);
const cocos2d::CCPoint	run_scale				= cocos2d::CCPoint(TILESIZE_X, TILESIZE_Y);

struct STATUSINFO
{
    int             sleep;
	int				exp;
	int             fullness;
    int             poop;
    int             health;
    int             joy;
    
    STATUSINFO()
    :sleep(80), exp(0), fullness(80), poop(0), health(100), joy(80) {}
    
    STATUSINFO(int _sleep, int _exp, int _fullness, int _poop, int _health, int _joy)
    :sleep(_sleep), exp(_exp), fullness(_fullness), poop(_poop), health(_health), joy(_joy) {}
};

struct ANIMALINFO
{
	int				key;
	ANIMAL_TYPE		type;
    char*			name;
	int             level;
    STATUSINFO      status;

    
	ANIMALINFO(int _key, ANIMAL_TYPE _type, int _level, int _exp, char *_name)
    : key(_key), type(_type), level(_level)
    {
        name = new char[strlen(_name)+1];
        strcpy( name, _name);
    }
    ANIMALINFO(int _key, ANIMAL_TYPE _type, int _level, int _exp, char *_name,
               int _sleep, int _fullness, int _poop, int _health, int _joy)
    : key(_key), type(_type), level(_level), status(_sleep, _exp, _fullness, _poop, _health, _joy)
    {
        name = new char[strlen(_name)+1];
        strcpy( name, _name);
    }
    ANIMALINFO() {}
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
	cocos2d::CCTexture2D	*animates[MOTION_END][SPRITE_FRAME];
	queue<MOTIONPACK*>		motionQueue;

protected:
	virtual bool makeAnimateWithImage(const char* filename, MOTION motion);
	virtual bool makeAnimates() = 0;
	virtual bool initiate(ANIMALINFO animalInfo);
	virtual void finishChk(cocos2d::CCNode *node);
    MOTION getDefaultMotion(int action);
    
public:
	void addMotion(MOTION name, short num_of_repeat, bool cleanQueue = false);
	void addMotion(MOTIONPACK pack, bool cleanQueue = false);
    void doAction(int action, int num_of_repeat = 1);
	void cancelAllMotions();
	virtual void runActionWithMotion(MOTION motion);
	
    void addStatus(STATUS_TYPE type, int value);
    void setStatus(STATUS_TYPE type, int value);
    int getStatus(STATUS_TYPE type);
    STATUSINFO getStatus();
    void frame(float dt);
public:
	cocos2d::CCSprite* getSprite();
	void setSprite(cocos2d::CCSprite *pBody);
	MOTION getMotionState();
	ANIMALINFO getAnimalInfo();

public:
	Animal(ANIMALINFO _animalInfo);
    Animal();
	~Animal(void);
};

