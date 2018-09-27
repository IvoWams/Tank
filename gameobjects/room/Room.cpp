#include <gameobjects/room/Room.h>
#include <global/Tools.h>
#include <gl/gl.h>

Room::Room(double x, double y, double z) : RootObject(){
	dimensions = new Vector(x, y, z);
}

Room::~Room(){
	delete dimensions;
}

void	Room::paint(){
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glColor4f(1,1,1,1);

	glBegin(GL_QUADS);

	paintRect(	Vector(-10, -10, -100),
				Vector( 10, -10, -100),
				Vector( 10,  10, -100),
				Vector(-10,  10, -100)
				);


	double slab_x = 0.06*dimensions->x;
 	double slab_y = 0.06*dimensions->y;
	double slab_z = 0.12*dimensions->z;

	bool color_inc = false;

	for(double y=-0.5*dimensions->y; y<=0.5*dimensions->y; y+=slab_y)
		for(double x=-0.5*dimensions->x; x<=0.5*dimensions->x; x+=slab_x){
			color_inc=!color_inc;
			if(color_inc){
				glColor4f(0.1,0.1,0.1, 1);
			}else{
				glColor4f(0.5,0.5,0.5, 1);
			}

   			paintRect(	Vector(x + slab_x, y, 0),
						Vector(x, y, 0),
						Vector(x, y + slab_y, 0),
						Vector(x + slab_x, y + slab_y, 0));			// Floor

   			paintRect(	Vector(x, y, dimensions->z),
						Vector(x + slab_x, y, dimensions->z),
						Vector(x + slab_x, y + slab_y, dimensions->z),
						Vector(x, y + slab_y, dimensions->z));			// Roof

		}

	for(double x=-0.5*dimensions->x; x<0.5*dimensions->x; x+=slab_x)
		for(double z=0; z<dimensions->z; z+=slab_z){
			color_inc=!color_inc;
			if(color_inc){
				glColor4f(0.1,0.1,0.1, 1);
			}else{
				glColor4f(0.5,0.5,0.5, 1);
			}

			paintRect(	Vector(x, -0.5*dimensions->y, z+slab_z),
						Vector(x, -0.5*dimensions->y, z),
						Vector(x+slab_x, -0.5*dimensions->y, z),
						Vector(x+slab_x, -0.5*dimensions->y, z+slab_z));		// Back

			paintRect(	Vector(x, 0.5*dimensions->y, z),
						Vector(x, 0.5*dimensions->y, z+slab_z),
						Vector(x+slab_x, 0.5*dimensions->y, z+slab_z),
      					Vector(x+slab_x, 0.5*dimensions->y, z));		// Front

		}


	for(double y=-0.5*dimensions->y; y<0.5*dimensions->y; y+=slab_y)
		for(double z=0; z<dimensions->z; z+=slab_z){
			color_inc=!color_inc;
			if(color_inc){
				glColor4f(0.1,0.1,0.1, 1);
			}else{
				glColor4f(0.5,0.5,0.5, 1);
			}
			paintRect(	Vector(-0.5*dimensions->x, y, z),
						Vector(-0.5*dimensions->x, y, z+slab_z),
						Vector(-0.5*dimensions->x, y + slab_y, z+slab_z),
      					Vector(-0.5*dimensions->x, y + slab_y, z));		// Left

			paintRect(	Vector(0.5*dimensions->x, y, z+slab_z),
						Vector(0.5*dimensions->x, y, z),
						Vector(0.5*dimensions->x, y + slab_y, z),
						Vector(0.5*dimensions->x, y + slab_y, z+slab_z));		// Right

		}

	glEnd();

	glDisable(GL_COLOR_MATERIAL);
}

