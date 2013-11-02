#include "Critter.h"
#include <iostream>

void Critter::action(const Coord& coord, Map* caller)
{
	//Have I been attacked?
	if(!Piece::whoAttackedMe())
		return;

	Coord blip(0,0);
	//Is my attacker in range?
	if(radar(coord, blip, getAttackRange(), caller))
	{
		//std::cout << "Critter attack b: " << getAttackPower() << std::endl;
		unsigned int totalDamage = totalAttackDamage();
		//std::cout << "Critter attack a: " << totalDamage << std::endl;
		caller->getHandleAt(blip)->iAttackedYou(this, totalDamage, caller);//Attack him
		setAssailant(0);
	}
}
