#pragma once

#include "Lion.h"
#include "Elephant.h"
#include "Monkey.h"
#include "Squirrel.h"

using namespace std;

struct ANIMALINDEX
{
    int accountKey;
    int animalKey;
    ANIMALINDEX(){}
    ANIMALINDEX(int _accountKey, int _animalKey)
    : accountKey(_accountKey), animalKey(_animalKey) {}
};

class DataManager
{
private:
	map<int, map<int, Animal*>*> AnimalData;
    vector< pair<int, string> > userFriendList;
    //map<int, int> num_of_Animal;
	ANIMALINDEX pointedAnimalKey;
	ANIMALINDEX lastPointedAnimalKey;

public:
	static DataManager* create();
	void release();
    void frame(cocos2d::CCLayer* pLayer, float dt);
    
public:
	Animal* getAnimalByAnimalKey(ANIMALINDEX index);
	map<int, Animal*>* getAnimalsByAccount(int accountKey);
	void makeDataFromAnimalInfo(int accountKey, ANIMALINFO animalInfo);
	void setPointedAnimal(ANIMALINDEX index);
	ANIMALINDEX getPointedAnimal();
	ANIMALINDEX getLastPointedAnimal();
	ANIMALINDEX findAnimalRectContainsPoint(cocos2d::CCPoint touch);
    void setZOrders(cocos2d::CCLayer *pLayer, float dt);
    int getNewAnimalKey(int accountKey);
    void addChildToLayer(cocos2d::CCLayer *pLayer, int _hostAccountKey);
    
    void addFriend(int accountKey, string ID);
    void deleteFriend();
    vector< pair<int, string> >* getFriendList();
    
public:
	DataManager();
};

