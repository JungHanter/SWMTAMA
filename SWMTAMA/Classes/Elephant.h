#pragma once

#include "Animal.h"

class Elephant : public Animal
{
private:
	virtual bool makeAnimates();

public:
	Elephant(ANIMALINFO animalInfo);
	~Elephant(void);
};

