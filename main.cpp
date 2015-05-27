#include "stdafx.h"
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
#include "Demo2.hpp"

//Namespaces
using namespace std;
using namespace Annwvyn; //All Annwvyn components are here 

///Debuging tool
class LevelManagerListener : LISTENER
{
public:
	LevelManagerListener(AnnPlayer* p, LevelManager* levelManager) : constructListener(p),
		lm(levelManager)
	{}

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
			if(e.getKey() == Annwvyn::KeyCode::three)
				lm->jump(level_id(2));
		}
	}

	void MouseEvent(AnnMouseEvent e){}
	void StickEvent(AnnStickEvent e){}

private:
	LevelManager* lm;
};

AnnMain()
{
	AnnEngine::openConsole();
	new AnnEngine("My Game", false);

	AnnEngine::Instance()->loadDir("GUI");
	AnnEngine::Instance()->loadDir("media/sky");
	AnnEngine::Instance()->loadDir("media/example");
	AnnEngine::Instance()->loadDir("media/bureau");
	AnnEngine::Instance()->initResources();

	AnnEngine::Instance()->oculusInit();

	AnnEngine::Instance()->initPlayerPhysics();

	AnnLeapInterface leap;
	LeapLoggerListener* l = new LeapLoggerListener();
	HandObject* leftHand = (HandObject*) AnnEngine::Instance()->createGameObject("hand.left.mesh", new HandObject);
	leftHand->setType("left");
	leftHand->registerListener(l);
	HandObject* rightHand = (HandObject*) AnnEngine::Instance()->createGameObject("hand.right.mesh", new HandObject);
	rightHand->setType("right");
	rightHand->registerListener(l);
	LeapVisualizer visualizer;
	visualizer.setInterfarce(leap.getPointer());
	visualizer.setHandsObjects(leftHand, rightHand);

	//for midrendering 
	leftHand->setVisualizerAddress(visualizer.getPointer());

	LevelManager* lm = new LevelManager;

	lm->addLevel(new Demo0);
	lm->addLevel(new Demo1);
	lm->addLevel(new Demo2);

	lm->jumpToFirstLevel();

	AnnEngine::Instance()->useDefaultEventListener();
	AnnEngine::Instance()->getEventManager()->addListener(new LevelManagerListener(AnnEngine::Instance()->getPlayer(), lm));

	AnnEngine::Instance()->resetOculusOrientation();
	AnnEngine::Instance()->openDebugWindow();
	do
	{
		lm->step();
	}while(AnnEngine::Instance()->refresh());

	delete lm;
	delete AnnEngine::Instance();
	return 0;
}
