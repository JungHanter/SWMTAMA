#pragma once

#include "Lion.h"
#include "Elephant.h"
#include "Monkey.h"
#include "Squirrel.h"

using namespace std;

class DataManager
{
private:
	map<int, map<int, Animal*>*> AnimalData;
	int pointedAnimalKey;
	int lastPointedAnimalKey;

public:
	static DataManager* create();
	void release();

public:
	Animal* getAnimalByAnimalKey(int accountKey, int animalKey);
	map<int, Animal*>* getAnimalsByAccount(int accountKey);
	void makeDataFromAnimalInfo(int accountKey, ANIMALINFO animalInfo);
	void setPointedAnimal(int accountKey, int animalKey);
	int getPointedAnimal(int accountKey);
	int getLastPointedAnimal(int accountKey);
	int findAnimalRectContainsPoint(int accountKey, cocos2d::CCPoint touch);

public:
	DataManager();
};

