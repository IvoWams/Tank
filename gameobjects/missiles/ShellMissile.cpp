#include <gameobjects/Missiles/ShellMissile.h>
#include <gl/gl.h>
#include <global/Tools.h>

ShellMissile::ShellMissile(Player* p, double hp, double _damage) : Missile(p, hp){
	damage	= _damage;
	drag	= 0.01;
//	size	= 0.01;	// collision size
	alpha   = 0;

//	setMaterial(0.9);
	setMass(5);
	setGravity( 0,0,-50 );

	xrot = 0;
	yrot = 0;
}

ShellMissile::~ShellMissile(){}

void	ShellMissile::detonate(){
	// just destroy the Missile
	hp = 0;
}

void	ShellMissile::move(int msec){
	if(msec != 0){
		// Keep track of previous position (for collision detection)
		prevposition->x = position->x;
		prevposition->y = position->y;
		prevposition->z = position->z;

		// just move along the bullet, dont do anything else
		
		calcAcceleration();
		calcFriction();
//		calcGravity();
		calcMotion(1000.0/msec);
	}
}

void    ShellMissile::paintCube(const Vector& center, double size){
	glBegin(GL_QUADS);

	paintRect(  Vector(center.x - 0.5*size, center.y - 0.5*size, center.z - 0.5*size),
	            Vector(center.x + 0.5*size, center.y - 0.5*size, center.z - 0.5*size),
	            Vector(center.x + 0.5*size, center.y + 0.5*size, center.z - 0.5*size),
	            Vector(center.x - 0.5*size, center.y + 0.5*size, center.z - 0.5*size)
		 );

	paintRect(  Vector(center.x - 0.5*size, center.y - 0.5*size, center.z + 0.5*size),
	            Vector(center.x + 0.5*size, center.y - 0.5*size, center.z + 0.5*size),
	            Vector(center.x + 0.5*size, center.y + 0.5*size, center.z + 0.5*size),
	            Vector(center.x - 0.5*size, center.y + 0.5*size, center.z + 0.5*size)
		 );

	paintRect(  Vector(center.x - 0.5*size, center.y - 0.5*size, center.z - 0.5*size),
	            Vector(center.x - 0.5*size, center.y + 0.5*size, center.z - 0.5*size),
	            Vector(center.x - 0.5*size, center.y + 0.5*size, center.z + 0.5*size),
				Vector(center.x - 0.5*size, center.y - 0.5*size, center.z + 0.5*size)
		);

	paintRect(  Vector(center.x + 0.5*size, center.y - 0.5*size, center.z - 0.5*size),
	            Vector(center.x + 0.5*size, center.y + 0.5*size, center.z - 0.5*size),
	            Vector(center.x + 0.5*size, center.y + 0.5*size, center.z + 0.5*size),
				Vector(center.x + 0.5*size, center.y - 0.5*size, center.z + 0.5*size)
		);

	paintRect(  Vector(center.x - 0.5*size, center.y - 0.5*size, center.z - 0.5*size),
	            Vector(center.x + 0.5*size, center.y - 0.5*size, center.z - 0.5*size),
	            Vector(center.x + 0.5*size, center.y - 0.5*size, center.z + 0.5*size),
				Vector(center.x - 0.5*size, center.y - 0.5*size, center.z + 0.5*size)
		);

	paintRect(  Vector(center.x - 0.5*size, center.y + 0.5*size, center.z - 0.5*size),
	            Vector(center.x + 0.5*size, center.y + 0.5*size, center.z - 0.5*size),
	            Vector(center.x + 0.5*size, center.y + 0.5*size, center.z + 0.5*size),
				Vector(center.x - 0.5*size, center.y + 0.5*size, center.z + 0.5*size)
		);

	glEnd();
}


void	ShellMissile::paint(){
	glPushMatrix();

//	glLoadIdentity();

	// Very simple shadow
	glTranslatef(position->x, position->y, 0);

	glColor4f(0,0,0,0.4);
	
	double size = 0.4;

	glBegin(GL_QUADS);
	glVertex3f(-0.5*size, -0.5*size, 0.01);
	glVertex3f( 0.5*size, -0.5*size, 0.01);
	glVertex3f( 0.5*size,  0.5*size, 0.01);
	glVertex3f(-0.5*size,  0.5*size, 0.01);
	glEnd();

	glTranslatef(0, 0, position->z);
	alpha += 30;
	glRotatef(alpha, 0.3, 0.5, 0.9);

	glColor4f(1,0.5,0.0,0.3);
	
	for(int i=0;i<15;++i){
		glRotatef(22, 0.3, 0.5, 0.9);
	    paintCube( Vector(0,0,0), size );
	}
	
	
	glPopMatrix();
}
