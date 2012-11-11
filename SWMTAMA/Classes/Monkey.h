#pragma once

#include "Animal.h"

class Monkey : public Animal
{
private:
	virtual bool makeAnimates();
    
public:
	Monkey(ANIMALINFO animalInfo);
	~Monkey(void);
};
