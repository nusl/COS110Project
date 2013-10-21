#include "Critter.h"

void Critter::action(const Coord& coord, Map* caller)
{
	//Have I been attacked?
	if(!Piece::whoAttackedMe())
		return;

	Coord blip(0,0);
	//Is my attacker in range?
	if(radar(coord, blip, getAttackRange(), caller))
	{
		unsigned int totalDamage = totalAttackDamage();
		caller->getHandleAt(blip)->iAttackedYou(this, totalDamage, caller);//Attack him
		setAssailant(0);
	}
}
