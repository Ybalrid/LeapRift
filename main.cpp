//Includes
#include <Annwvyn.h>
#include "LeapIntegration.hpp"

//Namespaces
using namespace std;
using namespace Annwvyn; //All Annwvyn components are here 


AnnMain()
{
	AnnEngine* GameEngine = new AnnEngine("My Game");

	GameEngine->initRessources();

	GameEngine->oculusInit(true);

	AnnLeapInterface leap;

	while(!GameEngine->requestStop())
	{
		leap.pollData();
		GameEngine->refresh();
	}

	delete GameEngine;
	return 0;
}

