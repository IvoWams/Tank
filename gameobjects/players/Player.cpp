#include <gameobjects/players/Player.h>

Player::Player(char* _name){
	name = _name;
}

Player::~Player(){
}

char*	Player::getName(){
	return name;
}
