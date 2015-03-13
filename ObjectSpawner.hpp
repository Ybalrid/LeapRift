#ifndef SPAWNER
#define SPAWNER

#include <AnnGameObject.hpp>
#include <AnnEngine.hpp>
#include <vector>
#include "GrabableObject.hpp"

using namespace Annwvyn;

class ObjectSpawner
{
public:
	ObjectSpawner(AnnEngine* e);
	~ObjectSpawner();
	void setSpawnPoint(Ogre::Vector3 point);
	std::vector<GrabableObject*> getList();
	
	void setEntityName(std::string name);

	void spawn();

private:
	Ogre::Vector3 spawnPoint;
	std::vector<GrabableObject*> objectList;

	AnnEngine* engine;

	std::string entityName;
};
#endif //SPAWNER