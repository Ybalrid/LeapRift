#include "LeapVisualizer.hpp"

using namespace Annwvyn;

LeapVisualizer::LeapVisualizer()
{
	LeapEyeOffset = Ogre::Vector3(0, 0, -0.08);

	leapOculus = Ogre::Matrix4
		(-1, 0, 0, LeapEyeOffset.x,
		0, 0, -1,  LeapEyeOffset.y,
		0, -1, 0,  LeapEyeOffset.z, 
		0, 0, 0, 1);

	scalling = Ogre::Matrix4
		(0.001, 0, 0, 0,
		0, 0.001, 0, 0,
		0, 0, 0.001, 0,
		0, 0, 0, 1);

	visualHands[left] = NULL;
	visualHands[right] = NULL;
}

void LeapVisualizer::setHandsObjects(AnnGameObject* lhand, AnnGameObject* rhand)
{
	visualHands[left] = lhand;
	visualHands[right] = rhand;
}

void LeapVisualizer::setPov(OgrePose pose)
{
	//Get a matrix4 representation of a pose.position vector
	Ogre::Matrix4 translation = Ogre::Matrix4
		(1, 0, 0, pose.position.x,
		0, 1, 0,  pose.position.y,
		0, 0, 1,   pose.position.z, 
		0, 0, 0, 1);

	//Get a matrix4 representation of a pose.orientation quaternion	
	Ogre::Matrix4 rotation(pose.orientation);

	currentPov = translation * rotation;
}

Ogre::Matrix4 LeapVisualizer::getProjectionFromCurrentPose()
{
	Ogre::Matrix4 leapWorld = currentPov * leapOculus;
	return leapWorld * scalling;
}

void LeapVisualizer::updateHandPosition(Leap::Hand lhand, Leap::Hand rhand)
{
	if(lhand.isValid() && visualHands[left])
	{
		visualHands[left]->node()->setVisible(true);
		Leap::Vector handPosition = lhand.palmPosition();

		Ogre::Vector4 position(handPosition.x, handPosition.y, handPosition.z, 1);
		position = getProjectionFromCurrentPose() * position;

		visualHands[left]->setPos(position.x, position.y, position.z);
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
	}
	else if(visualHands[right])
	{
		visualHands[right]->node()->setVisible(false);
	}
}