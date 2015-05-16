#ifndef DEMO0
#define DEMO0
#define M_PI 3.14159265358979323846
#include "AbstractLevel.hpp"

#include "GrabableObject.hpp"

using namespace Annwvyn;

class Demo0 : public AbstractLevel
{
public:
	virtual void load()
	{
		AnnEngine* GameEngine = AnnEngine::Instance();
	
		AnnLightObject* l (GameEngine->addLight());
		l->setPosition(Ogre::Vector3(0,1,10));
		levelLighting.push_back(l);

		AnnLightObject* sun (GameEngine->addLight());
		sun->setType(Ogre::Light::LT_DIRECTIONAL);
		sun->setDirection(Ogre::Vector3(-1,1,1));
		sun->setDiffuseColour(Ogre::ColourValue(1,1,.85f));
		levelLighting.push_back(sun);

		GameEngine->setAmbiantLight(Ogre::ColourValue(.25f,.25f,.25f));

		GameEngine->setSkyDomeMaterial(true, "Sky/dome1");
		GameEngine->log("Demo0 level loaded");
		AnnGameObject* House = GameEngine->createGameObject("house.mesh");
		House->setPos(0.15f,-.65f,12);

		House->setUpPhysics();

		levelContent.push_back(House);

		AnnGameObject* BasePlane = GameEngine->createGameObject("Plane.mesh");
		BasePlane->setPos(0, -.60f, 11);
		BasePlane->setUpPhysics();

		levelContent.push_back(BasePlane);

		AnnGameObject* Table = GameEngine->createGameObject("Table.mesh");
		Table->setPos(0.15f,-.08f,10.5);
		Table->setUpBullet();

		levelContent.push_back(Table);

		GameEngine->getPlayer()->setPosition(Ogre::Vector3(0,1,10));
		GameEngine->getPlayer()->setOrientation(Ogre::Euler(Ogre::Real(M_PI)));
		GameEngine->resetPlayerPhysics();

		GrabableObject* ball = (GrabableObject*) GameEngine->createGameObject("Ball.mesh", new GrabableObject);
		levelContent.push_back(ball);

		ball->setPos(0.1, 0.55, 10.3);
	}

	virtual void runLogic()
	{
		return;
	}
};
#endif