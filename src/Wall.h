#ifndef WALL_H
#define WALL_H

#include <climits>
#include "ImmovablePiece.h"

class Wall : public ImmovablePiece
{
	public:
		Wall
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
		(INT_MAX//inMaxLife
		,INT_MAX//inCurrentLife
		//,0//inMoveCount
		//,0//inRange
		//,0//inAttackPower
		//,0//inHitChance
		//,0//inCritChance
		//,0//inDodgeChance
		//,0//inParryChance
		,'/'//inState
		,'/'//inType
		,false//inMoveOnto
		)
		{}
		virtual void action(const Coord& coord, Map* caller){};
};

#endif
