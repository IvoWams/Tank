using namespace std;

#ifndef PANEENGINE_H
#define PANEENGINE_H

#include <main/MainEngine.h>
#include <interface/Label.h>
#include <interface/DragPane.h>
#include <timer/TimerListener.h>
#include <timer/Timer.h>

class PaneEngine :	public DragPane,
					public TimerListener {

	private:
		MainEngine* engine;
		Timer*		timer;

		Label*		lblMpos;
		Label*		lblDuration;
		Label*		lblFrames;
		Label*		lblFrameTime;
		Label*		lblFPS;

		void 		quickLabel(double, double, double, double, const char*);


	public:
		PaneEngine(double, double);
		~PaneEngine();

		virtual void 	onTime(Timer*);
};

#endif
