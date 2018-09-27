using namespace std;

#ifndef PANECOLLISIONS_H
#define PANECOLLISIONS_H

#include <main/MainEngine.h>
#include <interface/Label.h>
#include <interface/DragPane.h>
#include <collision/CollisionListener.h>
#include <timer/TimerListener.h>
#include <timer/Timer.h>

class PaneCollisions :	public DragPane,
						public TimerListener,
						public CollisionListener {
	private:
		MainEngine*	engine;
		Timer*		timer;	// for update

		Label*		lblColCounter;
		Label*		lblPairs;
		Label*		lblColDist;
		Label*		lblColMaxDist;
		long		counter;

		void 		quickLabel(double, double, double, double, const char*);

	public:
		PaneCollisions(double, double);
		~PaneCollisions();
		
		void	onCollision(CollisionPair*);
		void	onTime(Timer*);
};

#endif
