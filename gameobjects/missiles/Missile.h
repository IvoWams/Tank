// Missile
// Base class for different kinds of Missiles

#ifndef MISSILE_H
#define MISSILE_H

#include <gameobjects/GameObject.h>
#include <gameobjects/players/Player.h>
#include <collision/objects/CollisionLine.h>

class Missile : public GameObject,
				public CollisionLine {
	private:
	protected:
		double	damage;
		double	drag;

		Vector* prevposition;

	public:
		Missile(Player*, double);
		~Missile();

		double			getDrag();
		double			getDamage();
		virtual void	detonate();

		virtual void	move(int);
		virtual void	paint();
		
		virtual Vector* getPoint1();
		virtual Vector* getPoint2();
};

#endif
