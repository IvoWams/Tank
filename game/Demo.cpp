#include <game/Demo.h>
#include <gl/gl.h>
#include <gl/glu.h>

Demo::Demo():	MainListener(),
				TimerListener(),
				GameListener(),
				InputListener(){

	engine = Globals::getGlobals()->engine;

	engine->addListener(this);
	engine->getTimerHandler()->addListener(this);
	engine->getInputHandler()->addListener(this);
	engine->getInterfaceHandler()->addListener(this);
	engine->getMouseHandler()->addListener(this);

	engine->getMouseHandler()->resetBoundary();
	
	mousecam = false;
	mousecam_x = 0;
	mousecam_y = 600;
	mouse_x = 0;
	mouse_y = 0;
}

Demo::~Demo(){}

void	Demo::updateCam(Tank* view){
	// Update abovetank vector

	double heading = 180.0 + view->getHeading() + view->getTurretAngle();
	double x = 0;
	double y = 0;
	double mx = 0;
	double my = 0;
	
	mx = sin( (heading+mousecam_x) * (PI/180.0) ) * 10;
	my = cos( (heading+mousecam_x) * (PI/180.0) ) * 10;
	
//	x = sin( heading * (PI/180.0) ) * 50.0;
//	y = cos( heading * (PI/180.0) ) * 50.0;

//	cam_from->x = view->getPosition()->x + 0.3*x;
//	cam_from->y = view->getPosition()->y + 0.3*y;
//	cam_from->z = view->getPosition()->z + 5;

	cam_from->x = view->getPosition()->x + mx + x;
	cam_from->y = view->getPosition()->y + my + y;
	cam_from->z = view->getPosition()->z + 0.1*mousecam_y;

	cam_to->x = view->getPosition()->x - mx - x;
	cam_to->y = view->getPosition()->y - my - y;
	cam_to->z = view->getPosition()->z + 1;

	// Hook engine on our camera vectors
	engine->setCamera(*cam_from, *cam_to);
}


void	Demo::onStart(){
	// Create some funky lighting
	GLfloat ambient[]= { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuse[]= { 1.5f, 1.5f, 1.5f, 1.0f };
	GLfloat position[]= { 0.0f, 0.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION,position);

  	glEnable(GL_LIGHT2);

	GLuint fogfilter = 0;								// Which Fog To Use
	GLfloat fogColor[4]= {0.0f, 0.0f, 0.0f, 0.1f};		// Fog Color

	glFogi(GL_FOG_MODE, GL_EXP);				// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.005f);				// How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
	glFogf(GL_FOG_START, 0.0f);					// Fog Start Depth
	glFogf(GL_FOG_END, 100.0f);					// Fog End Depth
	glEnable(GL_FOG);							// Enables GL_FOG
	
	// Create Demo objects
	// Create objects that come with demo
	game = new GameHandler();

	player_you = new Player("You");
	player_opponent = new Player("Other");

	tank_you = new TankMark1(player_you, 1000);
	tank_you->setPosition(-50,-50,0);
	tank_you->setBarrel(new ShellBarrel(player_you, tank_you->getPosition()));
	
	tanks_opponent = new vector<Tank*>;
	tanks_opponent_ai = new vector<TankAI*>;
	
	int nr_of_tanks = 10;
	int x = 0;
	int y = 0;

	for(int i=0;i<nr_of_tanks;++i){
		Tank* tank_opponent;
		TankAI* tank_opponent_ai;
		
	    tank_opponent = new TankMark2(player_opponent, 1000000, 0.9 + 0.001 * i);
		tank_opponent->setPosition( x, y,0);
		x+=10;if(x>200){ x=0; y+=10; }
		tank_opponent->setBarrel(new ShellBarrel(player_opponent, tank_opponent->getPosition()));
		tank_opponent_ai = new TankAI(game, tank_opponent, tank_you, 10 + i*0.1, 50 + i*0.1);
		
		tanks_opponent->push_back(tank_opponent);
		tanks_opponent_ai->push_back(tank_opponent_ai);

	}

	cam_from = new Vector(1,1,1);
	cam_to = new Vector(1,1,1);

	pane_menu = new PaneMenu(5, Globals::getGlobals()->engine->getRenderer()->getResolution()->getHeight()-66);
	pane_engine = new PaneEngine(1, 1);	// adds itself to the engine
	pane_tank = new PaneTank(605, 1, tank_you);
	pane_physicsobject = new PanePhysicsObject(253, 1, tank_you);
	pane_collisions = new PaneCollisions(253, 88);

	// Initialize objects with engine
	engine->getInputHandler()->addBind(VK_ESCAPE, PRESS_QUIT);

 	engine->getInputHandler()->addBind('A', PRESS_TURRETLEFT);
	engine->getInputHandler()->addBind('D', PRESS_TURRETRIGHT);
	engine->getInputHandler()->addBind('S', PRESS_TURRETDOWN);
	engine->getInputHandler()->addBind('W', PRESS_TURRETUP);
	
	engine->getInputHandler()->addBind(VK_SPACE, PRESS_FIRE);

	engine->getInputHandler()->addBind(VK_UP, PRESS_UP);
	engine->getInputHandler()->addBind(VK_DOWN, PRESS_DOWN);
	engine->getInputHandler()->addBind(VK_LEFT, PRESS_LEFT);
	engine->getInputHandler()->addBind(VK_RIGHT, PRESS_RIGHT);

	game->addListener(this);

	game->addTank(tank_you);
	
	for(int i=0;i<tanks_opponent->size();++i)
		game->addTank((*tanks_opponent)[i]);

	pane_menu->enable();
	pane_collisions->enable();
	pane_engine->enable();
	pane_physicsobject->enable();
	pane_tank->enable();
}

void	Demo::onFrame(){
	double frametime = engine->getFrameTime();

	game->move(frametime);

	// Set the camera based on the settings of paneoptions
	if(pane_menu->getOptions()->getViewNr()==0)
		updateCam(tank_you);
	else
	    updateCam((*tanks_opponent)[pane_menu->getOptions()->getViewNr()]);
		
	game->paint();

	for(int i=0;i<tanks_opponent_ai->size();++i)
		(*tanks_opponent_ai)[i]->think();
	
//	tank_opponent_ai->paint();

	// Make mouse_x move to zero
	if(!mousecam){
//		if(mousecam_x!=0)mousecam_x -= (0.02*mousecam_x)/frametime;
	}

}

void	Demo::onStop(){
	// Clean up all that has been created in onStart
/*
//	pane_menu->disable();
//	pane_physicsobject->disable();
//	pane_collisions->disable();
//	pane_tank->disable();
//	pane_menu->disable();

	engine->getTimerHandler()->delTimer(fpstimer);
	
	// Delete demo objects

	delete fpstimer;
	delete game;

	delete cam_from;
	delete cam_to;

	delete player_you;
	delete tank_you;

	for(int i=0;i<tanks_opponent_ai->size();++i)
	    delete((*tanks_opponent_ai)[i]);

	delete tanks_opponent_ai;
	delete player_opponent;

//	for(int i=0;i<tanks_opponent->size();++i)
//	    delete((*tanks_opponent)[i]);
		
//	delete tanks_opponent;

	delete pane_engine;
	delete pane_physicsobject;
	delete pane_collisions;
	delete pane_tank;
	delete pane_menu;
*/
}

void	Demo::onTime(Timer* timer){
}

void	Demo::onDestroyed(GameObject* t, GameObject* go){
	// tank t was destroyed by gameobject go
}

void	Demo::onKeybind(int key){
	switch(key){
		case PRESS_UP:{				game->accelerate(tank_you, true);break; }
		case RELEASE_UP:{			game->accelerate(tank_you, false);break; }
		case PRESS_DOWN:{			game->brake(tank_you, true);break; }
		case RELEASE_DOWN:{			game->brake(tank_you, false);break; }
		case PRESS_LEFT:{			game->steerLeft(tank_you, true);break; }
		case RELEASE_LEFT:{			game->steerLeft(tank_you, false);break; }
		case PRESS_RIGHT:{			game->steerRight(tank_you, true);break; }
		case RELEASE_RIGHT:{		game->steerRight(tank_you, false);break; }

		case PRESS_TURRETLEFT:{		game->steerTurretLeft(tank_you, true);break; }
		case RELEASE_TURRETLEFT:{	game->steerTurretLeft(tank_you, false);break; }
		case PRESS_TURRETRIGHT:{	game->steerTurretRight(tank_you, true);break; }
		case RELEASE_TURRETRIGHT:{	game->steerTurretRight(tank_you, false);break; }

		case PRESS_TURRETUP:{		game->steerTurretUp(tank_you, true);break; }
		case RELEASE_TURRETUP:{		game->steerTurretUp(tank_you, false);break; }
		case PRESS_TURRETDOWN:{		game->steerTurretDown(tank_you, true);break; }
		case RELEASE_TURRETDOWN:{	game->steerTurretDown(tank_you, false);break; }

		case PRESS_FIRE:{			game->fire(tank_you, true);break; }
		case RELEASE_FIRE:{			game->fire(tank_you, false);break; }

		case PRESS_QUIT:{			engine->quit();break; }
		case RELEASE_QUIT:{			break; }
	}
}

void	Demo::onPress(InterfaceObject* io){
}

void	Demo::onRelease(InterfaceObject* io){
}

void	Demo::onMouseMove(double x, double y){
// Enable turret movement with mouse:
//	game->mouseSteerTurret(tank_you, x*0.1, -y*0.1);
	if(mousecam){
		mousecam_x += 0.4*x;
		if(mousecam_x>360)mousecam_x-=360;
		if(mousecam_x<-360)mousecam_x+=360;

		mousecam_y += 0.4*y;
		if(mousecam_y>1000)mousecam_y=1000;
		if(mousecam_y<0)mousecam_y=0;
		engine->getMouseHandler()->setMouse(50,50);
	}
}

void	Demo::onMouseDown(int button){
	if(button==0)game->fire(tank_you, true);
	
	// Camera scroll
	if(button==2){
		// Enable mouse to cam movement
		mousecam = true;

		// remember original mousepos
		mouse_x = engine->getMouseHandler()->getMouseCursor()->getX();
		mouse_y = engine->getMouseHandler()->getMouseCursor()->getY();

		// mouse movement box
		engine->getMouseHandler()->showMouse(false);
		engine->getMouseHandler()->setMouse(50, 50);
		engine->getMouseHandler()->setBoundary(0, 0, 100, 100);
	}
}

void	Demo::onMouseUp(int button){
	if(button==0)game->fire(tank_you, false);
	if(button==2){
		mousecam = false;
		engine->getMouseHandler()->showMouse(true);
		engine->getMouseHandler()->setMouse(mouse_x, mouse_y);
		engine->getMouseHandler()->resetBoundary();
	}
}

