#include <interface/PanePhysicsObject.h>
#include <gl/gl.h>
#include <global/Globals.h>
#include <global/Tools.h>

PanePhysicsObject::PanePhysicsObject(double x, double y, PhysicsObject* _pobj) : DragPane(x, y, 350, 85){
	pobj = _pobj;

	engine = Globals::getGlobals()->engine;

	timer = new Timer(100);
	engine->getTimerHandler()->addTimer(timer);
	engine->getTimerHandler()->addListener(this);
	Font* font = engine->getFontHandler()->getFont("fonts/bloq.glf");

	// Some colors
	Color* white = new Color(1,1,1);
	Color* yello = new Color(0.8, 0.8, 0);

	// interfaceobjects
	lblSpeed = new Label(x, y-1, 340, 20, font, ALIGN_RIGHT);
	lblSpeed->setColor(0.8, 0.8, 0, 1);
	lblAcceleration = new Label(x, y+19, 340, 20, font, ALIGN_RIGHT);
	lblAcceleration->setColor(0.8, 0.8, 0, 1);
	lblFriction = new Label(x, y+39, 340, 20, font, ALIGN_RIGHT);
	lblFriction->setColor(0.8, 0.8, 0, 1);
	lblMass = new Label(x, y+59, 340, 20, font, ALIGN_RIGHT);
	lblMass->setColor(0.8, 0.8, 0, 1);

	// due to something weird, renew children
//	children = new vector<InterfaceObject*>;
	
	quickLabel(x, y-1, 340, 20, "Speed");
	quickLabel(x, y+19, 340, 20, "Acceleration");
	quickLabel(x, y+39, 340, 20, "Friction");
	quickLabel(x, y+59, 340, 20, "Mass");
	
	children->push_back(lblSpeed);
	children->push_back(lblAcceleration);
	children->push_back(lblFriction);
	children->push_back(lblMass);
}

PanePhysicsObject::~PanePhysicsObject(){
	delete children;
	delete lblSpeed;

	engine->getTimerHandler()->delListener(this);
	engine->getTimerHandler()->delTimer(timer);
	delete timer;
}

void    PanePhysicsObject::quickLabel(double x, double y, double w, double h, const char* text){
	Label* label = new Label(x, y, w, h, engine->getFontHandler()->getFont("fonts/bloq.glf"), ALIGN_LEFT);
	label->setText(text);
	children->push_back(label);
}


void PanePhysicsObject::onTime(Timer* t){
	if(t==timer){
		lblSpeed->setText("%f", pobj->getSpeed());
		lblAcceleration->setText("%f", lengthVector(*pobj->getAcceleration()));
		lblFriction->setText("%f", lengthVector(*pobj->getFriction()));
		lblMass->setText("%f", pobj->getMass());
	}
}
