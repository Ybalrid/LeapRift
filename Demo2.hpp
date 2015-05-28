#ifndef DEMO2
#define DEMO2

#include "AbstractLevel.hpp"
#include "LeapInteractionManager.hpp"

using namespace Annwvyn;

class Demo2 : public Annwvyn::AbstractLevel
{
public:

	Demo2() : AbstractLevel(),
		lim(NULL)
	{}
	void load()
	{
		AnnEngine::Instance()->setDebugPhysicState(true);
		lim = new LeapInteractionManager(LeapVisualizer::getHands()[0], LeapVisualizer::getHands()[1]);
		AnnEngine::Instance()->setAmbiantLight(Ogre::ColourValue(0.2f,0.2f,0.2f));
		//Load static meshes
		levelContent.push_back(AnnEngine::Instance()->createGameObject("chaise.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("chaise.1.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("clavier.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("ecran.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("horloge.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("placard.1.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("placard.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("porte.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("pot.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("sofa.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("table.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("room.mesh"));
		levelContent.push_back(AnnEngine::Instance()->createGameObject("plafond.mesh"));

		//Correct scale
		for(size_t i(0); i < levelContent.size(); i++)
			levelContent[i]->setScale(AnnVect3(0.60f,0.60f,0.60f));
		
		//Init static object
		for(size_t i(1); i < levelContent.size(); i++)
			levelContent[i]->setUpBullet();

		//Reset player positions
		AnnEngine::Instance()->getPlayer()->setPosition(AnnVect3::ZERO);
		AnnEngine::Instance()->getPlayer()->setOrientation(AnnVect3::ZERO);
		AnnEngine::Instance()->resetPlayerPhysics();

		//light
		levelLighting.push_back(AnnEngine::Instance()->addLight());
		levelLighting.push_back(AnnEngine::Instance()->addLight());
		levelLighting[0]->setPosition(AnnVect3(0,1,-2));
		levelLighting[1]->setPosition(AnnVect3(0,1,0));

		for(int i(0); i < 3; i++)
		{
			GrabableObject* childCube = (GrabableObject*)AnnEngine::Instance()->createGameObject("PlayCube.mesh");
			childCube->setPos(0,-0.1 + 0.1*i,-0.5);
			//childCube->setScale((1.5,1.5,1.5));
			childCube->setUpPhysics(0.1, Annwvyn::phyShapeType::boxShape, false);
			childCube->setObjectRadius(0.7);
			lim->addTrackedGrabable(childCube);
			levelContent.push_back(childCube);
		}
	}



	void runLogic()
	{
		if(lim) lim->update();
	}

	void unload()
	{
		if(lim) delete lim;
		lim = NULL;
		AbstractLevel::unload();
	}

private:
	LeapInteractionManager* lim;
};

#endif
