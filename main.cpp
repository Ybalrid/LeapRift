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
#include "Demo1.hpp"

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
		if(e.isPressed())
		{
			if(e.getKey() == Annwvyn::KeyCode::enter)
				lm->unloadCurrentLevel();
			if(e.getKey() == Annwvyn::KeyCode::back)
				lm->jumpToFirstLevel();
			if(e.getKey() == Annwvyn::KeyCode::one)
				lm->jump(level_id(0));
			if(e.getKey() == Annwvyn::KeyCode::two)
				lm->jump(level_id(1));
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
	GameEngine->loadDir("media/example");
	GameEngine->initResources();

	GameEngine->oculusInit();

	GameEngine->setAmbiantLight(Ogre::ColourValue(.2f,.2f,.2f));
	GameEngine->initPlayerPhysics();

	AnnLeapInterface leap;
	HandObject* leftHand = (HandObject*) GameEngine->createGameObject("hand.left.mesh", new HandObject);
	HandObject* rightHand = (HandObject*) GameEngine->createGameObject("hand.right.mesh", new HandObject);
	LeapVisualizer visualizer;
	visualizer.setHandsObjects(leftHand, rightHand);

	AnnLightObject* l (GameEngine->addLight());
	l->setPosition(0,0,0);

	AnnLightObject* sun (GameEngine->addLight());
	l->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
	l->setDirection(Ogre::Vector3(-1,-1,-1));

	LevelManager* lm = new LevelManager;

	lm->addLevel(new Demo0);
	lm->addLevel(new Demo1);

	lm->jump(1);
	GameEngine->useDefaultEventListener();
	GameEngine->getEventManager()->addListener(new LevelManagerListener(GameEngine->getPlayer(), lm));

	do
	{
		leap.pollData();
		visualizer.setPov(GameEngine->getPoseFromOOR());
		visualizer.updateHandPosition(leap.getLeftHand(), leap.getRightHand());

		lm->step();

	}while(GameEngine->refresh());
	delete lm;
	return 0;
}

