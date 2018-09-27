using namespace std;

#ifndef PANETANK_H
#define PANETANK_H

#include <interface/DragPane.h>
#include <timer/TimerListener.h>
#include <timer/Timer.h>
#include <interface/Label.h>
#include <global/Color.h>
#include <main/MainEngine.h>
#include <vector>
#include <gameobjects/tanks/Tank.h>

class PaneTank : public DragPane,
				 public TimerListener {
	private:
		MainEngine*	engine;
		Timer*		timer;
		Tank*		tank;

		Label*		lbl_position;
		Label*		lbl_heading;
		Label*		lbl_turretheading;
		Label*		lbl_turretpitch;
		Label*		lbl_steerspeed;
		Label*		lbl_maxacceleration;
		Label*		lbl_maxspeed;
		Label*		lbl_turretspeed;

		void 		quickLabel(double, double, double, double, const char*);

	public:
		PaneTank(double, double, Tank*);
		~PaneTank();

		void	onTime(Timer*);
		
};

#endif
