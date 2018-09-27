
using namespace std;

#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <main/MainEngine.h>
#include <game/GameListener.h>
#include <collision/CollisionHandler.h>
#include <collision/CollisionListener.h>
#include <collision/CollisionPair.h>
#include <collision/algorithms/CASphereSphere.h>
#include <collision/algorithms/CASphereLine.h>
#include <gameobjects/GameObject.h>
#include <gameobjects/tanks/Tank.h>
#include <gameobjects/missiles/Missile.h>
#include <gameobjects/room/Room.h>
#include <math.h>


// Game controls:
// General movement commands
#define PRESS_UP				0
#define RELEASE_UP				1000
#define PRESS_DOWN				1
#define RELEASE_DOWN			1001
#define PRESS_LEFT				2
#define RELEASE_LEFT			1002
#define PRESS_RIGHT				3
#define RELEASE_RIGHT			1003
#define PRESS_FIRE				4
#define RELEASE_FIRE			1004
#define PRESS_QUIT				5
#define RELEASE_QUIT			1005
#define PRESS_TURRETLEFT		6
#define RELEASE_TURRETLEFT		1006
#define PRESS_TURRETRIGHT		7
#define RELEASE_TURRETRIGHT		1007
#define PRESS_TURRETUP			8
#define RELEASE_TURRETUP		1008
#define PRESS_TURRETDOWN		9
#define RELEASE_TURRETDOWN		1009


class GameHandler : public CollisionListener {
	private:
		MainEngine*                 engine;

		vector<GameListener*>*		listeners;
		vector<Tank*>*				tanks;
		vector<Missile*>*			missiles;
//		vector<GameObject*>*		objects;

		// For gamehandler only?
		void	addMissile(Missile*);
		void	delMissile(Missile*);
		
		Room*   room;               // just a box limiting our arena, for now

	public:
		GameHandler();
		~GameHandler();

		// Data management
		void	addListener(GameListener*);
		void	delListener(GameListener*);
		bool	isListening(GameListener*);

		void	addTank(Tank*);
		void	delTank(Tank*);
		vector<Tank*>*	getTanks();

		// Interface commands
		void	steerLeft (Tank*, bool);
		void	steerRight(Tank*, bool);
		void	accelerate(Tank*, bool);
		void 	brake(Tank*, bool);
		void	steerTurretLeft(Tank*, bool);
		void	steerTurretRight(Tank*, bool);

		void	steerTurretUp(Tank*, bool);
		void	steerTurretDown(Tank*, bool);

		void	mouseSteerTurret(Tank*, double, double);

		void	fire(Tank*, bool);				// activates a barrel to shoot
		void	damage(GameObject*, GameObject*, float);

		// Draw tanks and bullets
		void	paint();

		// Move everything
		void	move(int);

		// Collision events
		void	onCollision(CollisionPair*);
};

#endif
