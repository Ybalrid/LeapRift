#include "stdafx.h"
#include "LeapIntegration.hpp"

using namespace Annwvyn;

AnnLeapInterface::AnnLeapInterface()
{
	//Create a new leap controller 
	controller = new Leap::Controller();

	//assume it worked correctly
	assert(controller != NULL);

	//get handy dandy access to Ogre's log manager object
	logManagerPtr = Ogre::LogManager::getSingletonPtr();

	//pass the controller the Optimise HDM flag becase the leap is mounted on the rift.
	controller->setPolicyFlags(static_cast<Leap::Controller::PolicyFlag>(Leap::Controller::PolicyFlag::POLICY_OPTIMIZE_HMD | Leap::Controller::PolicyFlag::POLICY_BACKGROUND_FRAMES));

	logManagerPtr->logMessage("AnnLeapInterface Initialized");
	
	//Initialize some variables to default values
	newFrameAvailable = false;
	lastFrameId = -1;
}

AnnLeapInterface::~AnnLeapInterface()
{
	logManagerPtr->logMessage
		("Destroying the LeapMotion Interface. No longer can get data form LeapMotion controller");

	delete controller;
}

void AnnLeapInterface::pollData()
{
	//get most recent frame
	Leap::Frame currentFrame = controller->frame();

	//If current frame doesn't have the same ID thant the last one (= is a new one)
	if(currentFrame.id() != lastFrameId)
	{
		processFrame(currentFrame);
		newFrameAvailable = true;
	}
	else
	{
		//do nothing, just put the variable to false
		newFrameAvailable = false;
	}
}

void AnnLeapInterface::processFrame(Leap::Frame frame)
{
	//Stream for building log message
	std::stringstream log;
	
	//write OD
	log << "New frame available " << frame.id() << " " << std::endl;

	//Get the hand list from current frame
	Leap::HandList hands = frame.hands();

	//Write hand count
	log << "Detected hands : " << hands.count() << std::endl;

	//Extract player left and rights hands to dirrect acces. 
	extractHandsObjects(hands);

	handList = hands;

	logMessage = log.str();
}

void AnnLeapInterface::extractHandsObjects(Leap::HandList hands)
{
	//Do nothing if no hands are present on sight. Put invalid hands on attributes. 
	if(hands.count() == 0) 
	{
		leftHand = Leap::Hand::invalid();
		rightHand = Leap::Hand::invalid();
		return;
	}

	//if one hand only, store it and
	//set the 2nd one to "invalid"
	if(hands.count() == 1)
	{
		//Get the "kind" of hand it is:
		if(hands[0].isLeft())
		{
			//Store it
			leftHand = hands[0];
			rightHand = Leap::Hand::invalid();
		}
		else
		{
			//Store it in reverse
			rightHand = hands[0];
			leftHand = Leap::Hand::invalid();
		}
	}
	//if two hands or more
	else if(hands.count() >= 2)
	{
		//get left most and right most hands
		Leap::Hand leftMost = hands.leftmost();
		Leap::Hand rightMost = hands.rightmost();

		//if hands arent crossed
		if(leftMost.isLeft() && rightMost.isRight())
		{
			//Store in "normal order"
			leftHand = leftMost;
			rightHand = rightMost;
		}
		//if crossed
		else
		{
			//Store in "reversed order" 
			leftHand = rightMost;
			rightHand = leftMost;
		}
	}
}

//passives getters
bool AnnLeapInterface::newDataAvailable()
{
	return newFrameAvailable;
}

Leap::Hand AnnLeapInterface::getRightHand()
{
	return rightHand;
}

Leap::Hand AnnLeapInterface::getLeftHand()
{
	return leftHand;
}

Leap::HandList AnnLeapInterface::getHandList()
{
	return handList;
}

std::string AnnLeapInterface::getLogMessage()
{
	return logMessage;
}
