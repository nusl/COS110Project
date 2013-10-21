#include "Ranger.h"


void Ranger::iAttackedYou(Piece * const assailant, unsigned int &damage, Map *caller)
{
	critTurnCounter = 1;
	Piece::iAttackedYou(assailant, damage, caller);
}

void Ranger::tick()
{
	++critTurnCounter;
	if (critTurnCounter == 3)
	{
		critTurnCounter = 0;
	}
}

const double Ranger::getCritChance() const
{
	switch (critTurnCounter)
	{
		case 1:
			return Piece::getCritChance() * 2;
			break;
		case 2:
			return Piece::getCritChance() / 2;
			break;
		case 3:
			return Piece::getCritChance();
			break;
		default:
			return Piece::getCritChance();
			break;
	}
	return Piece::getCritChance();
}
