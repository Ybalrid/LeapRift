#ifndef LEAP_VIZUALIZER
#define LEAP_VIZUALIZER

#include <Leap.h>
#include <Annwvyn.h>
#include "HandObject.hpp"
#include "LeapIntegration.hpp"

///Class that updates hand object with information from the LEAP Interface
class LeapVisualizer
{
public:
	///Construct the visualizer
	LeapVisualizer();
	///Destroy the visualizer
	~LeapVisualizer();
	///Get the address of this object
	LeapVisualizer* getPointer(){return this;}
	///Set the inteface to react to
	void setInterfarce(AnnLeapInterface* interface);
	///Set the current point of view. This is used to update projection the projection matrix
	///\param pose the in-engine pose
	void setPov(OgrePose pose);
	///Update the hands with the last known information from the LEAP interface and the last known pose
	///\param lhand Left Hand from the LEAP
	///\param rhand Right Hand from the LEAP
	void updateHandPosition(Leap::Hand lhand, Leap::Hand rhand);
	///Set the hands object address t
	///\param lhand Left HandObject
	///\param rhand Right HandObject
	void setHandsObjects(HandObject* lhand, HandObject* rhand);
	///calculate the projection matrix from the current pose
	Ogre::Matrix4 getProjectionFromCurrentPose();

	///Convert a Leap::Vector object to an Ogre::Vector3 object
	///\param v Leap::Vector to convert
	static Ogre::Vector3 convert(Leap::Vector v);
	 
	///Update the visualizer
	void update();

	///Return the array of hands known by the visualizer
	static HandObject** getHands()
	{
		return visualHands;
	}

private:
	///The interface
	AnnLeapInterface* inter;
	enum {left, right};
	static HandObject* visualHands[2];

	///Offect, should be 8cm but let it variable
	Ogre::Vector3 LeapEyeOffset;
	///pov matrix
	Ogre::Matrix4 currentPov;
	///Leap to oculus projection
	Ogre::Matrix4 leapOculus;
	///mm to m projection (scaling)
	Ogre::Matrix4 scalling;

	///Last pose knonw
	OgrePose lPose;
	///Update orientation
	void updateHandOrientation(Leap::Hand lhand, Leap::Hand rhand);
	///Update fingers
	void updateFingerPose(Leap::Hand lhand, Leap::Hand rhand);
	///Get a specific bone orientation friom the leap bone. isLeft get the opposite of the X axis because left hand use a "left hand" rule.
	Ogre::Quaternion getBoneOrientation(Leap::Bone bone, bool isLeft = false);
	///Get the name of a bone from theire index
	std::string getBoneName(int finger, int bone);

	///Scale the hand to roughly match user's anatomy
	///\param l left hand
	///\param r right hand
	void manageSize(Leap::Hand l, Leap::Hand r);

	bool lSizeApplied;
	bool rSizeApplied;


	Ogre::Quaternion lwrist, rwrist;
};

#endif