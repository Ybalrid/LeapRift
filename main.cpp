//Includes
#include <Annwvyn.h>


#include "LeapIntegration.hpp"
#include "LeapVisualizer.hpp"
#include "DebugGUI.hpp"
#include <string>



//Namespaces
using namespace std;
using namespace Annwvyn; //All Annwvyn components are here 


AnnMain()
{
	AnnEngine* GameEngine = new AnnEngine("My Game");

	GameEngine->loadDir("GUI");
	GameEngine->initResources();

	GameEngine->oculusInit(false);

	AnnLeapInterface leap;

	

	//create hands objects:
	AnnGameObject* leftHand = GameEngine->createGameObject("hand.left.mesh");
	AnnGameObject* rightHand = GameEngine->createGameObject("hand.right.mesh");

	LeapVisualizer visualizer;
	visualizer.setHandsObjects(leftHand, rightHand);


	//DebugGUI gui;
	//gui.setText("Ceci est un putain de TEST");
	//gui.init(GameEngine->getCamera()); 


	AnnGameObject* Suzanne = GameEngine->createGameObject("Suzanne.mesh");
	GameEngine->setAmbiantLight(Ogre::ColourValue(.2f,.2f,.2f));


	AnnLightObject* l (GameEngine->addLight());
	l->setPosition(0,0,0);

	AnnLightObject* sun (GameEngine->addLight());
	l->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
	l->setDirection(Ogre::Vector3(-1,-1,-1));

	Suzanne->setPos(0,0,9);

	AnnGameObject* House = GameEngine->createGameObject("house.mesh");
	House->setPos(0,-1.65,0);

	House->setUpPhysics();


	AnnGameObject* BasePlane = GameEngine->createGameObject("Plane.mesh");
	BasePlane->setPos(0, -1.65, 11);
	BasePlane->setUpPhysics();
	GameEngine->setDebugPhysicState(true);


	GameEngine->initPlayerPhysics();

	GameEngine->resetOculusOrientation();
	while(!GameEngine->requestStop())
	{
		leap.pollData();
		//gui.setText(leap.getLogMessage());
		//gui.update();

		visualizer.setPov(GameEngine->getPoseFromOOR());
		visualizer.updateHandPosition(leap.getLeftHand(), leap.getRightHand());
		GameEngine->refresh();
	}

	//delete GameEngine;
	return 0;
}

