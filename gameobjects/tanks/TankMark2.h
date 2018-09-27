// Tank Mark 1
// Extends normal tank

using namespace std;

#ifndef TANKMARK2_H
#define TANKMARK2_H

#include <gameobjects/tanks/TankMark1.h>
#include <gameobjects/barrels/ShellBarrel.h>

class TankMark2 : public TankMark1 {
	private:
	public:
		TankMark2(Player*, double, double);
		~TankMark2();
		// bla
};

#endif
