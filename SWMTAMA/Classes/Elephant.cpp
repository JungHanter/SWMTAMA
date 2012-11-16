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
	makeAnimateWithImage("ELEPHANT_WALK_LEFT", WALK_LEFT);
	makeAnimateWithImage("ELEPHANT_WALK_RIGHT", WALK_RIGHT);
	makeAnimateWithImage("ELEPHANT_WALK_BACK_LEFT", WALK_BACK_LEFT);
	makeAnimateWithImage("ELEPHANT_WALK_BACK_RIGHT", WALK_BACK_RIGHT);
	makeAnimateWithImage("ELEPHANT_RUN_LEFT", RUN_LEFT);
	makeAnimateWithImage("ELEPHANT_RUN_RIGHT", RUN_RIGHT);
	makeAnimateWithImage("ELEPHANT_RUN_BACK_LEFT", RUN_BACK_LEFT);
	makeAnimateWithImage("ELEPHANT_RUN_BACK_RIGHT", RUN_BACK_RIGHT);
	makeAnimateWithImage("ELEPHANT_STAND", STAND);
	makeAnimateWithImage("ELEPHANT_SIT", SIT);
	makeAnimateWithImage("ELEPHANT_SLEEP", SLEEP);
	makeAnimateWithImage("ELEPHANT_EAT", EAT);
	makeAnimateWithImage("ELEPHANT_POOP", POOP);
	makeAnimateWithImage("ELEPHANT_SICK", SICK);
	makeAnimateWithImage("ELEPHANT_SWING", FUN_SWING);
	makeAnimateWithImage("ELEPHANT_RUNNING", FUN_RUNNING);
	makeAnimateWithImage("ELEPHANT_ROPE", FUN_ROPE);

	return true;
}