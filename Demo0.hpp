#ifndef DEMO0
#define DEMO0
#define M_PI 3.14159265358979323846
#include "AbstractLevel.hpp"

#include "GrabableObject.hpp"
#include "ObjectSpawner.hpp"

using namespace Annwvyn;

class Demo0 : public AbstractLevel
{
public:

	Demo0() : AbstractLevel(),
		os(NULL),
		lboundingBox(NULL),
		rboundingBox(NULL),
		now(0),
		last(0)
	{}

	virtual void load()
	{
		AnnEngine* GameEngine = AnnEngine::Instance();
		os = new ObjectSpawner(GameEngine);
		os->setEntityName("Ball.mesh");
		os->setSpawnPoint(AnnVect3(0.1f, 0.55f, 10.3f));
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

		//GrabableObject* ball = (GrabableObject*) GameEngine->createGameObject("Ball.mesh", new GrabableObject);
		//levelContent.push_back(ball);

		//ball->setPos();


		lboundingBox = GameEngine->createGameObject("Box.mesh");
		rboundingBox = GameEngine->createGameObject("Box.mesh");

		Ogre::Vector3 size(0.25f,0.02f,0.15f);

		lboundingBox->setScale(size);
		rboundingBox->setScale(size);

		lboundingBox->setUpPhysics(0, boxShape, false);
		rboundingBox->setUpPhysics(0, boxShape, false);

		lboundingBox->Entity()->setVisible(false);
		rboundingBox->Entity()->setVisible(false);

		levelContent.push_back(lboundingBox);
		levelContent.push_back(rboundingBox);
	}

	virtual void unload()
	{
		os->reset();
		delete os; 
		os = NULL;
		AbstractLevel::unload();
	}

	virtual void runLogic()
	{
		now = AnnEngine::Instance()->getTimeFromStartUp();

		if(now - last >= 1000)
		{
			last = now;
			os->spawn();
		}

		if(os->getList().size() >= 15) 
			os->reset();

		HandObject* leftHand(LeapVisualizer::getHands()[0]);
		HandObject* rightHand(LeapVisualizer::getHands()[1]);
		lboundingBox->setPos(leftHand->pos());
		rboundingBox->setPos(rightHand->pos());

		lboundingBox->setOrientation(leftHand->getWristOrientation());
		rboundingBox->setOrientation(rightHand->getWristOrientation());

		if(!leftHand->isVisible()) lboundingBox->setPos(0,1000,0);
		if(!rightHand->isVisible()) rboundingBox->setPos(0,1000,0);
 	}

private:
	ObjectSpawner* os;
	AnnGameObject* lboundingBox;
	AnnGameObject* rboundingBox;
	double now, last;
};
#endif