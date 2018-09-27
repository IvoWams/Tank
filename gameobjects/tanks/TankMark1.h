// Tank Mark 1
// Extends normal tank

using namespace std;

#ifndef TANKMARK1_H
#define TANKMARK1_H

#include <renderer/Renderer.h>
#include <global/Tools.h>

#include <gameobjects/tanks/Tank.h>
#include <gameobjects/barrels/ShellBarrel.h>

class TankMark1 : public Tank {
	private:
	protected:
	    double height;
	    double clearance;
	    double width;
	    double length;
	    double front_panel_length;
	    double top;

	    double turret_length;
		double barrel_length;
 		double barrel_size;
	    double turret_width;
	    double turret_clearance;
	    double turret_top;


	public:
		TankMark1(Player*, double);
		~TankMark1();
		void paint();	// only overwrites paint method
};

#endif
