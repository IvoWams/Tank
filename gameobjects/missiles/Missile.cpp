#include <gameobjects/Missiles/Missile.h>

Missile::Missile(Player* p, double hp) : GameObject(p, hp){
	damage	= 0;
	drag	= 0;
	prevposition = new Vector(0,0,0);
}

Missile::~Missile(){
	delete prevposition;
}

double	Missile::getDrag(){
	return drag;
}

double	Missile::getDamage(){
	return damage;
}

void	Missile::detonate(){}
void	Missile::move(int){}
void	Missile::paint(){}

Vector*    Missile::getPoint1(){
	return position;
}

Vector*     Missile::getPoint2(){
	return prevposition;
}