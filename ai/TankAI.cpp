#include <ai/TankAI.h>
#include <gl/gl.h>

TankAI::TankAI(GameHandler* _handler, Tank* _control, Tank* _target, int _distance_inner, int _distance_outer){
	handler = _handler;
	control = _control;
	target  = _target;

	change_lane = 0;

	distance_inner = _distance_inner;	// AI tries to move the tank to at least a distance of 10
	distance_outer = _distance_outer;	// and at most 50
}

TankAI::~TankAI(){}

void	TankAI::changeTarget(Tank* _target){
	target = _target;
}

void	TankAI::setInnerDistance(float _distance){
	distance_inner = _distance;
}

void	TankAI::setOuterDistance(float _distance){
	distance_outer = _distance;
}

void	TankAI::think(){
	Vector difv;
	divVector(difv, *control->getPosition(), *target->getPosition());

	distance = (int)lengthVector(difv);
	int difangle = (int)getAngle( Vector(0,0,0), difv);

    int heading = (int)control->getHeading();

	int turretangle = ((int)control->getTurretAngle() + heading) % 360;
	int delta_aim = (360+difangle-turretangle) % 360;

	// If distance is lower than x, make them move around opponent or else move in direction of opponent
	int delta_heading = 0;
	control->setAccelerate(true);

	if(distance > distance_outer){
		delta_heading = 360+difangle-heading;
		change_lane++;
	}else if (distance > distance_inner){

		if(change_lane % 2 == 0){
			delta_heading = 270+difangle-heading;
		} else {
			delta_heading = 450+difangle-heading;
		}
	}else{ // distance <= distance_inner
		delta_heading = 180+difangle-heading;
		change_lane++;
	}

    if(delta_aim<180 && delta_aim>3){
		control->setRotateTurretLeft(false);
		control->setRotateTurretRight(true);
	} else if(delta_aim>=180 && delta_aim < 357){
		control->setRotateTurretLeft(true);
		control->setRotateTurretRight(false);
	} else {
		control->setRotateTurretLeft(false);
		control->setRotateTurretRight(false);
	}

	while(delta_heading>360)delta_heading-=360;
	while(delta_heading<0)delta_heading+=360;
	
	if(distance < 100 && (delta_heading < 10 || delta_heading > 350)){
//		control->setFiring(true);
	}else{
//		control->setFiring(false);
	}

//	if(distance > 15){
	if(delta_heading<180){
		control->setSteerLeft(false);
		control->setSteerRight(true);
	} else {
		control->setSteerLeft(true);
		control->setSteerRight(false);
	}

}

void	TankAI::paint(){
	glPushMatrix();
	glEnable(GL_BLEND);
	int segments = 30;

	glColor4f(1,0,0, 0.1);
	glTranslatef(control->getPosition()->x,control->getPosition()->y,control->getPosition()->z+0.01);

	if(distance > distance_outer){
	}else if(distance > distance_inner){
		glBegin(GL_POLYGON);
		for(int i=0;i<segments;i++){
			glVertex3f( sin(i*2*3.141592654/segments)* distance_outer, cos(i*2*3.141592654/segments)* distance_outer, 0);
			glVertex3f( sin((i+1)*2*3.141592654/segments)* distance_outer, cos((i+1)*2*3.141592654/segments)* distance_outer, 0);
		}
	glEnd();
	}else{
		glBegin(GL_POLYGON);
		for(int i=0;i<segments;i++){
			glVertex3f( sin(i*2*3.141592654/segments)* distance_inner, cos(i*2*3.141592654/segments)* distance_inner, 0);
			glVertex3f( sin((i+1)*2*3.141592654/segments)* distance_inner, cos((i+1)*2*3.141592654/segments)* distance_inner, 0);
		}
		glEnd();
	}
	glPopMatrix();
}
