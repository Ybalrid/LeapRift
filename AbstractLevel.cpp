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
	AnnEngine::Instance()->removeSkyDome();
	AnnGameObjectVect::iterator it;
	for(it = levelContent.begin(); it != levelContent.end(); ++it)
		AnnEngine::Instance()->destroyGameObject(*it);

	levelContent.clear();
}