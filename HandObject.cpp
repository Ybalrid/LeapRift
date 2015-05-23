#include "stdafx.h"
#include "HandObject.hpp"
#include "LeapVisualizer.hpp"

void HandObject::atRefresh()
{
	if(vis) vis->update();

	if(closed && palmRadius > 0.09)
	{
		closed = false;
		
		//Create Event
		LeapCloseEvent e;
		e.close = false;
		e.hand = type;
		//Notify listeners;
		notifyListener(&e, HAND_CLOSED);
	}

	if(!closed && palmRadius < 0.06)
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