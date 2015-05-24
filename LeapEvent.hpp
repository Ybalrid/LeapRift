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
	LeapEventListener()
	{
		AnnEngine::log("Creating a LeapEventListener");
	}

	virtual ~LeapEventListener()
	{
		AnnEngine::log("Deleting a LeapEventListener");
	}
	
	bool notifyEvent(LeapEvent* event, LeapEventType eventType)
	{
		switch(eventType)
		{
		case HAND_CLOSED:
			return closeEvent(static_cast<LeapCloseEvent*>(event));			
		}

		return false;
	}

	virtual bool closeEvent(LeapCloseEvent* e){return false;}
};

class LeapLoggerListener : public LeapEventListener
{
public:
	LeapLoggerListener() : LeapEventListener()
	{

	}

	bool closeEvent(LeapCloseEvent* e)
	{
		logStream << e->hand << " hand: close -> " << e->close;
		log();
		return true;
	}

	void clearStream()
	{
		logStream.str("");
	}

	void log()
	{
		AnnEngine::log(logStream.str());
		clearStream();
	}
	std::stringstream logStream;

};

#endif
