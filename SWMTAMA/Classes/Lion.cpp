#include "Lion.h"


Lion::Lion(ANIMALINFO animalInfo)
{
	initiate(animalInfo);
}


Lion::~Lion(void)
{
}

bool Lion::makeAnimates()
{
	makeAnimateWithImage("LION_WALK_LEFT", WALK_LEFT);
	makeAnimateWithImage("LION_WALK_RIGHT", WALK_RIGHT);
	makeAnimateWithImage("LION_WALK_BACK_LEFT", WALK_BACK_LEFT);
	makeAnimateWithImage("LION_WALK_BACK_RIGHT", WALK_BACK_RIGHT);
	makeAnimateWithImage("LION_RUN_LEFT", RUN_LEFT);
	makeAnimateWithImage("LION_RUN_RIGHT", RUN_RIGHT);
	makeAnimateWithImage("LION_RUN_BACK_LEFT", RUN_BACK_LEFT);
	makeAnimateWithImage("LION_RUN_BACK_RIGHT", RUN_BACK_RIGHT);
	makeAnimateWithImage("LION_STAND", STAND);
	makeAnimateWithImage("LION_SIT", SIT);
	makeAnimateWithImage("LION_SLEEP", SLEEP);
	makeAnimateWithImage("LION_EAT", EAT);
	makeAnimateWithImage("LION_POOP", POOP);
	makeAnimateWithImage("LION_SICK", SICK);
	makeAnimateWithImage("LION_SWING", FUN_SWING);
	makeAnimateWithImage("LION_RUNNING", FUN_RUNNING);
	makeAnimateWithImage("LION_ROPE", FUN_ROPE);

    pBody->setPosition(ccp(700,100));
	return true;
}