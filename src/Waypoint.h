#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "ImmovablePiece.h"

class Waypoint : public ImmovablePiece
{
	public:
		Waypoint
		(//unsigned int inMaxLife
		//,unsigned int inCurrentLife
		//,unsigned int inMoveCount
		//,unsigned int inRange
		//,unsigned int inAttackPower
		//,double inHitChance
		//,double inCritChance
		//,double inDodgeChance
		//,double inParryChance
		 char inState
		//,char inType
		//,bool inMoveOnto
		):
		ImmovablePiece
		(1//inMaxLife
		,1//inCurrentLife
		//,0//inMoveCount
		//,0//inRange
		//,0//inAttackPower
		//,0//inHitChance
		//,0//inCritChance
		//,0//inDodgeChance
		//,0//inParryChance
		,inState
		,'W'//inType
		,true//inMoveOnto
		)
		{}
		virtual void action(const Coord& coord, Map* caller){};
};

#endif
