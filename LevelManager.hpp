#ifndef LEVELMANAGER
#define LEVELMANAGER

#include <Annwvyn.h>

#include "AbstractLevel.hpp"
namespace Annwvyn
{
	class LevelManager
	{
	public:
		LevelManager();
		~LevelManager();

	private:
		std::vector<AbstractLevel*> levelList;
	};
}
#endif LEVELMANAGER