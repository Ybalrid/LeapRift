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
		///Object that can be grabbed by an hand
		GrabableObject();
		///Grabbed state
		bool isGrabed();
		///The hand that is holding this obect
		HandObject* currentHandObjectHolding();
		///Radius of that object
		void setObjectRadius(float r);

		///Distance between object center and the hand center, oriented following the hand
		Ogre::Vector3 getSeparationVector(Ogre::Quaternion handOrientation = AnnQuaternion::IDENTITY);

	private:
		//friend void HandObject::grab(GrabableObject*);

		bool grabed;
		HandObject* holder;
		float radius;
		float margin;

};
#endif //GRABABLE