#include <game/main.h>
#include <game/Demo.h>

Globals*	globals	= Globals::getGlobals();
MainEngine* engine	= globals->engine;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	// Pass message interfacing onto the engine
	return EngineWndProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow){
	// Create your demo here :
	Demo* demo = new Demo();
	
	// Pass windows parameters onto engine
	EngineWinMain(hInstance, hPrevInstance, lpCmdLine, iCmdShow);

	MSG		msg;
    return msg.wParam;
}
