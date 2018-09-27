#include <gameobjects/barrels/Barrel.h>

Barrel::Barrel(Player* _owner, Vector* hook){
	owner		 	= _owner;
	position 		= hook;
	cooldown_counter = 0;
	cooldown 		 = 0;
	power			 = 0;
	drag			 = 0;
}

Barrel::~Barrel(){}

void	Barrel::setCooldown(int _cooldown){
	cooldown = _cooldown;
}

int		Barrel::getCooldown(){
	return cooldown;
}

void	Barrel::setPower(double _power){
	power = _power;
}

double	Barrel::getPower(){
	return power;
}

bool	Barrel::ready(){
	return cooldown_counter <= 0;
}

void	Barrel::move(int msec){
	if(msec != 0)
		cooldown_counter-=msec;
}

void        Barrel::resetCooldown(){
	cooldown_counter = cooldown;
}

Missile*	Barrel::obtainMissile(){
	// reset cooldown upon retrieving missle
	return new Missile(owner, 0);
}
