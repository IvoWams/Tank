// Class Barrel
// A barrel can be anything from what a missle can be fired (or so it seems)
// Different types of weapons should extend this class

using namespace std;

#ifndef BARREL_H
#define BARREL_H

#include <global/RootObject.h>
#include <gameobjects/missiles/Missile.h>

class Barrel : public RootObject {
	private:

	protected:
		int		cooldown_counter;

		Player*	owner;
		int		cooldown;

		double	power;
		double	drag;

	public:
		Barrel(Player*, Vector*);		// owned by player, hooked up on vector ...
		~Barrel();

		// attributes
		void	setCooldown(int);
		int		getCooldown();
		void	setPower(double);
		double	getPower();

		bool	ready();

		// update timer
		void	move(int);
		
		void    resetCooldown();

		// Create a missle for the handler
		virtual Missile*		obtainMissile();
};

#endif
