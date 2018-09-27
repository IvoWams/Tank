using namespace std;

#ifndef PANEPHYSICSOBJECT_H
#define PANEPHYSICSOBJECT_H

#include <main/MainEngine.h>
#include <physics/PhysicsObject.h>
#include <interface/Label.h>
#include <interface/DragPane.h>
#include <timer/TimerListener.h>
#include <timer/Timer.h>

class PanePhysicsObject :	public DragPane,
							public TimerListener {
	private:
		MainEngine*	engine;
		Timer*		timer;

		PhysicsObject*	pobj;

		Label*			lblSpeed;
		Label*			lblAcceleration;
		Label*			lblFriction;
		Label*			lblMass;

		void 		quickLabel(double, double, double, double, const char*);

	public:
		PanePhysicsObject(double, double, PhysicsObject*);
		~PanePhysicsObject();

		virtual void onTime(Timer*);
};

#endif
