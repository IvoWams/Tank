using namespace std;

#ifndef PANEOPTIONS_H
#define PANEOPTIONS_H

#include <interface/DragPane.h>
#include <interface/InputBox.h>
#include <interface/Button.h>
#include <interface/InterfaceListener.h>
#include <interface/InputBox.h>
#include <main/MainEngine.h>

class PaneOptions : public DragPane {
	private:
		MainEngine* engine;
		InputBox*   inp_playername;
		
//		KeyButton*  key_left;
//		KeyButton*  key_right;
//		KeyButton*  key_up;
//		KeyButton*  key_down;
//      KeyButton*  key_fire;
//      KeyButton*  key_turretleft;
//      KeyButton*  key_turretright;
//      KeyButton*  key_turretup;
//      KeyButton*  key_turretdown;

		Label*      lbl_name;
		InputBox*   inp_name;
		
		Label*      lbl_camera;
		Button*     btn_camera1;
		Button*     btn_camera2;

		Button*     btn_close;
		
		Label*      lbl_info1;
		Label*      lbl_info2;
		Label*      lbl_info3;
		
		int         viewtanknr;     // demo uses this value to determine camera
		
		
	public:
		PaneOptions(double, double);
		~PaneOptions();

		virtual void enable();
		virtual void disable();
		
		int     getViewNr(){ return viewtanknr; }

		virtual void onRelease(InterfaceObject*);
		
};

#endif