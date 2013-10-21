#ifndef IMMOVABLE_PEICE_H
#define IMMOVABLE_PEICE_H

#include "Piece.h"

class ImmovablePiece : public Piece
{
	public:
		ImmovablePiece
		(unsigned int inMaxLife
		,unsigned int inCurrentLife
		//,unsigned int inMoveCount
		//,unsigned int inRange
		//,unsigned int inAttackPower
		//,double inHitChance
		//,double inCritChance
		//,double inDodgeChance
		//,double inParryChance
		,char inState
		,char inType
		,bool inMoveOnto):
		Piece
		(inMaxLife
		,inCurrentLife
		,0//inMoveCount
		,0//inRange
		,0//inAttackPower
		,0 //inMoveRange
		,0//inHitChance
		,0//inCritChance
		,0//inDodgeChance
		,0//inParryChance
		,inState
		,inType
		,inMoveOnto){}
		
};

#endif
