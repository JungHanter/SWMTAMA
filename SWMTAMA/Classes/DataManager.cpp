#include "DataManager.h"

DataManager* DataManager::create()
{
	return new DataManager;
}

DataManager::DataManager()
{
	pointedAnimalKey = -1;
	lastPointedAnimalKey = pointedAnimalKey;
}

void DataManager::release()
{
	for( map<int, map<int, Animal*>*>::iterator accountIter = AnimalData.begin();
		accountIter != AnimalData.end(); accountIter++ )
	{
		for( map<int, Animal*>::iterator animalIter = accountIter->second->begin();
			animalIter != accountIter->second->end(); animalIter++ )
		{
			delete animalIter->second;
		}
		delete accountIter->second;
	}
}

void DataManager::frame(CCLayer *pLayer, float dt)
{
    setZOrders(pLayer, dt);
}

Animal* DataManager::getAnimalByAnimalKey(int accountKey, int animalKey)
{
	if( AnimalData.find(accountKey) == AnimalData.end() ) return NULL;
	if( AnimalData[accountKey]->find(animalKey) == AnimalData[accountKey]->end() ) return NULL;
	return (*AnimalData[accountKey])[animalKey];
}

map<int, Animal*>* DataManager::getAnimalsByAccount(int accountKey)
{
	if( AnimalData.find(accountKey) == AnimalData.end() ) return NULL;

	return AnimalData[accountKey];
}

void DataManager::makeDataFromAnimalInfo(int accountKey, ANIMALINFO animalInfo)
{
	if( AnimalData.find(accountKey) == AnimalData.end() )
		AnimalData[accountKey] = new map<int, Animal*>;

	map<int, Animal*>* pAnimalList = AnimalData[accountKey];
	if( pAnimalList->find(animalInfo.key) == pAnimalList->end() )
	{
		switch(animalInfo.type)
		{
		case LION:
			(*pAnimalList)[animalInfo.key] = new Lion(animalInfo);
			break;
		case ELEPHANT:
			(*pAnimalList)[animalInfo.key] = new Elephant(animalInfo);
			break;
		case MONKEY:
			(*pAnimalList)[animalInfo.key] = new Monkey(animalInfo);
			break;
		//case SQUIRREL:
		//	(*pAnimalList)[animalInfo.key] = new Squirrel(animalInfo);
		//	break;
		}
	}
}

void DataManager::setPointedAnimal(int accountKey, int animalKey)
{
	if( animalKey != -1 )
		lastPointedAnimalKey = animalKey;
	pointedAnimalKey = animalKey;
}

int DataManager::getPointedAnimal(int accountKey)
{
	return pointedAnimalKey;
}

int DataManager::getLastPointedAnimal(int accountKey)
{
	return lastPointedAnimalKey;
}

int DataManager::findAnimalRectContainsPoint(int accountKey, CCPoint touch)
{
	if( AnimalData.find(accountKey) == AnimalData.end() ) return -1;
	//if( lastPointedAnimalKey != -1 ) return lastPointedAnimalKey;
	for( map<int, map<int, Animal*>*>::iterator accountIter = AnimalData.begin();
		accountIter != AnimalData.end(); accountIter++ )
	{
		for( map<int, Animal*>::iterator animalIter = accountIter->second->begin();
			animalIter != accountIter->second->end(); animalIter++ )
		{
			if( CCRect::CCRectContainsPoint( animalIter->second->getSprite()->boundingBox(), touch ) )
			{
				return animalIter->first;
			}
		}
	}
	return -1;
}

void DataManager::setZOrders(cocos2d::CCLayer *pLayer, float dt)
{
    for( map<int, map<int, Animal*>*>::iterator accountIter = AnimalData.begin();
		accountIter != AnimalData.end(); accountIter++ )
	{
		for( map<int, Animal*>::iterator animalIter = accountIter->second->begin();
			animalIter != accountIter->second->end(); animalIter++ )
		{
            int zorder = 800;
            zorder -= animalIter->second->getSprite()->getPosition().y - animalIter->second->getSprite()->getContentSize().height/2;
			pLayer->reorderChild(animalIter->second->getSprite(), zorder);
		}
	}
}
