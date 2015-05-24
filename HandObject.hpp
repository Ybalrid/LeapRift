#ifndef HANDOBJECT
#define HANDOBJECT

//#include "GrabableObject.hpp"
#include <OgreQuaternion.h>
#include "LeapEvent.hpp"


using namespace Annwvyn;

class GrabableObject;

class LeapVisualizer;

class HandObject : public AnnGameObject
{
public:

	HandObject() : AnnGameObject()
	{
		type = "unkonwn";
		vis = NULL;
		closed = false;
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
		/*
		std::stringstream ss;
		ss << (void*)this << " palm radius : " << palmRadius;
		AnnEngine::Instance()->log(ss.str());*/
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

	void setType(std::string stype)
	{
		type = stype;
	}

	void registerListener(LeapEventListener* listener)
	{
		if(listener)
			listeners.push_back(listener);
	}

	void unregisterAllListeners()
	{
		listeners.clear();
	}

	void unregisterListener(LeapEventListener* listener);


	void notifyListener(LeapEvent* e, LeapEventType eventType)
	{
		std::vector<LeapEventListener*>::iterator it;
		for(it = listeners.begin(); it != listeners.end(); it++)
		{
			(*it)->notifyEvent(e, eventType);
		}
	}

private:
	std::vector<LeapEventListener*> listeners;
	LeapVisualizer* vis;
	float palmRadius;
	GrabableObject* gObject;
	bool closed;
	std::string type;
};

#endif