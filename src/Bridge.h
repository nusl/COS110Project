#ifndef BRIDGE_H
#define BRIDGE_H

#include "ImmovablePiece.h"

class Bridge: public ImmovablePiece
{
	public:
		Bridge
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
		(10//inMaxLife, zero because wall has no hp and takes no damage.
		,10//inCurrentLife
		//,0//inMoveCount
		//,0//inRange
		//,0//inAttackPower
		//,0//inHitChance
		//,0//inCritChance
		//,0//inDodgeChance
		//,0//inParryChance
		,'#'//inState
		,'#'//inType
		,true//inMoveOnto	//NOTE: This is the important part.
		)
		{}
	virtual void action(const Coord& coord, Map* caller){}
};

#endif
