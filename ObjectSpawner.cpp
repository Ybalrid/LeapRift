#include "ObjectSpawner.hpp"

ObjectSpawner::ObjectSpawner(AnnEngine* e)
{
	assert(e);
	engine = e;
	spawnPoint = Ogre::Vector3(0, 0, 0);
}

ObjectSpawner::~ObjectSpawner()
{
	//stuff...
}

void ObjectSpawner::setSpawnPoint(Ogre::Vector3 point)
{
	spawnPoint = point;
}

std::vector<GrabableObject*> ObjectSpawner::getList()
{
	return objectList;
}

void ObjectSpawner::spawn()
{
	GrabableObject* tmp = 
		(GrabableObject*) engine->createGameObject(entityName.c_str(), new GrabableObject);
	
	objectList.push_back(tmp);
	tmp->setPos(spawnPoint);
	tmp->setUpPhysics(0.1f, sphereShape);
}

void ObjectSpawner::setEntityName(std::string name)
{
	entityName = name;
}

void ObjectSpawner::reset()
{
	for(std::vector<GrabableObject*>::iterator it = objectList.begin();
		it != objectList.end();
		++it)
		engine->destroyGameObject(*it);
	objectList.clear();
}