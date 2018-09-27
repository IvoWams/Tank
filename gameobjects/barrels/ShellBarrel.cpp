#include <gameobjects/barrels/ShellBarrel.h>

ShellBarrel::ShellBarrel(Player* _owner, Vector* _hook) : Barrel(_owner, _hook){
	cooldown = 500;
	power    = 200;
}

ShellBarrel::~ShellBarrel(){}

Missile*	ShellBarrel::obtainMissile(){
	resetCooldown();
	return new ShellMissile(owner, 10, 10);	// shellmissle with damage 10 and 10 hp
}
