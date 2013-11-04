#ifndef BARRIER_H
#define BARRIER_H

#include "ImmovablePiece.h"

class Barrier: public ImmovablePiece
{
	public:
		Barrier
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
		(60//inMaxLife, zero because wall has no hp and takes no damage.
		,60//inCurrentLife
		//,0//inMoveCount
		//,0//inRange
		//,0//inAttackPower
		//,0//inHitChance
		//,0//inCritChance
		//,0//inDodgeChance
		//,0//inParryChance
		,'|'//inState
		,'|'//inType
		,false//inMoveOnto
		)
		{}
	virtual void action(const Coord& coord, Map* caller){}
	void build(const Coord& myMaster, const Coord& myLocation, Map* caller);
};

#endif
