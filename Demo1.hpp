#ifndef DEMO1
#define DEMO1
#define M_PI 3.14159265358979323846
#include "AbstractLevel.hpp"
#include "LeapEvent.hpp"



using namespace Annwvyn;

///Class representing a fireball
class FireBall : public AnnGameObject
{
public :
	///Create a fireball indexed from an hand type
	FireBall(size_t type) : AnnGameObject()
	{
		hand = type;
		if(hand != 0 && hand != 1)
			hand = -1;
		shooted = false;
		speed = AnnVect3(0,0,0);
		creationTime = -1;

		
	}

	///Create the physical state of the Fireball
	void postInit()
	{
		setUpPhysics(1000, phyShapeType::sphereShape, false);
		//Ogre::ParticleSystem* fire = AnnEngine::Instance()->getSceneManager()->createParticleSystem("fire");
		//this->node()->attachObject(fire);
	}

	///Set the creator hand
	void setHand(size_t creator)
	{
		hand = creator;
	}

	///At each frame, if ball in hand : update position, if shooted : set linear speed
	void atRefresh()
	{
		if((hand == 0 || hand == 1) && !shooted)
		{
			HandObject* creator = LeapVisualizer::getHands()[hand];
			this->setPos(creator->pos());
			//this->setLinearSpeed(speed);
		}
		if((hand == 0 || hand == 1) && shooted)
		{
			HandObject* creator = LeapVisualizer::getHands()[hand];			
			this->setLinearSpeed(speed);
		}
	}

	///Shoot the fireball
	void shoot()
	{
		HandObject* creator = LeapVisualizer::getHands()[hand];
		shooted = true;
		speed = AnnEngine::Instance()->getPoseFromOOR().orientation * AnnVect3(0,0,-5);
		this->setPos(creator->pos());
	    creationTime = AnnEngine::Instance()->getTimeFromStartUp();
		
	}


	///Set the date the fireball has been shot. (overide the currently knew one)
	void setCreationTime(double time)
	{
		creationTime = time;
	}

	///Get the creation time
	double getCreationTime()
	{
		return creationTime;
	}

	///Get the shooted state
	bool isShooted()
	{
		return shooted;
	}

private:
	size_t hand;
	bool shooted;
	AnnVect3 speed;
	double creationTime;
};

///Spawn fireballs reacting to close event
class FireballSpawner : public LeapEventListener
{
public:
	///Create the spawner
	FireballSpawner() : LeapEventListener()
	{
		for(size_t i(0); i < 2; i++) 
		{
			fireballCharging[i] = false;
			fireballs[i] = NULL;
		}

		lifespan = 3;
	}

	///Destroy the spawner
	~FireballSpawner()
	{

		if(list.empty()) return;
		std::vector<FireBall*>::iterator it = list.begin();
		while(it != list.end())
		{
			AnnEngine::Instance()->destroyGameObject(*it++);
		}
	}

	///process the close event
	bool closeEvent(LeapCloseEvent* e)
	{
		size_t type = getFromString(e->hand);
		AnnEngine::log("fireball interaction");

		if(!fireballCharging[type] && e->close)
		{

			createFireball(e->hand);
			fireballCharging[type] = true;


		}

		else if(fireballCharging[type] && !e->close)
		{
			shootFireball(e->hand);
			fireballCharging[type] = false;
		}

		return true;
	}

	///Create a fireball
	void createFireball(std::string type)
	{
		createFireball(getFromString(type));
	}

	///Create a fireball 
	void createFireball(size_t type)
	{
		AnnEngine::log(type + " create fireball");
		//if(fireballs[type])
		//	AnnEngine::Instance()->destroyGameObject(fireballs[type]);

		fireballs[type] = (FireBall*) AnnEngine::Instance()->createGameObject("fireball.mesh", new FireBall(type));

		list.push_back(fireballs[type]);
	}

	///Shoot a fireball
	void shootFireball(std::string type)
	{
		shootFireball(getFromString(type));

	}

	///Shoot a fireball
	void shootFireball(size_t type)
	{
		AnnEngine::log(type + " shoot fireball");
		if(!fireballs[type]) return;
		fireballs[type]->shoot();
	}

	///Please call that at each frame to process fireball timing
	void tick()
	{
		std::stringstream ss;
		std::vector<FireBall*>::iterator it;
		it = list.begin();
		FireBall* fireball(NULL);
		while(it != list.end())
		{	
			fireball = *it;
			ss.str("");
			ss << "Ball " << (void*) *it << " Creation time : " << (*it)->getCreationTime();
			AnnEngine::log(ss.str());
			ss.str("");
			ss << "Current status : " << AnnEngine::Instance()->getTimeFromStartUp() - fireball->getCreationTime();
			AnnEngine::log(ss.str());
			if(fireball->isShooted())
				if(AnnEngine::Instance()->getTimeFromStartUp() - fireball->getCreationTime() > lifespan*1000)
				{
					AnnEngine::Instance()->destroyGameObject(fireball);
					it = list.erase(it);
					continue;
				}
			++it;
		}
	}

private:
	///Transform a string typed hand information to an index one
	size_t getFromString(std::string type)
	{
		if(type == "right")
			return 1;
		return 0;
	}

	///are fireballs currently in hands?
	bool fireballCharging[2];
	///The fireballs themselves
	FireBall* fireballs[2];
	///List of current living fireballs
	std::vector<FireBall*> list;
	///TTL of a fireball
	double lifespan;
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
		if(fireballSpawner) fireballSpawner->tick();
		return;
	}

private:
	FireballSpawner* fireballSpawner;

};
#endif