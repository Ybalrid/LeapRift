//Includes
#include <Annwvyn.h>
#include "LeapIntegration.hpp"
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

	DebugGUI gui;
	gui.setText("Ceci est un putain de TEST");
	gui.init(GameEngine->getCamera());


	while(!GameEngine->requestStop())
	{
		leap.pollData();
		gui.setText(leap.getLogMessage());
		gui.update();
		GameEngine->refresh();
	}

	delete GameEngine;
	return 0;
}

