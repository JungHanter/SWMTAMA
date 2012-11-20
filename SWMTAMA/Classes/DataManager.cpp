#include "DataManager.h"
#include "SceneManager.h"

DataManager* DataManager::create()
{
	return new DataManager;
}

DataManager::DataManager()
{
	pointedAnimalKey.accountKey = -1;
	pointedAnimalKey.animalKey = -1;
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
    for( map<int, map<int, Animal*>*>::iterator accountIter = AnimalData.begin();
		accountIter != AnimalData.end(); accountIter++ )
	{
        for( map<int, Animal*>::iterator animalIter = accountIter->second->begin();
			animalIter != accountIter->second->end(); animalIter++ )
		{
			if( accountIter->first != SceneManager::sharedSceneManager()->getHostAccountKey() )
			{
                animalIter->second->getSprite()->setVisible(false);
            }
            else
            {
                animalIter->second->getSprite()->setVisible(true);
                animalIter->second->frame(dt);
            }
            
		}
	}
}

Animal* DataManager::getAnimalByAnimalKey(ANIMALINDEX index)
{
	if( AnimalData.find(index.accountKey) == AnimalData.end() ) return NULL;
	if( AnimalData[index.accountKey]->find(index.animalKey) == AnimalData[index.accountKey]->end() ) return NULL;
	return (*AnimalData[index.accountKey])[index.animalKey];
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
		case SQUIRREL:
			(*pAnimalList)[animalInfo.key] = new Squirrel(animalInfo);
			break;
		}
	}
}

void DataManager::setPointedAnimal(ANIMALINDEX index)
{
	if( index.animalKey != -1 )
    {
        lastPointedAnimalKey.accountKey = index.accountKey;
		lastPointedAnimalKey.animalKey = index.animalKey;
	}
    pointedAnimalKey.accountKey = index.accountKey;
    pointedAnimalKey.animalKey = index.animalKey;
}

ANIMALINDEX DataManager::getPointedAnimal()
{
	return pointedAnimalKey;
}

ANIMALINDEX DataManager::getLastPointedAnimal()
{
	return lastPointedAnimalKey;
}

ANIMALINDEX DataManager::findAnimalRectContainsPoint(CCPoint touch)
{
	for( map<int, map<int, Animal*>*>::iterator accountIter = AnimalData.begin();
		accountIter != AnimalData.end(); accountIter++ )
	{
		for( map<int, Animal*>::iterator animalIter = accountIter->second->begin();
			animalIter != accountIter->second->end(); animalIter++ )
		{
			if( animalIter->second->getSprite()->isVisible() && CCRect::CCRectContainsPoint( animalIter->second->getSprite()->boundingBox(), touch ) )
			{
				return ANIMALINDEX(accountIter->first, animalIter->first);
			}
		}
	}
	return ANIMALINDEX(-1,-1);
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

int DataManager::getNewAnimalKey(int accountKey)
{
    if( AnimalData.find(accountKey) == AnimalData.end() ) return -1;
    return AnimalData[accountKey]->size() + 1;
}

void DataManager::addChildToLayer(cocos2d::CCLayer *pLayer, int _hostAccountKey)
{
    if( AnimalData.find(_hostAccountKey) == AnimalData.end() )
		AnimalData[_hostAccountKey] = new map<int, Animal*>;
    srand(time(NULL));
	map<int, Animal*>* pAnimalList = AnimalData[_hostAccountKey];
    for( map<int, Animal*>::iterator animalIter = pAnimalList->begin(); animalIter != pAnimalList->end(); animalIter++ )
    {
        CCPoint point;
        pLayer->addChild(animalIter->second->getSprite());
    }
}

void DataManager::addFriend(int accountKey, string ID)
{
    bool isAlreadyExist = false;
    for (vector< pair<int, string> >::iterator iter = userFriendList.begin(); iter != userFriendList.end(); iter++)
        if( iter->first == accountKey )
            isAlreadyExist = true;
    
    if( !isAlreadyExist )
        userFriendList.push_back(make_pair(accountKey, ID));
}

void DataManager::deleteFriend()
{
    userFriendList.clear();
}

vector< pair<int, string> >* DataManager::getFriendList()
{
    return &userFriendList;
}



