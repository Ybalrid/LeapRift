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

		static Ogre::Vector3 convert(Leap::Vector v);

	private:
		enum {left, right};
		AnnGameObject* visualHands[2];

		Ogre::Vector3 LeapEyeOffset;
		Ogre::Matrix4 currentPov;
		Ogre::Matrix4 leapOculus;
		Ogre::Matrix4 scalling;

		OgrePose lPose;
		void updateHandOrientation(Leap::Hand lhand, Leap::Hand rhand);
		void updateFingerPose(Leap::Hand lhand, Leap::Hand rhand);

		Ogre::Quaternion getBoneOrientation(Leap::Bone bone, bool isLeft = false);
		std::string getBoneName(int finger, int bone);

		void manageSize(Leap::Hand l, Leap::Hand r);

		bool lSizeApplied;
		bool rSizeApplied;


		Ogre::Quaternion lwrist, rwrist;

	};
}

#endif