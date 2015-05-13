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
	new AnnEngine("My Game");

	AnnEngine::Instance()->loadDir("GUI");
	AnnEngine::Instance()->loadDir("media/sky");
	AnnEngine::Instance()->loadDir("media/example");
	AnnEngine::Instance()->initResources();

	AnnEngine::Instance()->oculusInit();

	AnnEngine::Instance()->initPlayerPhysics();

	AnnLeapInterface leap;
	HandObject* leftHand = (HandObject*) AnnEngine::Instance()->createGameObject("hand.left.mesh", new HandObject);
	HandObject* rightHand = (HandObject*) AnnEngine::Instance()->createGameObject("hand.right.mesh", new HandObject);
	LeapVisualizer visualizer;
	visualizer.setHandsObjects(leftHand, rightHand);

	LevelManager* lm = new LevelManager;

	lm->addLevel(new Demo0);
	lm->addLevel(new Demo1);

	lm->jump(1);
	AnnEngine::Instance()->useDefaultEventListener();
	AnnEngine::Instance()->getEventManager()->addListener(new LevelManagerListener(AnnEngine::Instance()->getPlayer(), lm));

	AnnEngine::Instance()->setDebugPhysicState(true);

	do
	{
		leap.pollData();
		visualizer.setPov(AnnEngine::Instance()->getPoseFromOOR());
		visualizer.updateHandPosition(leap.getLeftHand(), leap.getRightHand());

		lm->step();
	}while(AnnEngine::Instance()->refresh());

	delete lm;
	delete AnnEngine::Instance();
	return 0;
}

