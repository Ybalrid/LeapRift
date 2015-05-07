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

		virtual void load() = 0;

		///Destroy the level
		virtual ~AbstractLevel();
		virtual void unload();

		virtual void runLogic() =0;

	protected:
		AnnGameObjectVect levelContent;
	};
}
#endif