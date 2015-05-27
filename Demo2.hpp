#ifndef DEMO2
#define DEMO2

#include "AbstractLevel.hpp"

class Demo2 : public AbstractLevel
{
public:
	void load()
	{
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
			levelContent[i]->setScale(AnnVect3(0.53f,0.53f,0.53f));
		
		//Init static object
		for(size_t i(1); i < levelContent.size(); i++)
			levelContent[i]->setUpBullet();

		//Reset player positions
		AnnEngine::Instance()->getPlayer()->setPosition(AnnVect3::ZERO);
		AnnEngine::Instance()->getPlayer()->setOrientation(AnnVect3::ZERO);
		AnnEngine::Instance()->resetPlayerPhysics();

		//light
		levelLighting.push_back(AnnEngine::Instance()->addLight());
		levelLighting[0]->setPosition(AnnVect3(0,1,-2));
	}

	void runLogic()
	{
	}
};

#endif
