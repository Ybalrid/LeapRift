#include "AbstractLevel.hpp"
#include <AnnEngine.hpp>

using namespace Annwvyn;

AbstractLevel::AbstractLevel()
{
	AnnEngine::Instance()->log("A level has been created");
}

AbstractLevel::~AbstractLevel()
{
	unload();
	AnnEngine::Instance()->log("Destroying a level");
}

void AbstractLevel::unload()
{
	//Remove the sky
	AnnEngine::Instance()->removeSkyDome();

	//Remove the ambiant lighting
	AnnEngine::Instance()->setAmbiantLight(Ogre::ColourValue::Black);
	
	//Remove the level lights
	for(AnnLightVect::iterator it = levelLighting.begin(); it != levelLighting.end(); ++it)
		AnnEngine::Instance()->getSceneManager()->destroyLight(*it);
	levelLighting.clear();

	//Remove the level objects
	for(AnnGameObjectVect::iterator it = levelContent.begin(); it != levelContent.end(); ++it)
		AnnEngine::Instance()->destroyGameObject(*it);
	levelContent.clear();
}