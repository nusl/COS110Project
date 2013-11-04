#include "SlenderMan.h"

#include <iostream>

void SlenderMan::action(const Coord &coord, Map *caller)
{
	if(!whoAttackedMe())
		setAssailant(caller->getHandleAt(caller->getSpriteCoord()));

	if (turnCounter < stalkTurns)
	{
		setState('.');
		++turnCounter;
		return;
	}

	// Slender man gradually stalks faster
	if (stalkCount == (2 * stalkTurns))
	{
		stalkCount = 0;
		--stalkTurns;
	}
	++stalkCount;

	Coord location(coord);
	Coord blip(coord);

	if (shouldHunt)
	{
		huntDown(location, caller);
		shouldHunt = false;
	}

	if (crossRadar(location, blip, getAttackRange(), caller))
	{
		unsigned ap = getAttackPower();
		caller->getHandleAt(blip)->iAttackedYou(this, ap, caller);
	} else
	{
		setState(getType());
		shouldHunt = true;
	}

	turnCounter = 0;
}

void SlenderMan::iAttackedYou(Piece * const assailant, unsigned int &damage, Map *caller)
{
	std::cout << "You have angered the Slenderman! He will persue you more viciously." << std::endl;
	--stalkTurns;
	damage = 0;
}
