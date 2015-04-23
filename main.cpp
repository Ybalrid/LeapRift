//Includes
#include <Annwvyn.h>


#include "LeapIntegration.hpp"
#include "LeapVisualizer.hpp"
#include "DebugGUI.hpp"
#include <string>

#include "GrabableObject.hpp"
#include "ObjectSpawner.hpp"
#include "HandObject.hpp"

#define M_PI 3.14159265358979323846

//Namespaces
using namespace std;
using namespace Annwvyn; //All Annwvyn components are here 


AnnMain()
{
	AnnEngine* GameEngine = new AnnEngine("My Game");

	GameEngine->loadDir("GUI");
	GameEngine->loadDir("media/sky");
	GameEngine->initResources();

	GameEngine->oculusInit();

	AnnLeapInterface leap;

	//create hands objects:
	HandObject* leftHand = (HandObject*) GameEngine->createGameObject("hand.left.mesh", new HandObject);
	HandObject* rightHand = (HandObject*) GameEngine->createGameObject("hand.right.mesh", new HandObject);

	LeapVisualizer visualizer;
	visualizer.setHandsObjects(leftHand, rightHand);
	GameEngine->setAmbiantLight(Ogre::ColourValue(.2f,.2f,.2f));

	AnnLightObject* l (GameEngine->addLight());
	l->setPosition(0,0,0);

	AnnLightObject* sun (GameEngine->addLight());
	l->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
	l->setDirection(Ogre::Vector3(-1,-1,-1));

	AnnGameObject* House = GameEngine->createGameObject("house.mesh");
	House->setPos(0.15,-.65,12);

	House->setUpPhysics();

	AnnGameObject* BasePlane = GameEngine->createGameObject("Plane.mesh");
	BasePlane->setPos(0, -.60, 11);
	BasePlane->setUpPhysics();

	AnnGameObject* Table = GameEngine->createGameObject("Table.mesh");
	Table->setPos(0.15,-.08,10.5);
	Table->setUpBullet();

	GameEngine->getPlayer()->setOrientation(Ogre::Euler(Ogre::Real(M_PI)));
	GameEngine->initPlayerPhysics();
	GameEngine->resetOculusOrientation();
	GameEngine->setSkyDomeMaterial(true, "Sky/dome1");

	GameEngine->getPlayer()->setOrientation(Ogre::Euler(Ogre::Real(M_PI)));
	GameEngine->resetOculusOrientation();


	AnnGameObject* lboundingBox;
	AnnGameObject* rboundingBox;

	lboundingBox = GameEngine->createGameObject("Box.mesh");
	rboundingBox = GameEngine->createGameObject("Box.mesh");

	Ogre::Vector3 size(0.25,0.02,0.15);

	lboundingBox->setScale(size);
	rboundingBox->setScale(size);

	lboundingBox->setUpPhysics(0, boxShape, false);
	rboundingBox->setUpPhysics(0, boxShape, false);
	
	lboundingBox->setInvisible();
	rboundingBox->setInvisible();
	float lastTime;
	float currentTime;

	GameEngine->useDefaultEventListener();

	do
	{
		currentTime = GameEngine->getTimeFromStartUp();

		leap.pollData();
		visualizer.setPov(GameEngine->getPoseFromOOR());
		visualizer.updateHandPosition(leap.getLeftHand(), leap.getRightHand());
		lboundingBox->setPos(leftHand->pos());
		rboundingBox->setPos(rightHand->pos());
		lboundingBox->setOrientation(leftHand->getWristOrientation());
		rboundingBox->setOrientation(rightHand->getWristOrientation());

	}while(GameEngine->refresh());
	//delete GameEngine;
	return 0;
}

