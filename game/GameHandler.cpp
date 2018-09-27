#include <game/GameHandler.h>
#include <global/GlobalValues.h>
#include <windows.h>

GameHandler::GameHandler(){
	engine = Globals::getGlobals()->engine;
	
	engine->getCollisionHandler()->addListener(this);

	listeners			= new vector<GameListener*>;
	tanks				= new vector<Tank*>;
	missiles			= new vector<Missile*>;
	
	room = new Room(500, 500, 100);
}

GameHandler::~GameHandler(){
	engine->getCollisionHandler()->delListener(this);
	delete(room);
	delete(listeners);
	delete(tanks);
	delete(missiles);
}

void	GameHandler::addListener(GameListener* tl){
	listeners->push_back(tl);
}

void	GameHandler::delListener(GameListener* tl){
	for(int i=0;i<listeners->size();++i)
		if((*listeners)[i]==tl)
			listeners->erase(listeners->begin()+i);
}

bool	GameHandler::isListening(GameListener* tl){
	for(int i=0;i<listeners->size();++i)
		if((*listeners)[i]==tl)
			return true;
	return false;
}

void	GameHandler::addTank(Tank* t){
	// Create a collision pair for this tank, with each other tank
	for(int i=0;i<tanks->size();++i){
	    engine->getCollisionHandler()->addPair(new CASphereSphere(t, (*tanks)[i]), t, (*tanks)[i]);
	}
	// Then add tank
	tanks->push_back(t);
}

void	GameHandler::delTank(Tank* t){
	engine->getCollisionHandler()->delPairsWith(t);
	for(int i=0;i<tanks->size();++i){
		if((*tanks)[i]==t)tanks->erase(tanks->begin()+i);
		return;
	}
}

vector<Tank*>*	GameHandler::getTanks(){
	return tanks;
}

void	GameHandler::addMissile(Missile* m){
	missiles->push_back(m);
	for(int i=0;i<tanks->size();++i)
		    engine->getCollisionHandler()->addPair(new CASphereLine((*tanks)[i], m), (*tanks)[i], m);
}

void	GameHandler::delMissile(Missile* m){
	engine->getCollisionHandler()->delPairsWith(m);
	for(int i=0;i<missiles->size();++i)
		if((*missiles)[i]==m){
			missiles->erase(missiles->begin()+i);
			return;
		}
}

// Interface methods (other class?)

void	GameHandler::steerLeft(Tank* t, bool b){
	t->setSteerLeft(b);
}

void	GameHandler::steerRight(Tank* t, bool b){
	t->setSteerRight(b);
}

void	GameHandler::accelerate(Tank* t, bool b){
	t->setAccelerate(b);
}

void	GameHandler::brake(Tank* t, bool b){
	t->setBrake(b);
}

void	GameHandler::steerTurretLeft(Tank* t, bool b){
	t->setRotateTurretLeft(b);
}

void	GameHandler::steerTurretRight(Tank* t, bool b){
	t->setRotateTurretRight(b);
}

void	GameHandler::steerTurretUp(Tank* t, bool b){
	t->setRotateTurretUp(b);
}

void	GameHandler::steerTurretDown(Tank* t, bool b){
	t->setRotateTurretDown(b);
}

void	GameHandler::mouseSteerTurret(Tank* t, double x, double y){
	t->setAim(x, y);
}

void	GameHandler::fire(Tank* t, bool b){
	t->setFiring(b);
}

// indirect methods

void	GameHandler::damage(GameObject* go, GameObject* by, float damage){
	// This object is damages by object 'by'
	go->damage(damage);

	// if this tank is killed
	if(go->isDestroyed()){
		if((Tank*)go){
			Tank* t = (Tank*)go;
		    delTank(t);
		}else if((Missile*)go){
			Missile* m = (Missile*)go;
			delMissile(m);
		}

		// Remove from list (?)

		// trigger listeners about this
//		for(int i=0;i<listeners->size();++i)
//			(*listeners)[i]->onDestroyed(go, by);
	}
}

void	GameHandler::paint(){
	room->paint();

	for(int i=0;i<tanks->size();++i){
		(*tanks)[i]->paint();
	}
	
	for(int i=0;i<missiles->size();++i)
		(*missiles)[i]->paint();
		
	// paint collision detection debug
}

void	GameHandler::move(int msec){
	if(msec!=0){

		for(int i=0;i<tanks->size();++i){
			Tank* tank = (*tanks)[i];
			tank->move(msec);
			double dimx = 0.495*room->getDimensions()->x;
			double dimy = 0.495*room->getDimensions()->y;

			// Prevent tanks from moving outside of room (copy code from onCollision)
			double  bounce = 10;
			
			if(tank->getPosition()->x < -dimx){
//				tank->getPosition()->x = -dimx;
				tank->setImpulse( bounce * tank->getSpeed() / tank->getMass(), 0, 0);
			}
			
			if(tank->getPosition()->x > dimx){
//				tank->getPosition()->x = dimx;
				tank->setImpulse( bounce * -tank->getSpeed() / tank->getMass(), 0, 0);
			}
		
			if(tank->getPosition()->y < -dimy){
//				tank->getPosition()->y = -dimy;
				tank->setImpulse( 0, bounce * tank->getSpeed() / tank->getMass(), 0);
			}
		
			if(tank->getPosition()->y > dimy){
//				tank->getPosition()->y = dimy;
				tank->setImpulse( 0, bounce * -tank->getSpeed() / tank->getMass(), 0);
			}
			
		}

		for(int i=0;i<missiles->size();++i)
			(*missiles)[i]->move(msec);


		// Bump missles that hit floor, or destroy

		for(int i=0;i<missiles->size();++i)
			if((*missiles)[i]->getPosition()->z < 0){
				Missile* m = (*missiles)[i];
				damage(m, m, 5);
				m->getPosition()->z = 0;
				m->setImpulse(0,0, -1.5*m->getMotion()->z);
			}

		// check for creating bullets

		for(int i=0;i<tanks->size();++i){
			Tank* t = (*tanks)[i];

			if(t->getBarrel()->ready() && t->isFiring()){
				// refresh cooldown counter
				t->getBarrel()->setCooldown( t->getBarrel()->getCooldown() );

				// Create a missle of the type this tank uses
				Missile* tm = t->getBarrel()->obtainMissile();

				// Get direction ifno
				float heading = t->getHeading() + t->getTurretAngle();
				float pitch   = t->getTurretPitch();

				// Missle start from tip of turret (or fire offset)
				Vector mpos = Vector(t->getPosition()->x, t->getPosition()->y, t->getPosition()->z);
				
				// Rotate fireoffset over y axis
				//	vector->y = (cos(f)* t.y) + (sin(f)* t.z) + center->y;
				//	vector->z = (-sin(f)* t.y) + (cos(f)* t.z) + center->z;
				double alpha = (heading-59) * (PI/180);
				mpos.x += (cos(alpha)*t->getFireOffset()->y) + (sin(alpha)*t->getFireOffset()->z);
				mpos.y += (-sin(alpha)*t->getFireOffset()->y) + (cos(alpha)*t->getFireOffset()->z);
				mpos.z += t->getFireOffset()->z;
				
				tm->setPosition(mpos.x, mpos.y, mpos.z);


				// Motion of bullet equals that of thank
				tm->setMotion( t->getMotion()->x, t->getMotion()->y, t->getMotion()->z );
				
				// Explosion creates the impulse of the bullet
				tm->setImpulse(         sin( heading * (PI/180) ) * cos( pitch * (PI/180) ) * t->getBarrel()->getPower(),
									 	cos( heading * (PI/180) ) * cos( pitch * (PI/180) ) * t->getBarrel()->getPower(),
									 	sin( pitch * (PI/180) ) * t->getBarrel()->getPower());
				

				// Add it to our objects
				missiles->push_back(tm);

				// create collision pairs for this missle vs. all other tanks
				for(int i=0;i<tanks->size();++i)
					if((*tanks)[i]!=t)
					    engine->getCollisionHandler()->addPair(new CASphereLine((*tanks)[i], tm), (*tanks)[i], tm);
			}
		}

	}
}

void	GameHandler::onCollision(CollisionPair* cp){
	// handle collision events
	CollisionObject* obj1 = cp->getObjectA();
	CollisionObject* obj2 = cp->getObjectB();
	
	// Create impulse same as difference in objects position
	
	if((Tank*)obj1 && (Tank*)obj2){

		Tank* tank1 = (Tank*)obj1;
		Tank* tank2 = (Tank*)obj2;
		
		// Collision reaction:

		double boost = 0.0; // Scale

		Vector direction1;
		divVector(direction1, *tank2->getPosition(), *tank1->getPosition());
		normalizeVector(direction1);
/*
		tank2->setImpulse(	boost * tank1->getSpeed() * (tank1->getMass()/tank2->getMass()) * direction1.x,
                      		boost * tank1->getSpeed() * (tank1->getMass()/tank2->getMass()) * direction1.y,
		                    0 );

		tank1->setImpulse(	boost * tank2->getSpeed() * (tank2->getMass()/tank1->getMass()) * -direction1.x,
                     		boost * tank2->getSpeed() * (tank2->getMass()/tank1->getMass()) * -direction1.y,
		                    0 );
*/
		// Move tanks back to last known best position (not intersecting)
//		tank1->setPosition(*tank1->getPrevPosition());
//		tank2->setPosition(*tank2->getPrevPosition());
	}
	
	if((Tank*)obj1 && (Missile*)obj2){

		Tank* tank = (Tank*)obj1;
		Missile* missile = (Missile*)obj2;

		double boost = 0.05; // Scale

		// Next is a simple collision reaction implementation
		// Tanks bounce back against each others direction, severity is modified against mass of both tanks and their speed

		// This is simple and looks good, just make

		Vector direction;
		divVector(direction, *missile->getPosition(), *tank->getPosition());
		normalizeVector(direction);

		missile->setImpulse(	boost * tank->getSpeed() * (tank->getMass()/missile->getMass()) * direction.x,
                      			boost * tank->getSpeed() * (tank->getMass()/missile->getMass()) * direction.y,
		                    	0 );

		tank->setImpulse(	boost * missile->getSpeed() * (missile->getMass()/tank->getMass()) * -direction.x,
                     		boost * missile->getSpeed() * (missile->getMass()/tank->getMass()) * -direction.y,
		                    0 );

//		tank->setPosition(*tank->getPrevPosition());
//		missile->setPosition(*missile->getPrevPosition());

		// damage tank
//		damage(tank, missile, 100);

	}
}