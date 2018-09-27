// class player, todo: extend

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player {
	private:
		char*	name;
	public:
		Player(char*);
		~Player();

		char*	getName();
};

#endif
