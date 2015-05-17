#ifndef GRABABLE
#define GRABABLE
#include <AnnGameObject.hpp>
#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <AnnTools.h>
#include "HandObject.hpp"

using namespace Annwvyn;

class GrabableObject : public AnnGameObject
{
	public:
		GrabableObject();
		bool isGrabed();
		HandObject* currentHandObjectHolding();
		void setObjectRadius(float r);

		Ogre::Vector3 getSeparationVector(Ogre::Quaternion handOrientation);

	private:
		//friend void HandObject::grab(GrabableObject*);

		bool grabed;
		HandObject* holder;
		float radius;
		float margin;

};
#endif //GRABABLE