#include "AbstractLevel.hpp"
#include <AnnEngine.hpp>

using namespace Annwvyn;

AbstractLevel::AbstractLevel()
{

}

AbstractLevel::~AbstractLevel()
{
	unload();
}

void AbstractLevel::unload()
{
	AnnGameObjectVect::iterator it;
	for(it = levelContent.begin(); it != levelContent.end(); ++it)
		AnnEngine::Instance()->destroyGameObject(*it);

	levelContent.clear();
}