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

	///Get the orientation of the wrist bone
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

	///Set the radius of the palm
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

	///Call any known visualizer + compute events
	void atRefresh();
	
	///Set a pointer to a visualizer
	///\param p pointer to visualizer
	void setVisualizerAddress(LeapVisualizer* p)
	{
		vis = p;
	}

	///Set the type of the hand
	///\param stype type of the hand. may be "right" or "left"
	void setType(std::string stype)
	{
		type = stype;
	}

	///Register a listener to the event listener
	///\param listener pointer to a listener
	void registerListener(LeapEventListener* listener)
	{
		if(listener)
			listeners.push_back(listener);
	}

	///Forget all known listeners
	void unregisterAllListeners()
	{
		listeners.clear();
	}

	///Unregister a particular listener
	///\param listener pointer to that listener
	void unregisterListener(LeapEventListener* listener);

	///Notify all event listener about a listener
	///\param e LeapEvent pointer to an event
	///\param eventType The type of the event
	void notifyListener(LeapEvent* e, LeapEventType eventType)
	{
		std::vector<LeapEventListener*>::iterator it;
		for(it = listeners.begin(); it != listeners.end(); it++)
		{
			(*it)->notifyEvent(e, eventType);
		}
	}

private:
	///List of listener
	std::vector<LeapEventListener*> listeners;
	///Vizualizer to update
	LeapVisualizer* vis;
	///Radius of the palm
	float palmRadius;
	///Object grabbed by the hand
	GrabableObject* gObject;
	///true if the hand is closed
	bool closed;
	///Type of the hand. "right" or "left".
	std::string type;
};

#endif