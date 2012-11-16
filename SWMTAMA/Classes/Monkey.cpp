#include "Monkey.h"


Monkey::Monkey(ANIMALINFO animalInfo)
{
    initiate(animalInfo);
}


Monkey::~Monkey(void)
{
}

bool Monkey::makeAnimates()
{
	makeAnimateWithImage("MONKEY_WALK_LEFT", WALK_LEFT);
	makeAnimateWithImage("MONKEY_WALK_RIGHT", WALK_RIGHT);
	makeAnimateWithImage("MONKEY_WALK_BACK_LEFT", WALK_BACK_LEFT);
	makeAnimateWithImage("MONKEY_WALK_BACK_RIGHT", WALK_BACK_RIGHT);
	makeAnimateWithImage("MONKEY_RUN_LEFT", RUN_LEFT);
	makeAnimateWithImage("MONKEY_RUN_RIGHT", RUN_RIGHT);
	makeAnimateWithImage("MONKEY_RUN_BACK_LEFT", RUN_BACK_LEFT);
	makeAnimateWithImage("MONKEY_RUN_BACK_RIGHT", RUN_BACK_RIGHT);
	makeAnimateWithImage("MONKEY_STAND", STAND);
	makeAnimateWithImage("MONKEY_SIT", SIT);
	makeAnimateWithImage("MONKEY_SLEEP", SLEEP);
	makeAnimateWithImage("MONKEY_EAT", EAT);
	makeAnimateWithImage("MONKEY_POOP", POOP);
	makeAnimateWithImage("MONKEY_SICK", SICK);
	makeAnimateWithImage("MONKEY_SWING", FUN_SWING);
	makeAnimateWithImage("MONKEY_RUNNING", FUN_RUNNING);
	makeAnimateWithImage("MONKEY_ROPE", FUN_ROPE);
    
	return true;
}