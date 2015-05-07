#ifndef LEVELMANAGER
#define LEVELMANAGER

//#include <Annwvyn.h>

#include "AbstractLevel.hpp"


namespace Annwvyn
{
	typedef size_t level_id;

	class LevelManager
	{
	public:
		LevelManager();
		~LevelManager();

		void jump(size_t levelId);
		void jump(AbstractLevel* level);
		
		void addLevel(AbstractLevel* level);
		
		void jumpToFirstLevel();

		void tick();

		void unloadCurrentLevel();

	private:
		std::vector<AbstractLevel*> levelList;
		AbstractLevel* current;
	};
}
#endif LEVELMANAGER