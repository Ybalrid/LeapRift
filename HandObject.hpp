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

	void setPalmRadius(float radius)
	{
		palmRadius = radius/1000;
		std::stringstream ss;
		ss << (void*)this << " palm radius : " << palmRadius;
		AnnEngine::Instance()->log(ss.str());
	}

private:
	float palmRadius;
};

#endif