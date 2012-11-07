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
	makeAnimateWithImage("LION_WALK_LEFT.png", WALK_LEFT);
	makeAnimateWithImage("LION_WALK_RIGHT.png", WALK_RIGHT);
	makeAnimateWithImage("LION_WALK_BACK_LEFT.png", WALK_BACK_LEFT);
	makeAnimateWithImage("LION_WALK_BACK_RIGHT.png", WALK_BACK_RIGHT);
	makeAnimateWithImage("LION_RUN_LEFT.png", RUN_LEFT);
	makeAnimateWithImage("LION_RUN_RIGHT.png", RUN_RIGHT);
	makeAnimateWithImage("LION_RUN_BACK_LEFT.png", RUN_BACK_LEFT);
	makeAnimateWithImage("LION_RUN_BACK_RIGHT.png", RUN_BACK_RIGHT);
	makeAnimateWithImage("LION_STAND.png", STAND);
	makeAnimateWithImage("LION_SIT.png", SIT);
	makeAnimateWithImage("LION_SLEEP.png", SLEEP);
	makeAnimateWithImage("LION_EAT.png", EAT);
	makeAnimateWithImage("LION_POOP.png", POOP);
	makeAnimateWithImage("LION_SICK.png", SICK);
	makeAnimateWithImage("LION_SWING.png", FUN_SWING);
	makeAnimateWithImage("LION_RUNNING.png", FUN_RUNNING);
	makeAnimateWithImage("LION_ROPE.png", FUN_ROPE);

	return true;
}