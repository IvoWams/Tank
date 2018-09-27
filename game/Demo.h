using namespace std;

#ifndef DEMO_H
#define DEMO_H

#include <global/Globals.h>
#include <global/Camera.h>
#include <global/Tools.h>
#include <main/MainEngine.h>
#include <main/MainListener.h>
#include <interface/Label.h>
#include <interface/Button.h>
#include <interface/MouseCursor.h>
#include <interface/InputBox.h>
#include <interface/Pane.h>
#include <interface/InterfaceListener.h>
#include <timer/TimerListener.h>
#include <collision/CollisionListener.h>
#include <input/InputListener.h>

#include <game/GameListener.h>
#include <game/GameHandler.h>
#include <gameobjects/tanks/Tank.h>
#include <gameobjects/tanks/TankMark1.h>
#include <gameobjects/tanks/TankMark2.h>
#include <gameobjects/barrels/ShellBarrel.h>
#include <interface/PaneEngine.h>
#include <interface/PanePhysicsObject.h>
#include <interface/PaneCollisions.h>
#include <interface/PaneTank.h>
#include <interface/PaneMenu.h>
#include <ai/TankAI.h>
#include <stdio.h> 

#define PRESS_CAMERA_UP       10
#define RELEASE_CAMERA_UP   1010
#define CAMERA_DOWN           11
#define RELEASE_CAMERA_DOWN 1011

// Stupid fars en zo
class MainEngine;
class TankAI;
class PaneEngine;
class PanePhysicsObject;
class GameHandler;

class Demo : public MainListener,
					TimerListener,
					GameListener,
					InputListener,
					InterfaceListener,
					MouseListener,
					CollisionListener {
	private:
		MainEngine*		engine;
		GameHandler*	game;

		Timer*			fpstimer;
		
		// Font
		Texture*        texture;
		Font*           font;

		// Panels
		PaneEngine*			pane_engine;
		PanePhysicsObject*	pane_physicsobject;
		PaneCollisions*     pane_collisions;
		PaneTank*           pane_tank;
		PaneMenu*           pane_menu;

		// Other game objects
		Player*         player_you;
		Player*         player_opponent;
		
		Tank*			tank_you;
		
		// Containers with tanks and ai of opponent
		vector<Tank*>*			tanks_opponent;
		vector<TankAI*>*        tanks_opponent_ai;

		Vector*			cam_from;
  		Vector*			cam_to;
  		
  		
  		// Manipulation of camera using mouse
  		bool            mousecam;
 		double          mousecam_x, mousecam_y, mousecam_z;
 		double          mouse_x, mouse_y;

		void   			updateCam(Tank*);

	public:
		Demo();
		~Demo();

		// Main event implementation
		void	onStart();
		void	onFrame();
		void	onStop();
		
		// Input trigger implement:
		void	onKeybind(int);

		// Trigger implementation
		void	onTime(Timer*);

		// Collision Handler
		void	onDestroyed(GameObject*, GameObject*);

		// Interfacehandler
		void	onPress(InterfaceObject*);
		void	onRelease(InterfaceObject*);

		// MouseListener
		void	onMouseMove(double, double);
		void	onMouseDown(int);
		void	onMouseUp(int);

};

#endif
