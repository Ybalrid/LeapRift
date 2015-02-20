#ifndef LEAP_VIZUALIZER
#define LEAP_VIZUALIZER

#include <Leap.h>
#include <Annwvyn.h>

namespace Annwvyn
{
	class LeapVisualizer
	{
	public:
		LeapVisualizer();
		void setPov(OgrePose pose);
		void updateHandPosition(Leap::Hand lhand, Leap::Hand rhand);
		void setHandsObjects(AnnGameObject* lhand, AnnGameObject* rhand);
		Ogre::Matrix4 getProjectionFromCurrentPose();


	private:
		enum {left, right};
		AnnGameObject* visualHands[2];

		Ogre::Vector3 LeapEyeOffset;
		Ogre::Matrix4 currentPov;
		Ogre::Matrix4 leapOculus;
		Ogre::Matrix4 scalling;

	};
}

#endif