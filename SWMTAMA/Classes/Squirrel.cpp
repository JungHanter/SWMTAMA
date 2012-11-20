#include "Squirrel.h"


Squirrel::Squirrel(ANIMALINFO animalInfo)
{
    initiate(animalInfo);
}


Squirrel::~Squirrel(void)
{
}

bool Squirrel::makeAnimates()
{
	makeAnimateWithImage("SQUIRREL_WALK_LEFT", WALK_LEFT);
	makeAnimateWithImage("SQUIRREL_WALK_RIGHT", WALK_RIGHT);
	makeAnimateWithImage("SQUIRREL_WALK_BACK_LEFT", WALK_BACK_LEFT);
	makeAnimateWithImage("SQUIRREL_WALK_BACK_RIGHT", WALK_BACK_RIGHT);
	makeAnimateWithImage("SQUIRREL_RUN_LEFT", RUN_LEFT);
	makeAnimateWithImage("SQUIRREL_RUN_RIGHT", RUN_RIGHT);
	makeAnimateWithImage("SQUIRREL_RUN_BACK_LEFT", RUN_BACK_LEFT);
	makeAnimateWithImage("SQUIRREL_RUN_BACK_RIGHT", RUN_BACK_RIGHT);
	makeAnimateWithImage("SQUIRREL_STAND", STAND);
	makeAnimateWithImage("SQUIRREL_SIT", SIT);
	makeAnimateWithImage("SQUIRREL_SLEEP", SLEEP);
	makeAnimateWithImage("SQUIRREL_EAT", EAT);
	makeAnimateWithImage("SQUIRREL_POOP", POOP);
	makeAnimateWithImage("SQUIRREL_SICK", SICK);
	makeAnimateWithImage("SQUIRREL_SWING", FUN_SWING);
	makeAnimateWithImage("SQUIRREL_RUNNING", FUN_RUNNING);
	makeAnimateWithImage("SQUIRREL_ROPE", FUN_ROPE);
    
    pBody->setPosition(ccp(-10,10));
    
	return true;
}