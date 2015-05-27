#ifndef LEVELMANAGER
#define LEVELMANAGER

//#include <Annwvyn.h>

#include "AbstractLevel.hpp"


namespace Annwvyn
{
	typedef size_t level_id;

	///Class that take care of switching between differents levels dynamicly and clearing the memory afterwards
	class LevelManager
	{
	public:
		///Construct LevelManager
		LevelManager();
		///Destroy the level manager
		~LevelManager();

		///Jump to an index referenced level
		///\param levelId Index of the level in the order they have been declraed
		void jump(level_id levelId);
		///Jump to a pointer referenced level
		///\param level address of a subclass instance of AbstractLevel
		void jump(AbstractLevel* level);
		///Add a level to the level manager
		///\param level address of a subclass instance of AbstractLevel
		void addLevel(AbstractLevel* level);
		///Jumpt to the 1st level
		void jumpToFirstLevel();
		///Run level logic
		void step();
		///Unload the level currently running
		void unloadCurrentLevel();

	private:
		///List of levels
		std::vector<AbstractLevel*> levelList;
		///Address to the currently running level
		AbstractLevel* current;
	};
}
#endif LEVELMANAGER