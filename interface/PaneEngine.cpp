#include <interface/PaneEngine.h>
#include <gl/gl.h>

PaneEngine::PaneEngine(double x, double y) : DragPane(x, y, 250, 105){
	// Create timer for updates
	timer = new Timer(100);

	// Get engine
	engine = Globals::getGlobals()->engine;

	// subscribe this pane as a timerlistener
	engine->getTimerHandler()->addTimer(timer);
	engine->getTimerHandler()->addListener(this);
	Font* font = engine->getFontHandler()->getFont("fonts/bloq.glf");

	// BUG children renewed, or app will close? (prolly null pointer, debugger doesnt work)
//	children = new vector<InterfaceObject*>;
	
	quickLabel(x, y-1, 290, 20, "Mouse");
	quickLabel(x, y+19, 290, 20, "Duration");
	quickLabel(x, y+39, 290, 20, "Frames");
	quickLabel(x, y+59, 290, 20, "Frametime");
	quickLabel(x, y+79, 290, 20, "FPS");

	lblMpos			= new Label(x, y-1, 240, 20, font, ALIGN_RIGHT);
	lblMpos->setColor(0.8,0.8,0,1);
	lblDuration		= new Label(x, y+19, 240, 20, font, ALIGN_RIGHT);
	lblDuration->setColor(0.8,0.8,0,1);
	lblFrames		= new Label(x, y+39, 240, 20, font, ALIGN_RIGHT);
	lblFrames->setColor(0.8,0.8,0,1);
	lblFrameTime	= new Label(x, y+59, 240, 20, font, ALIGN_RIGHT);
	lblFrameTime->setColor(0.8,0.8,0,1);
	lblFPS			= new Label(x, y+79, 240, 20, font, ALIGN_RIGHT);
	lblFPS->setColor(0.8,0.8,0,1);

	children->push_back(lblMpos);
	children->push_back(lblDuration);
	children->push_back(lblFrames);
	children->push_back(lblFrameTime);
	children->push_back(lblFPS);
}

PaneEngine::~PaneEngine(){
	// Unsubscribe
	engine->getTimerHandler()->delTimer(timer);
	engine->getTimerHandler()->delListener(this);
	
	// delete contents of children
	for(int i=0;i<children->size();++i)
	    delete (*children)[i];
}

void    PaneEngine::quickLabel(double x, double y, double w, double h, const char* text){
	Label* label = new Label(x, y, w, h, engine->getFontHandler()->getFont("fonts/bloq.glf"), ALIGN_LEFT);
	label->setText(text);
	children->push_back(label);
}

void	PaneEngine::onTime(Timer* t){
	if(t==timer){
		// maybe move to onmousemove
		lblMpos->setText("%d:%d", (int)Globals::getGlobals()->engine->getMouseHandler()->getMouseCursor()->getX(), (int)Globals::getGlobals()->engine->getMouseHandler()->getMouseCursor()->getY());
		lblDuration->setText("%d", engine->getDuration());
		lblFrames->setText("%d", (int)engine->getFrames());

		lblFrameTime->setText("%d", (int)engine->getFrameTime());
		lblFPS->setText("%d", (int)engine->getFPS());
	}
}

