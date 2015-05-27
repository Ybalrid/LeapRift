#ifndef LEAP_EVENT
#define LEAP_EVENT

#include <string>
#include <AnnEngine.hpp>

using namespace Annwvyn;
enum LeapEventType
{
	HAND_CLOSED
};

class LeapEvent
{
public:
	LeapEvent()
	{
	}

};

///Closing your hand
class LeapCloseEvent : public LeapEvent
{
public:
	LeapCloseEvent() : LeapEvent()
	{}
	bool close;
	std::string hand;
};

class LeapEventListener
{
public:

	///Construct listener
	LeapEventListener()
	{
		AnnEngine::log("Creating a LeapEventListener");
	}

	///Destruct listener
	virtual ~LeapEventListener()
	{
		AnnEngine::log("Deleting a LeapEventListener");
	}
	
	///Notify this listener. This will call the apropriate method and upcast the event object to the apropriate type
	bool notifyEvent(LeapEvent* event, LeapEventType eventType)
	{
		switch(eventType)
		{
		case HAND_CLOSED:
			return closeEvent(static_cast<LeapCloseEvent*>(event));			
		}

		return false;
	}

	///The hand as been (un)closed.
	virtual bool closeEvent(LeapCloseEvent* e){return false;}
};

///Class that write event notification to the logging system
class LeapLoggerListener : public LeapEventListener
{
public:
	///Construct the LeapLoggerListener
	LeapLoggerListener() : LeapEventListener()
	{

	}

	///Write the closing state of the hand
	bool closeEvent(LeapCloseEvent* e)
	{
		logStream << e->hand << " hand: close -> " << e->close;
		log();
		return true;
	}

	///Clear the output stream 
	void clearStream()
	{
		logStream.str("");
	}

	///Flush the output buffer to the stream
	void log()
	{
		AnnEngine::log(logStream.str());
		clearStream();
	}
private:
	///The output buffer
	std::stringstream logStream;

};

#endif
