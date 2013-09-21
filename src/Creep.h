#ifndef CREEP_H
#define CREEP_H

#include "MovablePiece.h"

class Creep : public MovablePiece
{
	public:
		Creep
		(unsigned int inMaxLife
		,unsigned int inCurrentLife
		,unsigned int inMoveCount
		,unsigned int inRange
		,unsigned int inAttackPower
		,double inHitChance
		,double inCritChance
		,double inDodgeChance
		,double inParryChance
		,char inState
		,char inType
		//,bool inMoveOnto
		):
		MovablePiece
		(inMaxLife
		,inCurrentLife
		,inMoveCount
		,inRange
		,inAttackPower
		,inHitChance
		,inCritChance
		,inDodgeChance
		,inParryChance
		,inState
		,inType
		//,false//inMoveOnto
		)
		{}
};

#endif
