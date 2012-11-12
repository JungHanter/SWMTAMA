#pragma once

#include "Animal.h"

class Lion : public Animal
{
private:
	virtual bool makeAnimates();

public:
	Lion(ANIMALINFO animalInfo);
	~Lion(void);
};

