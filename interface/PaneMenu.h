using namespace std;

#ifndef PANEMENU_H
#define PANEMENU_H

#include <interface/DragPane.h>
#include <interface/InterfaceObject.h>
#include <interface/Button.h>
#include <interface/InputBox.h>
#include <interface/PaneOptions.h>
#include <main/MainEngine.h>

class PaneMenu : public DragPane {
	private:
		MainEngine*	engine;
		Button*     btn_options;
		Button*     btn_quit;
		InputBox*   inp_text;
		
		PaneOptions*    pane_options;
		
	public:
		PaneMenu(double, double);
		~PaneMenu();

		void    enable();

		PaneOptions*        getOptions(){ return pane_options; }
		
		virtual void        onRelease(InterfaceObject*);
};

#endif