#ifndef BOULDER_H
#define BOULDER_H

#include "ImmovablePiece.h"

class Boulder : public ImmovablePiece
{
	public:
		Boulder
		(//unsigned int inMaxLife
		//,unsigned int inCurrentLife
		//,unsigned int inMoveCount
		//,unsigned int inRange
		//,unsigned int inAttackPower
		//,double inHitChance
		//,double inCritChance
		//,double inDodgeChance
		//,double inParryChance
		//,char inState
		//,char inType
		//,bool inMoveOnto
		):
		ImmovablePiece
		(5//inMaxLife
		,5//inCurrentLife
		//,0//inMoveCount
		//,0//inRange
		//,0//inAttackPower
		//,0//inHitChance
		//,0//inCritChance
		//,0//inDodgeChance
		//,0//inParryChance
		,'B'//inState
		,'B'//inType
		,false//inMoveOnto
		)
		{}
		virtual void action(const Coord& coord, Map* caller){};

		virtual void iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
		{
			Piece::iAttackedYou(assailant, damage, caller);
			const size_t knockBackDistance = 2;
			assailant->knockBack(assailant, knockBackDistance);
		}
};

#endif
