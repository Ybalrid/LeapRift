#define M_PI 3.14159265358979323846


//Includes
#include <Annwvyn.h>


#include "LeapIntegration.hpp"
#include "LeapVisualizer.hpp"
#include "DebugGUI.hpp"
#include <string>

#include "GrabableObject.hpp"
#include "ObjectSpawner.hpp"
#include "HandObject.hpp"


#include "LevelManager.hpp"
#include "Demo0.hpp"


//Namespaces
using namespace std;
using namespace Annwvyn; //All Annwvyn components are here 


///Debuging tool
class LevelManagerListener : LISTENER
{
public:
	LevelManagerListener(AnnPlayer* p, LevelManager* levelManager) : constructListener(p),
		lm(levelManager)
	{
	}

	void KeyEvent(AnnKeyEvent e)
	{
		if(e.isPressed()  && e.getKey() == Annwvyn::KeyCode::enter)
		{
			lm->unloadCurrentLevel();
		}
	}
	

	void MouseEvent(AnnMouseEvent e){}
	void StickEvent(AnnStickEvent e){}

private:
	LevelManager* lm;
};


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
	/*
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
	*/

	GameEngine->getPlayer()->setOrientation(Ogre::Euler(Ogre::Real(M_PI)));
	GameEngine->initPlayerPhysics();
	GameEngine->resetOculusOrientation();
	GameEngine->setSkyDomeMaterial(true, "Sky/dome1");

	GameEngine->getPlayer()->setOrientation(Ogre::Euler(Ogre::Real(M_PI)));
	GameEngine->resetOculusOrientation();
	GameEngine->useDefaultEventListener();

	LevelManager* lm = new LevelManager;

	lm->addLevel(new Demo0);
	lm->jumpToFirstLevel();

	GameEngine->getEventManager()->addListener(new LevelManagerListener(GameEngine->getPlayer(), lm));

	do
	{
		leap.pollData();
		visualizer.setPov(GameEngine->getPoseFromOOR());
		visualizer.updateHandPosition(leap.getLeftHand(), leap.getRightHand());

		lm->tick();

	}while(GameEngine->refresh());
	return 0;
}

