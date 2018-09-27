#include <gameobjects/tanks/TankMark2.h>
#include <gl/gl.h>

TankMark2::TankMark2(Player* p, double hp, double mp) : TankMark1(p, hp){
	// Use MP to scale the TankMark1

	// set attributes
//  height = 2 * mp;
//	clearance = 0.2 * mp;
//	width  = 5.0 * mp;
//	length = 7.0 * mp;
//	front_panel_length = 2 * mp;
//	top = height + clearance;

    height = 2;
	clearance = 0.2;
	width  = 5.0;
	length = 7.0;
	front_panel_length = 2;
	top = height + clearance;

	turret_width  = 4.0 * mp;
	turret_length = 5.0 * mp;
	barrel_length = 4 * mp;
	barrel_size = 0.6 * mp;
	turret_clearance = top + 0.1 * mp;
	turret_top = turret_clearance + 0.8 * mp;

	fire_offset = new Vector(0, turret_length, turret_top);
	barrel		= new ShellBarrel(p, position);

//	steerspeed				= 300.0*mp;
//	maxacceleration			= 30*mp;
//	maxspeed				= 30*mp;
//	turretspeed				= 100.0*mp;

	steerspeed				= 150.0;
	maxacceleration			= 30;
	maxspeed				= 30;
	turretspeed				= 150.0;


	// Set exit points deviation for bullets

//	size					= 0.1;		// hmf moet dat hier?

	fc_moving				= 0.8;
	fc_brake				= 0.99;

	// Set physics

//	setMass(10 * mp);
	setMass(10);
	setMaterial(fc_moving);

	color_a = new Color(0.7, 0.3, 0.3);
	color_b = new Color(0.9, 0.8, 0.5);
}

TankMark2::~TankMark2(){
	delete(color_b);
	delete(color_a);
	delete(barrel);
	delete(fire_offset);
}
