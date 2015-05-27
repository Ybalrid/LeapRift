#ifndef ABSTRACTLEVEL
#define ABSTRACTLEVEL

#include <Annwvyn.h>

namespace Annwvyn
{
	//AnnEngine should really be a singleton class with a static method to get the instance... 
	class AbstractLevel
	{
	public:
		///Construct the level 
		AbstractLevel();
		
		///Pure virtual methods that loads the level
		virtual void load() = 0;

		///Destroy the level
		virtual ~AbstractLevel();
		
		///Unload the level by destroying every objects in "levelContent" and every lights in "levelLighting"
		virtual void unload();
			
		///Run logic code from the level
		virtual void runLogic() =0;

	protected:
		AnnGameObjectVect levelContent;
		AnnLightVect levelLighting;
	};
}
#endif