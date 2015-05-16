#include "stdafx.h"
#include "GrabableObject.hpp"

using namespace Annwvyn;

GrabableObject::GrabableObject()
{
	grabed = false;
	holder = NULL;
	radius = 0;
	margin = 0.01f;
}

bool GrabableObject::isGrabed()
{
	return grabed;
}

HandObject* GrabableObject::currentHandObjectHolding()
{
	return holder;
}

void GrabableObject::setObjectRadius(float r)
{
	radius = r;
}

Ogre::Vector3 GrabableObject::getSeparationVector(Ogre::Quaternion handOrient)
{
	return handOrient* Ogre::Vector3(0, radius + margin, 0);
}

