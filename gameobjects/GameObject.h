// Game Object
// All game objects must extend this class, like tanks and missles and so forth

using namespace std;

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <physics/PhysicsObject.h>
#include <gameobjects/players/Player.h>

class GameObject : public PhysicsObject {
	protected:
		double		hp;
		Player*		owner;
		double		maxhp;
		bool        destroyed;

	public:
		GameObject(Player*, double);
		~GameObject();

		void		heal(double);			// repair n stuff
		void		damage(double);			// damage this object
		bool		isDestroyed(){ return destroyed; }
		
		Player*     getOwner(){ return owner; }

		void        setHP(double _hp){ hp = _hp; }
		void        setMaxHP(double _maxhp){ maxhp = _maxhp; }
		double      getHP(){ return hp; }
		double      getMaxHP(){ return maxhp; }

		virtual void	paint();	// decorator, to be implemented
};

#endif
