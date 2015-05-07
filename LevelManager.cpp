#include "LevelManager.hpp"

using namespace Annwvyn;

LevelManager::LevelManager():
	current(NULL)
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::jump(size_t levelId)
{
	if(!(levelId < levelList.size())) return;
	if(current)
		current->unload();
	current = levelList[levelId];
	current->load();
}



void LevelManager::jump(AbstractLevel* level)
{
	for(size_t i(0); i < levelList.size(); i++)
		if(levelList[i] == level)
		{
			jump(i);
			break;
		}
}

void LevelManager::addLevel(AbstractLevel* level)
{
	if(!level) return;
	levelList.push_back(level);
}

void LevelManager::jumpToFirstLevel()
{
	jump(level_id(0));
}

void LevelManager::tick()
{
	if(current) current->runLogic();
}

void LevelManager::unloadCurrentLevel()
{
	if(current) current->unload();
	current = NULL;
}