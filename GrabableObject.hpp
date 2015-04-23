#ifndef GRABABLE
#define GRABABLE
#include <AnnGameObject.hpp>

using namespace Annwvyn;

class HandObject;

class GrabableObject : public AnnGameObject
{
	public:
		GrabableObject();
		bool isGrabed();
		HandObject* currentHandObjectHolding();

	private:
		bool grabed;
		HandObject* holder;

};
#endif //GRABABLE