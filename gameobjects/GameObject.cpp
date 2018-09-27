#include <gameobjects/GameObject.h>

GameObject::GameObject(Player* _player, double _maxhp) : PhysicsObject(){
	owner  = _player;
	maxhp  = _maxhp;
	hp	   = _maxhp;
}

GameObject::~GameObject(){}

void	GameObject::heal(double healpoints){
	if(hp+healpoints < maxhp)
		hp+=healpoints;
	else
		hp=maxhp;
}

void	GameObject::damage(double damage){
	if(hp-damage < 0){
	    hp = 0;
	    destroyed = true;
	} else
	    hp -= damage;
}

void	GameObject::paint(){}
