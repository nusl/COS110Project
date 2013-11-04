#ifndef SLENDER_MAN_H
#define SLENDER_MAN_H

#include "Creep.h"

class SlenderMan : public Creep
{
	public:
		SlenderMan ():
		Creep
		(999999//inMaxLife
		,999999//inCurrentLife
		,1//inMoveCount
		,1//inRange
		,999999//inAttackPower
		,1//inHitChance
		,1//inCritChance
		,1//inDodgeChance
		,1//inParryChance
		,'.'//inState
		,'I'//inType
		)
		,stalkTurns(5)
		,turnCounter(0)
		,stalkCount(0)
		,shouldHunt(false)
		{
		}

		virtual void action(const Coord &coord, Map *caller);

		virtual void iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller);

	private:
		unsigned stalkTurns;
		unsigned turnCounter;
		unsigned stalkCount;
		// Used to add some suspense to it. Slender man shows himself, then moves forward on the next turn.
		// Creates an effect of slow pondering, then moving. Might be creepy.
		bool shouldHunt;
};

#endif
