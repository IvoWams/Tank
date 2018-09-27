// ShellMissile
// Simple example to create Missile types
// This Missile uses a basic ballistic path and can have variable damage

// See constructor for physics settings about the Missile

using namespace std;

#ifndef SHELLMISSILE_H
#define SHELLMISSILE_H

#include <gameobjects/Missiles/Missile.h>
#include <global/Tools.h>

class ShellMissile : public Missile {
	private:
		double xrot;
		double yrot;
		double alpha;       // rotation of bullet
		
		void    paintCube(const Vector&, double);

	public:
		ShellMissile(Player*, double, double);
		~ShellMissile();

		void	detonate();
		void	move(int);
		void	paint();
};

#endif
