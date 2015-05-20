#ifndef ANNLEAPINTERFACE
#define ANNLEAPINTERFACE

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
		AnnLeapInterface* getPointer(){return this;}

		///delete the controller
		~AnnLeapInterface();

		///get newest data
		void pollData();

		///get if new data is available
		bool newDataAvailable();

		///get the last message loged by the class. Probably processing or debug stuff.
		std::string getLogMessage();

		/**
		*   The getters below are returning data from the last frame processed.
		*	Calling the getters don't do any processing, they can be accessed any time.
		*   They are returning "invalid" object in case of error/non existance...
		*/

		///get the left hand
		Leap::Hand getLeftHand();

		///get the righ hand
		Leap::Hand getRightHand();

		///get the full list of hands (can be handy.... Ah ah...) 
		Leap::HandList getHandList();

	private: //methods

		///Extract basic data from current frame and store it indide of pointers.
		void processFrame(Leap::Frame frame);

		///Process hands information from the hand list, like testing the number and type of hands.
		void extractHandsObjects(Leap::HandList hands);

	private:
		///Pointer to a dynamicly allocated Leap Motion Controller object
		Leap::Controller* controller;

		///ID of the last frame processed by the object
		int64_t lastFrameId;

		///true if the actual frame is a new one
		bool newFrameAvailable;

		///Pointer to the current log manager
		Ogre::LogManager* logManagerPtr;

		///Object to keep copies of hands and lists
		Leap::Hand leftHand, rightHand;
		Leap::HandList handList;

		///String to store the last log message... 
		std::string logMessage;
	};
}

#endif //ANNLEAPINTERFACE