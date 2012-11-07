#include "Elephant.h"


Elephant::Elephant(ANIMALINFO animalInfo)
{
	initiate(animalInfo);
}


Elephant::~Elephant(void)
{
}

bool Elephant::makeAnimates()
{
	makeAnimateWithImage("ELEPHANT_WALK_LEFT.png", WALK_LEFT);
	makeAnimateWithImage("ELEPHANT_WALK_RIGHT.png", WALK_RIGHT);
	makeAnimateWithImage("ELEPHANT_WALK_BACK_LEFT.png", WALK_BACK_LEFT);
	makeAnimateWithImage("ELEPHANT_WALK_BACK_RIGHT.png", WALK_BACK_RIGHT);
	makeAnimateWithImage("ELEPHANT_RUN_LEFT.png", RUN_LEFT);
	makeAnimateWithImage("ELEPHANT_RUN_RIGHT.png", RUN_RIGHT);
	makeAnimateWithImage("ELEPHANT_RUN_BACK_LEFT.png", RUN_BACK_LEFT);
	makeAnimateWithImage("ELEPHANT_RUN_BACK_RIGHT.png", RUN_BACK_RIGHT);
	makeAnimateWithImage("ELEPHANT_STAND.png", STAND);
	makeAnimateWithImage("ELEPHANT_SIT.png", SIT);
	makeAnimateWithImage("ELEPHANT_SLEEP.png", SLEEP);
	makeAnimateWithImage("ELEPHANT_EAT.png", EAT);
	makeAnimateWithImage("ELEPHANT_POOP.png", POOP);
	makeAnimateWithImage("ELEPHANT_SICK.png", SICK);
	makeAnimateWithImage("ELEPHANT_SWING.png", FUN_SWING);
	makeAnimateWithImage("ELEPHANT_RUNNING.png", FUN_RUNNING);
	makeAnimateWithImage("ELEPHANT_ROPE.png", FUN_ROPE);

	return true;
}