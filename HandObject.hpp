#ifndef HANDOBJECT
#define HANDOBJECT

#include <AnnGameObject.hpp>
#include <OgreQuaternion.h>
using namespace Annwvyn;

class HandObject : public AnnGameObject
{
public:

	HandObject() : AnnGameObject()
	{
	}

	Ogre::Quaternion getWristOrientation()
	{
		Ogre::Entity* hand = this->Entity();
		assert(hand);

		Ogre::SkeletonInstance* ske;
		Ogre::Bone* wrist;
		if(ske = hand->getSkeleton())
			if(wrist = ske->getBone("Wrist"))
				return wrist->getOrientation();			
		return Ogre::Quaternion::IDENTITY;
	}
};

#endif