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
	GameEngine->initRessources();

	GameEngine->oculusInit(false);

	AnnLeapInterface leap;

	

	//create hands objects:
	AnnGameObject* leftHand = GameEngine->createGameObject("pointer.mesh");
	AnnGameObject* rightHand = GameEngine->createGameObject("pointer.mesh");

	LeapVisualizer visualizer;
	visualizer.setHandsObjects(leftHand, rightHand);


	//DebugGUI gui;
	//gui.setText("Ceci est un putain de TEST");
	//gui.init(GameEngine->getCamera()); 



	AnnGameObject* Suzanne = GameEngine->createGameObject("Suzanne.mesh");
	GameEngine->setAmbiantLight(Ogre::ColourValue(.2f,.2f,.2f));

	Suzanne->setPos(0,0,8);

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

