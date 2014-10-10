#include "LeapIntegration.hpp"

using namespace Annwvyn;

AnnLeapInterface::AnnLeapInterface()
{
	//Create a new leap controller 
	controller = new Leap::Controller();

	//assume it worked correctly
	assert(controller != NULL);

	//pass the controller the Optimise HDM flag becase the leap is mounted on the rift.
	controller->setPolicyFlags(Leap::Controller::PolicyFlag::POLICY_OPTIMIZE_HMD);

	//Set the log manager pointer to the current log manager singleton
	logManagerPtr = Ogre::LogManager::getSingletonPtr();
	
	newFrameAvailable = false;
	lastFrameId = -1;
}

AnnLeapInterface::~AnnLeapInterface()
{
	delete controller;
}

void AnnLeapInterface::pollData()
{
	//get most recent frame
	Leap::Frame currentFrame = controller->frame();
	
	if(currentFrame.id() != lastFrameId)
		{
			processFrame(currentFrame);
			newFrameAvailable = true;
		}
	else
		{
			newFrameAvailable = false;
		}
}

void AnnLeapInterface::processFrame(Leap::Frame frame)
{
	std::stringstream log;
	
	log << "New frame available " << frame.id();


	logManagerPtr->logMessage(Ogre::String(log.str()));

	return;
}