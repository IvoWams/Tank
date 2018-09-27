// Class TankListener
// Events based when tanks do something

using namespace std;

#ifndef GAMELISTENER_H
#define GAMELISTENER_H

#include <gameobjects/GameObject.h>
#include <gameobjects/tanks/Tank.h>

class GameListener {
	private:
	public:
		GameListener();
		~GameListener();

		// possible events
		void	onDestroyed(GameObject*, GameObject*);	// Object x got destroyed by object y
};

#endif
