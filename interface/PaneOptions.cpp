#include <interface/PaneOptions.h>
#include <global/Globals.h>

PaneOptions::PaneOptions(double x, double y) : DragPane(x, y, 600, 180){
	engine = Globals::getGlobals()->engine;
	Font* font = engine->getFontHandler()->getFont("fonts/bloq.glf");
	Font* smallfont = engine->getFontHandler()->getFont("fonts/small.glf");

	btn_close = new Button(x+496, y+149, 100, 27, font);
	btn_close->getLabel()->setText("Close");
	children->push_back(btn_close);
	
	lbl_name = new Label(x+10, y+14, 100, 30, font, ALIGN_LEFT);
	lbl_name->setText("Name:");
	children->push_back(lbl_name);

	inp_name = new InputBox(x+130, y+10, 450, 30, font, 255);
	children->push_back(inp_name);

	lbl_camera = new Label(x+10, y+54, 580, 30, font, ALIGN_CENTER);
	lbl_camera->setText("Select a camera");
	children->push_back(lbl_camera);
	
	btn_camera1 = new Button(x+10, y+80, 287, 27, font);
	btn_camera1->getLabel()->setText("Player Tank");
	children->push_back(btn_camera1);

	btn_camera2 = new Button(x+303, y+80, 287, 27, font);
	btn_camera2->getLabel()->setText("Opponent Tank");
	children->push_back(btn_camera2);
	
	lbl_info1 = new Label(x+10, y+120, 580, 20, smallfont, ALIGN_CENTER);
	lbl_info1->setText("Use the directional keys to steer your Tank.");

	lbl_info2 = new Label(x+10, y+135, 580, 20, smallfont, ALIGN_CENTER);
	lbl_info2->setText("Keys A, S, D and W are used to move the turret.");

	lbl_info3 = new Label(x+10, y+150, 580, 20, smallfont, ALIGN_CENTER);
	lbl_info3->setText("Under construction :|");

	children->push_back(lbl_info1);
	children->push_back(lbl_info2);
	children->push_back(lbl_info3);

	viewtanknr = 0;
}

PaneOptions::~PaneOptions(){
	delete lbl_name;
	delete lbl_camera;
	delete btn_camera1;
	delete btn_camera2;
	delete btn_close;
	delete lbl_info1;
	delete lbl_info2;
	delete lbl_info3;
}

void    PaneOptions::enable(){
	if(!engine->getInterfaceHandler()->hasObject(this)){
	 	InterfaceObject::enable();
		engine->getInterfaceHandler()->addObject(btn_close);
		engine->getInterfaceHandler()->addObject(inp_name);
		engine->getInputHandler()->addListener(inp_name);  // Make inputbox listen to input too
		engine->getInterfaceHandler()->addObject(btn_camera1);
		engine->getInterfaceHandler()->addObject(btn_camera2);
	}
}

void    PaneOptions::disable(){
	if(engine->getInterfaceHandler()->hasObject(this)){
		// all objects added to interfacehandler are automatically removed
		engine->getInputHandler()->delListener(inp_name);
	 	InterfaceObject::disable();
	}
}

void    PaneOptions::onRelease(InterfaceObject* io){
	if(io==btn_close){
		// change keycodes
		disable();
	}else if(io==btn_camera1){
		viewtanknr = 0;
	}else if(io==btn_camera2){
		viewtanknr = 1;
	}
	
	// further handling
	DragPane::onRelease(io);
}