#include "Wall.h"

#include "Sprite.h"
#include "Player.h"

#include <cmath>
#include <iostream>

void Wall::iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
{
	if (dynamic_cast<Sprite*>(assailant))
	{
		std::string attackMod = "attacks";

		if (damage > assailant->getAttackPower())
		{
			attackMod = "critical attacks";
		}
		std::cout << "Player " << attackMod << ", dealing a total damage amount of " << ((damage > getCurrentLife()) ? getCurrentLife() : damage) << ".\n";

		// Wall only applies the 10% of life damage penalty and score reduction
		// if the attack actually hits. An attack value of zero indicates a miss.
		if (damage > 0)
		{
			unsigned healthLoss = floor(assailant->getMaxLife() * 0.1);
			static_cast<Sprite*>(assailant)->getOwner()->removeScore(healthLoss);
			assailant->decreaseLife(healthLoss, caller);
		}
	}

	static_cast<Sprite*>(assailant)->knockBack(caller);
}

void Wall::decreaseLife(const unsigned &howMuch, Map *caller)
{
	// Walls cannot die, so we just sit here and watch the damage fly.
	// Hells yeah. I'm a wall.
}
