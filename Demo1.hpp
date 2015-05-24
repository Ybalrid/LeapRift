#ifndef DEMO1
#define DEMO1
#define M_PI 3.14159265358979323846
#include "AbstractLevel.hpp"
#include "LeapEvent.hpp"



using namespace Annwvyn;

class FireballSpawner : public LeapEventListener
{
public:
	FireballSpawner() : LeapEventListener()
	{

	}

	bool closeEvent(LeapCloseEvent* e)
	{
		AnnEngine::log("fireball interaction");
		return true;
	}
};

class Sinbad : public AnnGameObject
{
public:
	void postInit()
	{
		setPos(0,0,-5);
		setScale(0.2f,0.2f,0.2f);
		setAnimation("Dance");
		playAnimation(true);
		loopAnimation(true);
		setUpPhysics(40, phyShapeType::boxShape);
	}
};

class Demo1 : public AbstractLevel
{
public:

	Demo1() : AbstractLevel(),
		fireballSpawner(NULL)
	{
	}

	virtual void load()
	{
		fireballSpawner = new FireballSpawner();
		LeapVisualizer::getHands()[0]->registerListener(fireballSpawner);
		LeapVisualizer::getHands()[1]->registerListener(fireballSpawner);

		AnnEngine::Instance()->log("Demo1");
		AnnEngine* GameEngine(AnnEngine::Instance());
		
		AnnLightObject* l (GameEngine->addLight());
		l->setPosition(Ogre::Vector3(0,2,10));
		l->setType(Ogre::Light::LT_SPOTLIGHT);
		l->setDirection(0,-1,-2.5); 
		levelLighting.push_back(l);

		AnnLightObject* sun (GameEngine->addLight());
		sun->setType(Ogre::Light::LT_DIRECTIONAL);
		sun->setDirection(Ogre::Vector3(-0.5,1,0.5));
		sun->setDiffuseColour(Ogre::ColourValue(1,1,.85f));
		levelLighting.push_back(sun);

		GameEngine->setAmbiantLight(Ogre::ColourValue(.33f,.33f,.33f));

		AnnGameObject* Island(AnnEngine::Instance()->createGameObject("Island.mesh"));
		Island->setUpBullet();
		AnnGameObject* Water (AnnEngine::Instance()->createGameObject("Water.mesh"));
		AnnGameObject* Sign(AnnEngine::Instance()->createGameObject("Sign.mesh"));

		Sign->setPos(1,-0,-2);
		Sign->setUpPhysics(0, phyShapeType::staticShape);
		Sign->setOrientation(Ogre::Quaternion(Ogre::Degree(-45), Ogre::Vector3::UNIT_Y));

		levelContent.push_back(Island);
		levelContent.push_back(Water);
		levelContent.push_back(Sign);

		levelContent.push_back(GameEngine->createGameObject("Sinbad.mesh", new Sinbad));
		
		GameEngine->getPlayer()->setOrientation(Ogre::Euler(0));
		GameEngine->getPlayer()->setPosition(Ogre::Vector3(0,1,0));
		GameEngine->resetPlayerPhysics();
	}

	virtual void unload() 
	{
		if(LeapVisualizer::getHands()[0] == NULL)
		{
			AnnEngine::log("Some shit is going wrong here...");
		}

		LeapVisualizer::getHands()[0]->unregisterListener(fireballSpawner);
		LeapVisualizer::getHands()[1]->unregisterListener(fireballSpawner);
		delete fireballSpawner;
		fireballSpawner = NULL;
		AbstractLevel::unload();
	}

	virtual void runLogic()
	{
		return;
	}

private:
	FireballSpawner* fireballSpawner;

};
#endif