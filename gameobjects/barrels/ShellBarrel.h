// Simple form of a barrel
// this turret can fire basic shells in 1 second intervalls with a bit of power

using namespace std;

#ifndef SHELLBARREL_H
#define SHELLBARREL_H

#include <gameobjects/barrels/Barrel.h>
#include <gameobjects/missiles/ShellMissile.h>		// Fires shells

class ShellBarrel : public Barrel {
	private:
	public:
		ShellBarrel(Player*, Vector*);
		~ShellBarrel();

		Missile*	obtainMissile();
};

#endif

