#include "Boulder.h"

#include "Sprite.h"
#include "Player.h"

void Boulder::iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
{
	if ((damage > assailant->getAttackPower()) && (damage >= getCurrentLife()))
	{
		static_cast<Sprite*>(assailant)->getOwner()->addScore(150);
	}
	else if (damage > 0)
	{
		static_cast<Sprite*>(assailant)->getOwner()->removeScore(assailant->getAttackPower());
	}

	Piece::iAttackedYou(assailant, damage, caller);
}
