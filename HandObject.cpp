#include "stdafx.h"
#include "HandObject.hpp"
#include "LeapVisualizer.hpp"

void HandObject::atRefresh()
{
	if(vis) vis->update();

	if(closed && palmRadius > 0.1)
	{
		closed = false;

		//Create Event
		LeapCloseEvent e;
		e.close = false;
		e.hand = type;
		//Notify listeners;
		notifyListener(&e, HAND_CLOSED);
	}

	if(!closed && palmRadius < 0.05)
	{
		closed = true;

		//Create Event
		LeapCloseEvent e;
		e.close = true;
		e.hand = type;
		//
		notifyListener(&e, HAND_CLOSED);
	}


}

void HandObject::unregisterListener(LeapEventListener* listener)
{
	std::vector<LeapEventListener*>::iterator it(listeners.begin());
	while(it != listeners.end())
		if(*it == listener)
			it = listeners.erase(it);
		else
			it++;
}