using namespace std;

#ifndef TANK_H
#define TANK_H

#include <global/GlobalValues.h>
#include <global/Color.h>
#include <gameobjects/GameObject.h>
#include <gameobjects/barrels/Barrel.h>
#include <collision/objects/CollisionSphere.h>

class Tank :	public GameObject,
				public CollisionSphere {

	private:

		double		heading;
		double		turretangle;
		double		turretpitch;

		bool		isAccelerating;
		bool		isBraking;
		bool		isSteeringleft;
		bool		isSteeringright;
		bool		isRotatingturretleft;
		bool		isRotatingturretright;
		bool		isRotatingturretup;
		bool		isRotatingturretdown;
		bool		isfiring;

	protected:

		Barrel*		barrel;

		double		steerspeed;
		double		maxacceleration;
		double		maxspeed;			// new!
		double		turretspeed;
		double      turretpitch_min;
		double      turretpitch_max;

		double		fc_moving;			// friction coefficient of not braking;
		double		fc_brake;			// friction coefficient of braking

		Color*		color_a;
		Color*		color_b;

		Vector*		fire_offset;
		Vector*		dimensions;

	public:
		Tank(Player*, double);
		~Tank();

		// read and  modify abilities
		void	setSteerSpeed(double);
		double	getSteerSpeed();
		void	setMaxAcceleration(double);
		double	getMaxAcceleration();
		void	setMaxSpeed(double);
		double	getMaxSpeed();
		void	setTurretSpeed(double);
		double	getTurretSpeed();

		double	getHeading();
		void	setHeading(double);

		double	getTurretAngle();
		void	setTurretAngle(double);
		double	getTurretPitch();
		void	setTurretPitch(double);

		Vector*	getFireOffset(){ return fire_offset; }

		// interface methods

		void	setFiring(bool b);

		bool	isFiring();	// for handler

		void	setAccelerate(bool);
		void	setBrake(bool);
		void	setSteerLeft(bool);
		void	setSteerRight(bool);
		void	setRotateTurretLeft(bool);
		void	setRotateTurretRight(bool);
		void	setRotateTurretUp(bool);
		void	setRotateTurretDown(bool);

		void	setAim(double, double);

		// note: firing is handled by the gamehandler, tank itself does nothing

		// access to the tanks barrel
		void	setBarrel(Barrel*);
		Barrel*	getBarrel();

		// movement of this object
		void	move(int);

		// decorator
		void	paint();
		
		// Collisionsphere implementation
		virtual Vector*     getCenter();
		virtual double      getSize();
};

#endif
