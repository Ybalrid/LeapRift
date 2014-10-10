#include <Leap.h>
#include <Ogre.h> //get for accessing ogre log manager
#include <sstream>
#include <string>

namespace Annwvyn
{
	class AnnLeapInterface
	{
	public:
		///Initialise the LeapMotion interface
		AnnLeapInterface();

		///delete the controller
		~AnnLeapInterface();
		
		///get newest data
		void pollData();

		///Return number of hand found;
		int getHandCount();

		///get the left hand
		Leap::Hand getLeftHand();

		///get the righ hand
		Leap::Hand getRightHand();
	
	private: //methods
		
		///Extract basic data from current frame and store it indide of pointers
		void processFrame(Leap::Frame frame);

	private:

		///Pointer to a dynamicly allocated Leap Motion Controller object
		Leap::Controller* controller;
		
		///ID of the last frame processed by the object
		int64_t lastFrameId;
		
		///true if the actual frame is a new one
		bool newFrameAvailable;

		///Pointer to the current log manager
		Ogre::LogManager* logManagerPtr;
	};
}