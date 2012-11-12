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
	makeAnimateWithImage("MONKEY_WALK_LEFT.png", WALK_LEFT);
	makeAnimateWithImage("MONKEY_WALK_RIGHT.png", WALK_RIGHT);
	makeAnimateWithImage("MONKEY_WALK_BACK_LEFT.png", WALK_BACK_LEFT);
	makeAnimateWithImage("MONKEY_WALK_BACK_RIGHT.png", WALK_BACK_RIGHT);
	makeAnimateWithImage("MONKEY_RUN_LEFT.png", RUN_LEFT);
	makeAnimateWithImage("MONKEY_RUN_RIGHT.png", RUN_RIGHT);
	makeAnimateWithImage("MONKEY_RUN_BACK_LEFT.png", RUN_BACK_LEFT);
	makeAnimateWithImage("MONKEY_RUN_BACK_RIGHT.png", RUN_BACK_RIGHT);
	makeAnimateWithImage("MONKEY_STAND.png", STAND);
	makeAnimateWithImage("MONKEY_SIT.png", SIT);
	makeAnimateWithImage("MONKEY_SLEEP.png", SLEEP);
	makeAnimateWithImage("MONKEY_EAT.png", EAT);
	makeAnimateWithImage("MONKEY_POOP.png", POOP);
	makeAnimateWithImage("MONKEY_SICK.png", SICK);
	makeAnimateWithImage("MONKEY_SWING.png", FUN_SWING);
	makeAnimateWithImage("MONKEY_RUNNING.png", FUN_RUNNING);
	makeAnimateWithImage("MONKEY_ROPE.png", FUN_ROPE);
    
	return true;
}