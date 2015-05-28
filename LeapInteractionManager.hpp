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
	LeapInteractionManager(HandObject* leftHand, HandObject* rightHand)
	{
		hands[left] = leftHand;
		hands[right] = rightHand;
	}
	///Update the states and positions of the objects
	void update()
	{
		std::vector<GrabableObject*>::iterator it(grabableList.begin());
		while(it != grabableList.end())
		{
			//this seems to be not working

			if((*it)->isGrabed())
			{
				AnnEngine::log("not grabbed"); 
				for(int i(0); i < 2; i++)
					if(getDistance((*it), hands[i]) <= (*it)->getObjectRadius())
					{
						(*it)->beGrabbed(hands[i]);
					}
			}
			else
			{
				AnnEngine::log("grabbed");
				if(getDistance(*it, (*it)->currentHandObjectHolding()) >= (*it)->getObjectRadius()+0.1)
				{
					(*it)->release();
				}
				else
				{
					(*it)->setPos((*it)->currentHandObjectHolding()->pos());
				}			
			}
			it++;
		}
	}
	///Remove every grabagble object from the manager
	void reset()
	{
		grabableList.clear();
	}
	///Add a grabable Objedt to be tracked
	void addTrackedGrabable(GrabableObject* object)
	{
		grabableList.push_back(object);
	}

private:
	float getDistance(GrabableObject* oa, HandObject* ob)
	{
		AnnVect3 a(oa->pos());
		AnnVect3 b(ob->pos());
		//get a vector representing translation between the two objects
		AnnVect3 vector = b-a; 

		//store math result :
		float dist;

		//do dist = x² + y² + z²
		dist = vector.x * vector.x;
		dist += vector.y * vector.y;
		dist += vector.z * vector.z;

		return sqrt(dist); 
	}

	std::vector <GrabableObject*> grabableList;
	enum {left, right};
	HandObject* hands[2];
};

#endif
