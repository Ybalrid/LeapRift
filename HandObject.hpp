#ifndef HANDOBJECT
#define HANDOBJECT

//#include "GrabableObject.hpp"
#include <OgreQuaternion.h>

using namespace Annwvyn;

class GrabableObject;

class LeapVisualizer;

class HandObject : public AnnGameObject
{
public:

	HandObject() : AnnGameObject()
	{
		vis = NULL;
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

	/*void grab(GrabableObject* object)
	{
		gObject = object;
		gObject->currentHandObjectHolding = this;
		object->grabed = true;
		gObject->setPos(this->pos() + gObject->getSeparationVector(getWristOrientation()));
	}
	*/

	void atRefresh();
	void setVisualizerAddress(LeapVisualizer* p)
	{
		vis = p;
	}


private:
	LeapVisualizer* vis;
	float palmRadius;
	GrabableObject* gObject;
};

#endif