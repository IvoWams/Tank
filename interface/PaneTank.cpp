#include <interface/PaneTank.h>
#include <gl/gl.h>

PaneTank::PaneTank(double x, double y, Tank* _tank) : DragPane(x, y, 300, 165){
		tank = _tank;

		engine = Globals::getGlobals()->engine;
		timer = new Timer(100);
		engine->getTimerHandler()->addTimer(timer);
		engine->getTimerHandler()->addListener(this);
		Font* font = engine->getFontHandler()->getFont("fonts/bloq.glf");

		Color*	white = new Color(1,1,1);
		Color*	yello = new Color(0.8,0.8,0);

		lbl_position = new Label(x, y-1, 290, 20, font, ALIGN_RIGHT);
		lbl_position->setColor(0.8, 0.8, 0, 1);
		lbl_heading = new Label(x, y+19, 290, 20, font, ALIGN_RIGHT);
		lbl_heading->setColor(0.8, 0.8, 0, 1);
		lbl_turretheading = new Label(x, y+39, 290, 20, font, ALIGN_RIGHT);
		lbl_turretheading->setColor(0.8, 0.8, 0, 1);
		lbl_turretpitch = new Label(x, y+59, 290, 20, font, ALIGN_RIGHT);
		lbl_turretpitch->setColor(0.8, 0.8, 0, 1);
		lbl_steerspeed = new Label(x, y+79, 290, 20, font, ALIGN_RIGHT);
		lbl_steerspeed->setColor(0.8, 0.8, 0, 1);
		lbl_maxacceleration = new Label(x, y+99, 290, 20, font, ALIGN_RIGHT);
		lbl_maxacceleration->setColor(0.8, 0.8, 0, 1);
		lbl_maxspeed = new Label(x, y+119, 290, 20, font, ALIGN_RIGHT);
		lbl_maxspeed->setColor(0.8, 0.8, 0, 1);
		lbl_turretspeed = new Label(x, y+139, 290, 20, font, ALIGN_RIGHT);
		lbl_turretspeed->setColor(0.8, 0.8, 0, 1);

		children = new vector<InterfaceObject*>;    // ??
		
		quickLabel(x, y-1, 290, 20, "Position");
		quickLabel(x, y+19, 290, 20, "Heading");
		quickLabel(x, y+39, 290, 20, "TurretHeading");
		quickLabel(x, y+59, 290, 20, "TurretPitch");
		quickLabel(x, y+79, 290, 20, "Steerspeed");
		quickLabel(x, y+99, 290, 20, "MaxAcceleration");
		quickLabel(x, y+119, 290, 20, "MaxSpeed");
		quickLabel(x, y+139, 290, 20, "TurretSpeed");
		
		children->push_back(lbl_position);
		children->push_back(lbl_heading);
		children->push_back(lbl_turretheading);
		children->push_back(lbl_turretpitch);
		children->push_back(lbl_steerspeed);
		children->push_back(lbl_maxacceleration);
		children->push_back(lbl_maxspeed);
		children->push_back(lbl_turretspeed);

}

PaneTank::~PaneTank(){
	for(int i=0;i<children->size();++i)
		delete (*children)[i];
}

void    PaneTank::quickLabel(double x, double y, double w, double h, const char* text){
	Label* label = new Label(x, y, w, h, engine->getFontHandler()->getFont("fonts/bloq.glf"), ALIGN_LEFT);
	label->setText(text);
	children->push_back(label);
}

void	PaneTank::onTime(Timer* t){
	if(t==timer){
		lbl_position->setText("%d:%d:%d", (int)tank->getPosition()->x, (int)tank->getPosition()->y, (int)tank->getPosition()->z);
		lbl_heading->setText("%d", (int)tank->getHeading());
		lbl_turretheading->setText("%d", (int)tank->getTurretAngle());
		lbl_turretpitch->setText("%d", (int)tank->getTurretPitch());
		lbl_steerspeed->setText("%d", (int)tank->getSteerSpeed());
		lbl_maxacceleration->setText("%d", (int)tank->getMaxAcceleration());
		lbl_maxspeed->setText("%d", (int)tank->getMaxSpeed());
		lbl_turretspeed->setText("%d", (int)tank->getTurretSpeed());
	}
}
