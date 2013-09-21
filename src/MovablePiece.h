#ifndef MOVABLE_PIECE_H
#define MOVABLE_PIECE_H

#include "Piece.h"

class MovablePiece : public Piece
{
	public:
		MovablePiece
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
		Piece
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
		,false//inMoveOnto
		)
		{}
};

#endif
