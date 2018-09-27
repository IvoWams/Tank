#include <interface/PaneCollisions.h>
#include <gl/gl.h>
#include <typeinfo>
#include <gameobjects/tanks/tank.h>

PaneCollisions::PaneCollisions(double x, double y) : DragPane(x, y, 350, 110){
	timer = new Timer(100);
	engine = Globals::getGlobals()->engine;
	Font* font = engine->getFontHandler()->getFont("fonts/bloq.glf");

	counter = 0;

	engine->getTimerHandler()->addTimer(timer);
	engine->getTimerHandler()->addListener(this);
	engine->getCollisionHandler()->addListener(this);

	Color* white = new Color(1,1,1);
	Color* yello = new Color(0.8,0.8,0);

	lblColCounter = new Label(x, y-1, 340, 20, font, ALIGN_RIGHT);
	lblColCounter->setColor(0.8,0.8,0,1);
	lblPairs = new Label(x, y+19, 340, 20, font, ALIGN_RIGHT);
	lblPairs->setColor(0.8,0.8,0,1);
	lblColDist = new Label(x, y+59, 340, 20, font, ALIGN_RIGHT);
	lblColDist->setColor(0.8,0.8,0,1);
	lblColMaxDist = new Label(x, y+79, 340, 20, font, ALIGN_RIGHT);
	lblColMaxDist->setColor(0.8,0.8,0,1);

//	children = new vector<InterfaceObject*>;
	
	quickLabel(x, y-1, 340, 20, "Collisions");
	quickLabel(x, y+19, 340, 20, "Pairs");
	quickLabel(x, y+39, 340, 20, "Pair[0] :");
	quickLabel(x, y+59, 340, 20, "Distance");
	
	children->push_back(lblColCounter);
	children->push_back(lblPairs);
	children->push_back(lblColDist);
}

PaneCollisions::~PaneCollisions(){
	engine->getCollisionHandler()->delListener(this);
	engine->getTimerHandler()->delListener(this);
	engine->getTimerHandler()->delTimer(timer);
	delete timer;
	delete children;
	delete lblColCounter;
}

void    PaneCollisions::quickLabel(double x, double y, double w, double h, const char* text){
	Label* label = new Label(x, y, w, h, engine->getFontHandler()->getFont("fonts/bloq.glf"), ALIGN_LEFT);
	label->setText(text);
	children->push_back(label);
}


void	PaneCollisions::onCollision(CollisionPair* cp){
	counter++;
}

void	PaneCollisions::onTime(Timer* t){
	if(timer==t){
		lblColCounter->setText("%d", counter);
		lblPairs->setText("%d", engine->getCollisionHandler()->getPairs()->size());
		if(engine->getCollisionHandler()->getPairs()->size()>=1){

			
/*
			CollisionBS*	ct1 = (CollisionBS*)(engine->getCollisionHandler()->getPair(0)->getObjectA());
			CollisionBS*	ct2 = (CollisionBS*)(engine->getCollisionHandler()->getPair(0)->getObjectB());
			Vector* c1 = ct1->getCenter();
			Vector* c2 = ct2->getCenter();

			Vector d = Vector(c1->x - c2->x, c1->y - c2->y, c1->z - c2->z);
			float distance = sqrt( d.x*d.x + d.y*d.y + d.z*d.z );
			float maxdistance = ct1->getSize() + ct2->getSize();

*/
			CollisionPair* pair = (*engine->getCollisionHandler()->getPairs())[0];
			if(pair){
				Tank* obj1 = (Tank*)pair->getObjectA();
				Tank* obj2 = (Tank*)pair->getObjectB();
				
				double distance = lengthVector( Vector( obj1->getPosition()->x - obj2->getPosition()->x,
				                                 		obj1->getPosition()->y - obj2->getPosition()->y,
				                                  		obj1->getPosition()->z - obj2->getPosition()->z ));

				lblColDist->setText("%d", (int)distance);
			}
		
		} else {
			lblColDist->setText("-");
		}
	}
}
