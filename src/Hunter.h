#ifndef HUNTER_H
#define HUNTER_H

#include "Creep.h"

class Hunter : public Creep
{
	public:
		Hunter
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
		Creep
		(25//inMaxLife
		,25//inCurrentLife
		,1//inMoveCount
		,1//inRange
		,10//inAttackPower
		,0.75//inHitChance
		,0.10//inCritChance
		,0.10//inDodgeChance
		,0.20//inParryChance
		,'U'//inState
		,'U'//inType
		//,false//inMoveOnto
		)
		{}
		virtual void action(const Coord& coord, Map* caller){};
};

#endif
