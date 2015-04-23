//Includes
#include <Annwvyn.h>


#include "LeapIntegration.hpp"
#include "LeapVisualizer.hpp"
#include "DebugGUI.hpp"
#include <string>

#include "GrabableObject.hpp"
#include "ObjectSpawner.hpp"
#include "HandObject.hpp"

# define M_PI           3.14159265358979323846  /* pi */

//Namespaces
using namespace std;
using namespace Annwvyn; //All Annwvyn components are here 


AnnMain()
{
	AnnEngine* GameEngine = new AnnEngine("My Game");

	GameEngine->loadDir("GUI");
	GameEngine->loadDir("media/sky");
	GameEngine->initResources();

	GameEngine->oculusInit(false);

	AnnLeapInterface leap;

	

	//create hands objects:
	HandObject* leftHand = (HandObject*) GameEngine->createGameObject("hand.left.mesh", new HandObject);
	HandObject* rightHand = (HandObject*) GameEngine->createGameObject("hand.right.mesh", new HandObject);

	//leftHand->setUpPhysics(0, boxShape, false);
	//rightHand->setUpPhysics(0, boxShape, false);


	LeapVisualizer visualizer;
	visualizer.setHandsObjects(leftHand, rightHand);


	//DebugGUI gui;
	//gui.setText("Ceci est un putain de TEST");
	//gui.init(GameEngine->getCamera()); 


	//AnnGameObject* Suzanne = GameEngine->createGameObject("Suzanne.mesh");
	GameEngine->setAmbiantLight(Ogre::ColourValue(.2f,.2f,.2f));


	AnnLightObject* l (GameEngine->addLight());
	l->setPosition(0,0,0);

	AnnLightObject* sun (GameEngine->addLight());
	l->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
	l->setDirection(Ogre::Vector3(-1,-1,-1));

	//Suzanne->setPos(0,0,9);

	AnnGameObject* House = GameEngine->createGameObject("house.mesh");
	House->setPos(0.15,-.65,12);

	House->setUpPhysics();


	AnnGameObject* BasePlane = GameEngine->createGameObject("Plane.mesh");
	BasePlane->setPos(0, -.60, 11);
	BasePlane->setUpPhysics();
	//GameEngine->setDebugPhysicState(true);

	AnnGameObject* Table = GameEngine->createGameObject("Table.mesh");
	Table->setPos(0.15,-.08,10.5);
	Table->setUpBullet();

	GameEngine->getPlayer()->setOrientation(Ogre::Euler(Ogre::Real(M_PI)));

	GameEngine->initPlayerPhysics();

	GameEngine->resetOculusOrientation();

	GameEngine->setSkyDomeMaterial(true, "Sky/dome1");

	
	ObjectSpawner spawner(GameEngine);
	spawner.setSpawnPoint(Ogre::Vector3(0.15, 0.6, 10.7-.5));
	spawner.setEntityName("Ball.mesh");

	spawner.spawn();

	GameEngine->getPlayer()->setOrientation(Ogre::Euler(Ogre::Real(M_PI)));
	GameEngine->resetOculusOrientation();


	AnnGameObject* lboundingBox;
	AnnGameObject* rboundingBox;

	lboundingBox = GameEngine->createGameObject("Box.mesh");
	rboundingBox = GameEngine->createGameObject("Box.mesh");

	lboundingBox = GameEngine->createGameObject("Box.mesh");
	rboundingBox = GameEngine->createGameObject("Box.mesh");


	Ogre::Vector3 size(0.25,0.02,0.15);

	lboundingBox->setScale(size);
	rboundingBox->setScale(size);

	lboundingBox->setUpPhysics(0, boxShape, false);
	rboundingBox->setUpPhysics(0, boxShape, false);

	float lastTime;
	float currentTime;

	while(!GameEngine->requestStop())
	{
		currentTime = GameEngine->getTimeFromStartUp();

		leap.pollData();
		//gui.setText(leap.getLogMessage());
		//gui.update();

		visualizer.setPov(GameEngine->getPoseFromOOR());
		visualizer.updateHandPosition(leap.getLeftHand(), leap.getRightHand());
		
		lboundingBox->setPos(leftHand->pos());
		rboundingBox->setPos(rightHand->pos());

		lboundingBox->setOrientation(leftHand->getWristOrientation());
		rboundingBox->setOrientation(rightHand->getWristOrientation());


		lboundingBox->Entity()->setVisible(false);
		rboundingBox->Entity()->setVisible(false);

		if(GameEngine->isKeyDown(OIS::KC_F12))
			GameEngine->resetOculusOrientation();
		if(GameEngine->isKeyDown(OIS::KC_SPACE))
			if((currentTime - lastTime) >= 500)
			{
				lastTime = currentTime;
				spawner.spawn();
			}

		if(GameEngine->isKeyDown(OIS::KC_RETURN))
			spawner.reset();

		GameEngine->refresh();
	}

	//delete GameEngine;
	return 0;
}

