#pragma once

#include "Animal.h"

class Squirrel : public Animal
{
private:
	virtual bool makeAnimates();
    
public:
	Squirrel(ANIMALINFO animalInfo);
	~Squirrel(void);
};

