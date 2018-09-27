#include <gameobjects/tanks/Tank.h>

Tank::Tank(Player* player, double hp) : GameObject(player, hp), CollisionSphere(){

	heading					= 0;
	turretangle				= 0;
	turretpitch				= 0;
	turretpitch_min         = 0;
	turretpitch_max         = 0;
	steerspeed				= 0;
	maxacceleration			= 0;
	maxspeed				= 0;
	turretspeed				= 0;

	isAccelerating			= false;
	isSteeringleft			= false;
	isSteeringright			= false;
	isRotatingturretleft	= false;
	isRotatingturretright	= false;
	isRotatingturretup		= false;
	isRotatingturretdown	= false;
	isfiring				= false;
}

Tank::~Tank(){}

// Ability modifiers

void	Tank::setSteerSpeed(double _speed){
	steerspeed = _speed;
}

double	Tank::getSteerSpeed(){
	return steerspeed;
}

void	Tank::setMaxAcceleration(double _maxacceleration){
	maxacceleration = _maxacceleration;
}

double	Tank::getMaxAcceleration(){
	return maxacceleration;
}

void	Tank::setMaxSpeed(double _maxspeed){
	maxspeed = _maxspeed;
}

double	Tank::getMaxSpeed(){
	return maxspeed;
}

void	Tank::setTurretSpeed(double _turretspeed){
	turretspeed = _turretspeed;
}

double	Tank::getTurretSpeed(){
	return turretspeed;
}

double	Tank::getHeading(){
	return heading;
}

void	Tank::setHeading(double _heading){
	heading = _heading;
}

double	Tank::getTurretAngle(){
	return turretangle;
}

void	Tank::setTurretAngle(double angle){
	turretangle = angle;
}

double	Tank::getTurretPitch(){
	return turretpitch;
}

void	Tank::setTurretPitch(double _turretpitch){
	turretpitch = _turretpitch;
}

// Interface methods

void	Tank::setAccelerate(bool b){
	isAccelerating = b;
}

void	Tank::setBrake(bool b){
	if(b){
		setMaterial(fc_brake);
	} else {
		setMaterial(fc_moving);
	}
}

void	Tank::setSteerLeft(bool b){
	isSteeringleft = b;
}

void	Tank::setSteerRight(bool b){
	isSteeringright = b;
}

void	Tank::setRotateTurretLeft(bool b){
	isRotatingturretleft = b;
}

void	Tank::setRotateTurretRight(bool b){
	isRotatingturretright = b;
}

void	Tank::setRotateTurretUp(bool b){
	isRotatingturretup = b;
}

void	Tank::setRotateTurretDown(bool b){
	isRotatingturretdown = b;
}

void	Tank::setFiring(bool b){
	isfiring = b;
}

bool	Tank::isFiring(){
	return isfiring;
}

void	Tank::setAim(double x, double y){
	turretangle+=x;
	if(turretangle>360)turretangle-=360;
	if(turretangle<0)turretangle+=360;
	turretpitch+=y;
	if(turretpitch>40)turretpitch=40;
	if(turretpitch<0)turretpitch=0;
}

void	Tank::setBarrel(Barrel* _barrel){
	barrel = _barrel;
}

Barrel*	Tank::getBarrel(){
	return barrel;
}

void	Tank::move(int msec){
	if(msec != 0){
		double unit = 1000.0/msec;

		if(isAccelerating){
			// calculate acceleration vector from maxacceleration and heading
			// accelerate to the heading
			setAcceleration( sin( heading * (PI/180.0) ) * maxacceleration,
							 cos( heading * (PI/180.0) ) * maxacceleration,
							 0 );
		}else{
			setAcceleration( 0,0,0 );
		}

		if(maxspeed <= getSpeed()){
			setAcceleration( 0,0,0 );
		}

		if(isSteeringleft){
			heading -= steerspeed/unit;
			if(heading<0)heading+=360;
		}

		if(isSteeringright){
			heading += (steerspeed/unit);
			if(heading>360)heading-=360;
		}

		if(isRotatingturretleft){
			turretangle -= turretspeed/unit;
			if(turretangle<0)turretangle+=360;
		}

		if(isRotatingturretright){
			turretangle += (turretspeed/unit);
			if(turretangle>360)turretangle-=360;
		}

		if(isRotatingturretup)
			turretpitch += (turretspeed/unit); if(turretpitch>turretpitch_max)turretpitch=turretpitch_max;

		if(isRotatingturretdown)
			turretpitch -= (turretspeed/unit); if(turretpitch<turretpitch_min)turretpitch=turretpitch_min;

		// apply physics
		calcAcceleration();
		calcFriction();
		calcCentrifugal();
		calcRotational();
		calcMotion(unit);

		// update barrel too for cooldown
		barrel->move(msec);
	}
}

void	Tank::paint(){}

Vector*    Tank::getCenter(){
	return position;
}

double      Tank::getSize(){
	return 4;
}
