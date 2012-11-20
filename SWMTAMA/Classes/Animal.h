#pragma once

#include "GameStd.h"
#include "cocos2d.h"
#include <queue>
#include "ActionList.h"
using namespace cocos2d;
using namespace std;

#define SPRITE_FRAME	8
enum	ANIMAL_TYPE		{ LION, ELEPHANT, MONKEY, SQUIRREL, ANIMAL_TYPE_END };
enum	MOTION			{ WALK_LEFT, WALK_RIGHT, WALK_BACK_LEFT, WALK_BACK_RIGHT, RUN_LEFT, RUN_RIGHT, RUN_BACK_LEFT, RUN_BACK_RIGHT, STAND, SIT, SLEEP, EAT, POOP, SICK, FUN_SWING, FUN_RUNNING, FUN_ROPE, MOTION_END };
enum	MOTION_WAY		{ ITERATIVE };
enum    STATUS_TYPE     { STATUS_SLEEP, STATUS_EXP, STATUS_FULLNESS, STATUS_POOP, STATUS_HEALTH, STATUS_JOY };

const float				duration[MOTION_END]	= { 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f };
const float				default_scale			= 0.8f;
const cocos2d::CCPoint	walk_scale				= cocos2d::CCPoint(TILESIZE_X/2, TILESIZE_Y/2);
const cocos2d::CCPoint	run_scale				= cocos2d::CCPoint(TILESIZE_X, TILESIZE_Y);

enum TAG_STATE { STATE_HAPPY = 3000, STATE_UNHAPPY, STATE_SICK, STATE_HUNGRY, STATE_SLEEPY, STATE_POOP };
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

struct STATEINFO
{
    bool    isHappy;
    bool    isUnhappy;
    bool    isSick;
    bool    isHungry;
    bool    isSleepy;
    bool    isPoop; //;;;
    
    float   timerHappy;
    float   timerUnhappy;
    float   timerSick;
    float   timerHungry;
    float   timerSleepy;
    float   timerPoop; //;;;
    
    STATEINFO()
    : isHappy(false), isUnhappy(false), isSick(false), isHungry(false), isSleepy(false), isPoop(false),
    timerHappy(0.f), timerUnhappy(0.f), timerSick(0.f), timerHungry(0.f), timerSleepy(0.f), timerPoop(0.f) {}
    
    int countTriggered()
    {
        int counter = 0;
        if( isHappy ) counter++;
        if( isSick ) counter++;
        if( isHungry ) counter++;
        if( isSleepy ) counter++;
        if( isPoop ) counter++;
        return counter;
    }
    
    bool frame(float dt)
    {
//        if( isHappy )   timerHappy += dt;
//        if( isSick )    timerSick += dt;
//        if( isHungry )  timerHungry += dt;
//        if( isSleepy )  timerSleepy += dt;
//        if( isPoop )    timerPoop += dt;
//        
//        if( timerHappy > 5.f )
//        {
//            
//        }isHappy = false;
    }
};

struct ANIMALINFO
{
	int				key;
	ANIMAL_TYPE		type;
    string			name;
	int             level;
    STATUSINFO      status;

    
	ANIMALINFO(int _key, ANIMAL_TYPE _type, int _level, int _exp, string _name)
    : key(_key), type(_type), name(_name), level(_level) {}
    ANIMALINFO(int _key, ANIMAL_TYPE _type, int _level, int _exp, string _name,
               int _sleep, int _fullness, int _poop, int _health, int _joy)
    : key(_key), type(_type), name(_name), level(_level), status(_sleep, _exp, _fullness, _poop, _health, _joy)
    {}
    ANIMALINFO() {}
};

struct MOTIONPACK
{
	MOTION		name;
	short		num_of_repeat;
    bool        isOrder;
};

class Animal : public CCObject
{
protected:
	ANIMALINFO				info;
	CCSprite*				pBody;
	MOTIONPACK				motionState;
	cocos2d::CCTexture2D	*animates[MOTION_END][SPRITE_FRAME];
	queue<MOTIONPACK*>		motionQueue;
    static cocos2d::CCTexture2D     *animatesPool[ANIMAL_TYPE_END][MOTION_END][SPRITE_FRAME];
    
    STATEINFO               state;
    int                     stateIndex;
    float                   timer;
    
protected:
	virtual bool makeAnimateWithImage(const char* filename, MOTION motion);
	virtual bool makeAnimates() = 0;
	virtual bool initiate(ANIMALINFO animalInfo);
	virtual void finishChk(cocos2d::CCNode *node);
    MOTION getDefaultMotion(int action);
    
public:
	void addMotion(MOTION name, short num_of_repeat, bool isOrder, bool cleanQueue = false);
	void addMotion(MOTIONPACK pack, bool cleanQueue = false);
    void doAction(int action, bool isOrder);
	void cancelAllMotions(int superFlag = -1);
	virtual void runActionWithMotion(MOTION motion);
	
    void addStatus(STATUS_TYPE type, int value);
    void setStatus(STATUS_TYPE type, int value);
    int getStatus(STATUS_TYPE type);
    STATUSINFO getStatus();
    void frame(float dt);
    
public:
    void setHappy(float time = 5.0f);
    void setSick(float time = 5.0f);
    void setSleepy(float time = 5.0f);
    
public:
    static void loadAnimateWithImage(const char* filename, ANIMAL_TYPE type, int number, MOTION motion);
    
public:
	cocos2d::CCSprite* getSprite();
	void setSprite(cocos2d::CCSprite *pBody);
	MOTIONPACK getMotionState();
	ANIMALINFO getAnimalInfo();

public:
	Animal(ANIMALINFO _animalInfo);
    Animal();
	~Animal(void);
};

