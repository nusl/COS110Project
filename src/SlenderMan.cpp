#include "SlenderMan.h"

#include <iostream>

void SlenderMan::action(const Coord &coord, Map *caller)
{
	if (turnCounter < stalkTurns)
	{
		setState(newState);
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

	if (shouldHunt)
	{
		Coord moveCoord(coord);
		//std::cout << coord.x << " : " << coord.y << " = " << ((caller->getSpriteCoord().x > coord.x) ? 1 : -1) << std::endl;
		//std::cout << caller->getSpriteCoord().x << " : " << caller->getSpriteCoord().y << " = " << ((caller->getSpriteCoord().y > coord.x) ? 1 : -1) << std::endl;
		if (caller->getSpriteCoord().x != coord.x)
		{
			moveCoord.x += (caller->getSpriteCoord().x > coord.x) ? 1 : -1;
		}
		if (caller->getSpriteCoord().y != coord.y)
		{
			moveCoord.y += (caller->getSpriteCoord().y > coord.x) ? 1 : -1;
		}
		if (caller->inBoundary(moveCoord))
		{
			setState(getType());
			if (moveCoord == caller->getSpriteCoord())
			{
				unsigned ap = getAttackPower();
				caller->getHandleAt(moveCoord)->iAttackedYou(this, ap, caller);
			} else
			{
				caller->destroyPieceAt(coord);
				newState = caller->getHandleAt(moveCoord)->getState();
				caller->placePieceAtForce(this, moveCoord);
			}
		}
	}

	setState(getType());
	shouldHunt = true;

	turnCounter = 0;
}

void SlenderMan::iAttackedYou(Piece * const assailant, unsigned int &damage, Map *caller)
{
	std::cout << "You have angered the Slenderman! He will persue you more viciously." << std::endl;
	--stalkTurns;
	damage = 0;
}
