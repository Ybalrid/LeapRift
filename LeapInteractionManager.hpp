#ifndef LEAP_INTERACTION_MANAGER
#define LEAP_INTERACTION_MANAGER

#include "HandObject.hpp"
#include "GrabableObject.hpp"
#include <vector>

class LeapInteractionManager
{
public :
	LeapInteractionManager();
	void update();
private:
	std::vector <GrabableObject*> grabableList;
	enum {left, right};
	HandObject* hands[2];
};

#endif
