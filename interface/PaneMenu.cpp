#include <interface/PaneMenu.h>
#include <global/Globals.h>

PaneMenu::PaneMenu(double x, double y) : DragPane(x, y, 200, 62){
	engine = Globals::getGlobals()->engine;
	Font* font = engine->getFontHandler()->getFont("fonts/bloq.glf");
	Font* smallfont = engine->getFontHandler()->getFont("fonts/small.glf");

//	children = new vector<InterfaceObject*>;        // Still buggy without?

	btn_options = new Button(x+4, y+4, 192, 27, font);
	btn_options->getLabel()->setText("Options");
	children->push_back(btn_options);

	btn_quit = new Button(x+4, y+32, 192, 27, font);
	btn_quit->getLabel()->setText("Quit");
	children->push_back(btn_quit);

	engine->getInterfaceHandler()->addListener(this);
	pane_options = new PaneOptions((Globals::getGlobals()->engine->getRenderer()->getResolution()->getWidth()/2)-300, (Globals::getGlobals()->engine->getRenderer()->getResolution()->getHeight()/2)-90);
//	pane_options->enable();
}

PaneMenu::~PaneMenu(){
	delete btn_quit;
	delete btn_options;
}

void    PaneMenu::enable(){
	InterfaceObject::enable();
	engine->getInterfaceHandler()->addObject(btn_options);
	engine->getInterfaceHandler()->addObject(btn_quit);
}

void    PaneMenu::onRelease(InterfaceObject* io){

	if(io==btn_options){
		// Go and do something with options
		pane_options->enable();
	}else if(io==btn_quit){
		engine->quit();
	}

	// continue with dragpane functions (dragging)
	DragPane::onRelease(io);
}