#include <gameobjects/tanks/TankMark1.h>
#include <gl/gl.h>

TankMark1::TankMark1(Player* p, double hp) : Tank(p, hp){
	// set attributes
    height = 2;
	clearance = 0.2;
	width  = 5.0;
	length = 7.0;
	front_panel_length = 2;
	top = height + clearance;

	turret_width  = 4.0;
	turret_length = 5.0;
	barrel_length = 4;
	barrel_size = 0.6;
	turret_clearance = top + 0.1;
	turret_top = turret_clearance + 0.8;

	fire_offset = new Vector(0, turret_length, turret_top);

	barrel					= new ShellBarrel(p, position);

	steerspeed				= 150.0;
	maxacceleration			= 50;
	maxspeed				= 60;
	turretspeed				= 100.0;
	turretpitch_min         = 0;
	turretpitch_max         = 10;

//	size					= 0.1;		// hmf moet dat hier?

	fc_moving				= 0.4;	// almost no friction if moving
	fc_brake				= 0.99;	// lot of friction when braking

	// Set physics

	setMass(15);
	setMaterial(fc_moving);

	// Colors
	color_a = new Color(0.1, 0.5, 0.9);
	color_b = new Color(0.3, 0.9, 0.9);
}

TankMark1::~TankMark1(){
	delete(color_b);
	delete(color_a);
	delete(barrel);
	delete(fire_offset);
}

void	TankMark1::paint(){
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	// test representation
	glPushMatrix();	// save current scene
	glTranslatef(position->x, position->y, position->z);	// position tha thang

	glRotatef(-getHeading(), 0, 0, 1);	// move in that direction

	// Body Works
	glBegin(GL_QUADS);

	glColor3f( color_a->R, color_a->G, color_a->B );

 	paintRect(	Vector(0.5*width, -0.5*length, top),
				Vector(-0.5*width, -0.5*length, top),
        		Vector(-0.5*width, 0.5*length, top),
                Vector(0.5*width, 0.5*length, top));	// Top Slab

	paintRect(	Vector(-0.5*width, 0.5*length + front_panel_length, clearance),
				Vector(0.5*width, 0.5*length + front_panel_length, clearance),
				Vector(0.5*width, 0.5*length, top),
				Vector(-0.5*width, 0.5*length, top));	// Front Slab

	paintRect(	Vector(-0.5*width, -0.5*length, top),
				Vector(0.5*width, -0.5*length, top),
				Vector(0.5*width, -0.5*length, clearance),
				Vector(-0.5*width, -0.5*length, clearance));	// Back Slab

	paintRect(  Vector(-0.5*width, 0.5*length, top),
				Vector(-0.5*width, -0.5*length, top),
				Vector(-0.5*width, -0.5*length, clearance),
				Vector(-0.5*width, 0.5*length, clearance));		// Left Slab

	paintRect(  Vector(0.5*width, -0.5*length, top),
				Vector(0.5*width, 0.5*length, top),
				Vector(0.5*width, 0.5*length, clearance),
				Vector(0.5*width, -0.5*length, clearance));		// Right Slab

	glEnd();

	glBegin(GL_TRIANGLES);

	paintTria(	Vector(-0.5*width, 0.5*length + front_panel_length, clearance),
				Vector(-0.5*width, 0.5*length, top),
				Vector(-0.5*width, 0.5*length, clearance));		// Left Slab front fill

	paintTria(	Vector(0.5*width, 0.5*length, top),
				Vector(0.5*width, 0.5*length + front_panel_length, clearance),
				Vector(0.5*width, 0.5*length, clearance));		// Right Slab front fill

	glEnd();

	// Start turret without barrel
	glRotatef(-getTurretAngle(), 0, 0, 1);
	glBegin(GL_QUADS);
	glColor3f( color_b->R, color_b->G, color_b->B );

	paintRect(	Vector( 0.5*turret_width, -0.5*turret_length, turret_top),
				Vector(-0.5*turret_width, -0.5*turret_length, turret_top),
				Vector(-0.5*turret_width,  0.5*turret_length, turret_top),
				Vector( 0.5*turret_width,  0.5*turret_length, turret_top));	// Turret Top slab

	paintRect(	Vector(-0.5*turret_width,  0.5*turret_length, turret_top),
				Vector(-0.5*turret_width, -0.5*turret_length, turret_top),
				Vector(-0.5*turret_width, -0.5*turret_length, turret_clearance),
				Vector(-0.5*turret_width,  0.5*turret_length, turret_clearance));	// Turret Left Slab

	paintRect(	Vector( 0.5*turret_width, -0.5*turret_length, turret_top),
				Vector( 0.5*turret_width,  0.5*turret_length, turret_top),
				Vector( 0.5*turret_width,  0.5*turret_length, turret_clearance),
				Vector( 0.5*turret_width, -0.5*turret_length, turret_clearance));	// Turret Right Slab

	paintRect(	Vector( 0.5*turret_width, 0.5*turret_length, turret_top),
				Vector(-0.5*turret_width, 0.5*turret_length, turret_top),
				Vector(-0.5*turret_width, 0.5*turret_length, turret_clearance),
				Vector( 0.5*turret_width, 0.5*turret_length, turret_clearance)); 	// Turret front Slab

	paintRect(	Vector(-0.5*turret_width, -0.5*turret_length, turret_top),
				Vector( 0.5*turret_width, -0.5*turret_length, turret_top),
				Vector( 0.5*turret_width, -0.5*turret_length, turret_clearance),
				Vector(-0.5*turret_width, -0.5*turret_length, turret_clearance)); 	// Turret front Slab

	glEnd();

	glTranslatef(0, 0.5*turret_length, 0);
	glRotatef(getTurretPitch(), 1, 0, 0);

	glBegin(GL_QUADS);

	paintRect(	Vector(-0.5*barrel_size, barrel_length, turret_top),
				Vector( 0.5*barrel_size, barrel_length, turret_top),
				Vector( 0.5*barrel_size, 0, turret_top),
				Vector(-0.5*barrel_size, 0, turret_top));

	paintRect(	Vector(-0.5*barrel_size, barrel_length, turret_top - barrel_size),
				Vector(-0.5*barrel_size, barrel_length, turret_top),
				Vector(-0.5*barrel_size, 0, turret_top),
				Vector(-0.5*barrel_size, 0, turret_top - barrel_size));

	paintRect(	Vector( 0.5*barrel_size, barrel_length, turret_top - barrel_size),
				Vector(-0.5*barrel_size, barrel_length, turret_top - barrel_size),
				Vector(-0.5*barrel_size, 0, turret_top - barrel_size),
				Vector( 0.5*barrel_size, 0, turret_top - barrel_size));

	paintRect(	Vector( 0.5*barrel_size, barrel_length, turret_top),
				Vector( 0.5*barrel_size, barrel_length, turret_top - barrel_size),
				Vector( 0.5*barrel_size, 0, turret_top - barrel_size),
				Vector( 0.5*barrel_size, 0, turret_top));

	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

	glPopMatrix();	// continue previous scene
}
