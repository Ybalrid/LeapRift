#ifndef DEMO0
#define DEMO0
#include "AbstractLevel.hpp"

using namespace Annwvyn;

class Demo0 : public AbstractLevel
{
public:
	virtual void load()
	{
		AnnEngine* GameEngine = AnnEngine::Instance();
		GameEngine->log("Demo0 level");
		AnnGameObject* House = GameEngine->createGameObject("house.mesh");
		House->setPos(0.15,-.65,12);

		House->setUpPhysics();

		levelContent.push_back(House);

		AnnGameObject* BasePlane = GameEngine->createGameObject("Plane.mesh");
		BasePlane->setPos(0, -.60, 11);
		BasePlane->setUpPhysics();

		levelContent.push_back(BasePlane);

		AnnGameObject* Table = GameEngine->createGameObject("Table.mesh");
		Table->setPos(0.15,-.08,10.5);
		Table->setUpBullet();

		levelContent.push_back(Table);
	}

	virtual void runLogic()
	{
		return;
	}
};
#endif