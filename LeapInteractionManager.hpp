#ifndef LEAP_INTERACTION_MANAGER
#define LEAP_INTERACTION_MANAGER

#include "HandObject.hpp"
#include "GrabableObject.hpp"
#include <vector>

///Class that compute the "holding obect" states 
class LeapInteractionManager
{
public :
	///Construct the LeapInteractionManager
	LeapInteractionManager(HandObject* leftHand, HandObject* rightHand);
	///Update the states and positions of the objects
	void update();
	///Remove every grabagble object and forget
	void reset();
		
private:
	std::vector <GrabableObject*> grabableList;
	enum {left, right};
	HandObject* hands[2];
};

#endif
