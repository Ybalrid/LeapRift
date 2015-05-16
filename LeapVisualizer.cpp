#include "stdafx.h"
#include "LeapVisualizer.hpp"
#include <sstream>
using namespace Annwvyn;

LeapVisualizer::LeapVisualizer()
{
	LeapEyeOffset = Ogre::Vector3(0, 0, -0.08f);

	leapOculus = Ogre::Matrix4
		(-1, 0, 0, LeapEyeOffset.x,
		0, 0, -1,  LeapEyeOffset.y,
		0, -1, 0,  LeapEyeOffset.z, 
		0, 0, 0, 1);

	scalling = Ogre::Matrix4
		(0.001f, 0, 0, 0,
		0, 0.001f, 0, 0,
		0, 0, 0.001f, 0,
		0, 0, 0, 1);

	visualHands[left] = NULL;
	visualHands[right] = NULL;
	lSizeApplied = false;
	rSizeApplied = false;
}

void LeapVisualizer::setHandsObjects(HandObject* lhand, HandObject* rhand)
{
	visualHands[left] = lhand;
	visualHands[right] = rhand;
}

void LeapVisualizer::setPov(OgrePose pose)
{
	//Get a matrix4 representation of a pose.position vector
	Ogre::Matrix4 translation = Ogre::Matrix4
		(1, 0, 0,  pose.position.x,
		0, 1, 0,   pose.position.y,
		0, 0, 1,   pose.position.z, 
		0, 0, 0, 1);

	//Get a matrix4 representation of a pose.orientation quaternion	
	Ogre::Matrix4 rotation(pose.orientation);

	currentPov = translation * rotation;

	lPose = pose;
}

Ogre::Matrix4 LeapVisualizer::getProjectionFromCurrentPose()
{
	Ogre::Matrix4 leapWorld = currentPov * leapOculus;
	return leapWorld * scalling;
}

void LeapVisualizer::manageSize(Leap::Hand lhand, Leap::Hand rhand)
{
	Ogre::Real modelPalmWidth = 0.04f;
	if(!lSizeApplied)
		if(lhand.isValid() && visualHands[left])
		{
			Ogre::Vector3 mesuredSize = (lhand.palmWidth()/1000) * Ogre::Vector3::UNIT_SCALE;

			visualHands[left]->setScale(mesuredSize*(visualHands[left]->node()->getScale()/modelPalmWidth));

			lSizeApplied = true;
		}

		if(!rSizeApplied)
			if(rhand.isValid() && visualHands[right])
			{
				Ogre::Vector3 mesuredSize = (rhand.palmWidth()/1000) * Ogre::Vector3::UNIT_SCALE;

				visualHands[right]->setScale(mesuredSize*(visualHands[right]->node()->getScale()/modelPalmWidth));

				rSizeApplied = true;
			}
}

void LeapVisualizer::updateHandPosition(Leap::Hand lhand, Leap::Hand rhand)
{
	manageSize(lhand, rhand);
	if(lhand.isValid() && visualHands[left])
	{
		visualHands[left]->node()->setVisible(true);
		Leap::Vector handPosition = lhand.palmPosition();

		Ogre::Vector4 position(handPosition.x, handPosition.y, handPosition.z, 1);
		position = getProjectionFromCurrentPose() * position;

		visualHands[left]->setPos(position.x, position.y, position.z);

		visualHands[left]->setPalmRadius(lhand.sphereRadius());
	}
	else if(visualHands[left])
	{
		visualHands[left]->node()->setVisible(false);
	}
	if(rhand.isValid() && visualHands[right])
	{
		visualHands[right]->node()->setVisible(true);

		Leap::Vector handPosition = rhand.palmPosition();

		Ogre::Vector4 position(handPosition.x, handPosition.y, handPosition.z, 1);
		position = getProjectionFromCurrentPose() * position;

		visualHands[right]->setPos(position.x, position.y, position.z);
		visualHands[right]->setPalmRadius(rhand.sphereRadius());

	}
	else if(visualHands[right])
	{
		visualHands[right]->node()->setVisible(false);
	}

	updateHandOrientation(lhand, rhand);
}

void LeapVisualizer::updateHandOrientation(Leap::Hand lhand, Leap::Hand rhand)
{
	if(lhand.isValid() && visualHands[left])
	{
		//Get vectors from the LEAP hand object
		Leap::Vector normal(lhand.palmNormal());
		Leap::Vector direction(lhand.direction());

		//Reorient them to a local base "attached on the rift"
		normal = Leap::Vector(-normal.x, -normal.z, -normal.y);
		direction = Leap::Vector(-direction.x, -direction.z, -direction.y);

		//Get the "world-space" projection (and in the same time convert object to OGRE classes ;-) )
		Ogre::Vector3 projectedNormal = lPose.orientation*Ogre::Vector3(normal.x, normal.y, normal.z);
		Ogre::Vector3 projectedDirection = lPose.orientation*Ogre::Vector3(direction.x, direction.y, direction.z);

		//Make them unit vectors (norm = 1)
		projectedNormal.normalise();
		projectedDirection.normalise();

		//Calculate a cathesian base oriented like the hand
		Ogre::Vector3 Y = -projectedNormal;
		Ogre::Vector3 Z = -projectedDirection;
		Ogre::Vector3 X = Y.crossProduct(Z);


		//Get the corresponding quaternion and apply it to the hand
		//visualHands[left]->setOrientation(Ogre::Quaternion(X,Y,Z));
		lwrist = Ogre::Quaternion(X,Y,Z);
	}

	if(rhand.isValid() && visualHands[right])
	{
		//Get vectors from the LEAP hand object
		Leap::Vector normal(rhand.palmNormal());
		Leap::Vector direction(rhand.direction());

		//Reorient them to a local base "attached on the rift"
		normal = Leap::Vector(-normal.x, -normal.z, -normal.y);
		direction = Leap::Vector(-direction.x, -direction.z, -direction.y);

		//Get the "world-space" projection (and in the same time convert object to OGRE classes ;-) )
		Ogre::Vector3 projectedNormal = lPose.orientation*Ogre::Vector3(normal.x, normal.y, normal.z);
		Ogre::Vector3 projectedDirection = lPose.orientation*Ogre::Vector3(direction.x, direction.y, direction.z);

		//Make them unit vectors (norm = 1)
		projectedNormal.normalise();
		projectedDirection.normalise();

		//Calculate a cathesian base oriented like the hand
		Ogre::Vector3 Y = -projectedNormal;
		Ogre::Vector3 Z = -projectedDirection;
		Ogre::Vector3 X = Y.crossProduct(Z);


		//Get the corresponding quaternion and apply it to the hand
		//visualHands[right]->setOrientation(Ogre::Quaternion(X,Y,Z));
		rwrist = Ogre::Quaternion(X,Y,Z);
	}
	updateFingerPose(lhand, rhand);
}


void LeapVisualizer::updateFingerPose(Leap::Hand lhand, Leap::Hand rhand)
{
	/*visualHands[left]->setScale(1.5f*Ogre::Vector3::UNIT_SCALE);
	visualHands[right]->setScale(1.5f*Ogre::Vector3::UNIT_SCALE);*/
	Ogre::SkeletonInstance* ske;
	if(!visualHands[left]->Entity()->hasSkeleton()) return;
	ske = visualHands[left]->Entity()->getSkeleton();
	Ogre::Bone* wrist(ske->getBone("Wrist"));
	wrist->setManuallyControlled(true);
	wrist->setInheritOrientation(false);
	wrist->setOrientation(lwrist*Ogre::Quaternion(Ogre::Degree(65), Ogre::Vector3::UNIT_Y));

	for(int fingerIndex(0); fingerIndex < 5; fingerIndex++)
	{
		for(int boneIndex(1); boneIndex < 4; boneIndex++)
		{
			Leap::Finger finger(lhand.fingers()[fingerIndex]);
			Leap::Bone bone(finger.bone(Leap::Bone::Type(boneIndex)));
			Ogre::Bone *b = ske->getBone(getBoneName(fingerIndex, boneIndex));
			b->setManuallyControlled(true);
			b->setInheritOrientation(false);

			Ogre::Quaternion boneOrientation(getBoneOrientation(bone, true));
			if(fingerIndex != 0)
				b->setOrientation(lPose.orientation
				*boneOrientation
				/**Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X)*/
				*Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Z)
				*Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X)
				);
			else
				b->setOrientation(lPose.orientation
				*boneOrientation
				//	*Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_X)
				*Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X)
				*Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y)
				);
		}
	}

	if(!visualHands[right]->Entity()->hasSkeleton()) return;

	ske = visualHands[right]->Entity()->getSkeleton();
	wrist=ske->getBone("Wrist");
	wrist->setManuallyControlled(true);
	wrist->setInheritOrientation(false);
	wrist->setOrientation(rwrist*Ogre::Quaternion(Ogre::Degree(65), Ogre::Vector3::NEGATIVE_UNIT_Y));

	for(int fingerIndex(0); fingerIndex < 5; fingerIndex++)
	{
		for(int boneIndex(1); boneIndex < 4; boneIndex++)
		{
			Leap::Finger finger(rhand.fingers()[fingerIndex]);
			Leap::Bone bone(finger.bone(Leap::Bone::Type(boneIndex)));
			Ogre::Bone *b = ske->getBone(getBoneName(fingerIndex, boneIndex));
			b->setManuallyControlled(true);
			b->setInheritOrientation(false);

			Ogre::Quaternion boneOrientation(getBoneOrientation(bone, false));
			if(fingerIndex != 0)
				b->setOrientation(lPose.orientation
				*boneOrientation
				/**Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X)*/
				*Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Z)
				*Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X)
				);
			else
				b->setOrientation(lPose.orientation
				*boneOrientation
				*Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Z)
				*Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X)
				*Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y)
				);
		}
	}
}

Ogre::Quaternion LeapVisualizer::getBoneOrientation(Leap::Bone bone, bool isLeft)
{
	Leap::Matrix rotationMatrix(bone.basis());

	Leap::Vector xBasis = rotationMatrix.xBasis;
	Leap::Vector yBasis = rotationMatrix.yBasis;
	Leap::Vector zBasis = rotationMatrix.zBasis;
	if(isLeft)
		xBasis = - xBasis;

	xBasis = Leap::Vector(-xBasis.x, -xBasis.z, -xBasis.y);
	yBasis = Leap::Vector(-yBasis.x, -yBasis.z, -yBasis.y);
	zBasis = Leap::Vector(-zBasis.x, -zBasis.z, -zBasis.y);

	return Ogre::Quaternion(convert(xBasis).normalisedCopy(), convert(yBasis).normalisedCopy(), convert(zBasis).normalisedCopy());
}

std::string LeapVisualizer::getBoneName(int finger, int bone)
{
	std::stringstream ss;
	ss << "Finger_";
	ss << finger;
	ss << bone - 1;

	return ss.str();
}

Ogre::Vector3 LeapVisualizer::convert(Leap::Vector v)
{
	return Ogre::Vector3(v.x, v.y, v.z);
}
