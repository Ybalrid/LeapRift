#ifndef SPAWNER
#define SPAWNER

#include <AnnEngine.hpp>
#include <vector>
#include "GrabableObject.hpp"

using namespace Annwvyn;

///Spawn objects at a specific pont. Can clear all spawned object easily
class ObjectSpawner
{
public:

	///Construct the object 
	ObjectSpawner(AnnEngine* e = AnnEngine::Instance());
	///Destroy the spawner
	~ObjectSpawner();

	///Set the point in space where the objects are spwaned
	///\param point Point in space where to spawn objects
	void setSpawnPoint(Ogre::Vector3 point);
	///Get the list of spawned object
	std::vector<GrabableObject*> getList();
	
	///Set the name of the object to spawn. The name must be known by the engine resource manager
	///\param name Name of the entity to be spawned
	void setEntityName(std::string name);

	///Spawn an object
	void spawn();

	///Remove every spawned objects
	void reset();

private:
	Ogre::Vector3 spawnPoint;
	std::vector<GrabableObject*> objectList;

	AnnEngine* engine;

	std::string entityName;
};
#endif //SPAWNER