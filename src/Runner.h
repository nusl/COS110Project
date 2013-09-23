#ifndef RUNNER_H
#define RUNNER_H

#include "Creep.h"

class Runner : public Creep
{
	public:
		Runner
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
		(30//inMaxLife
		,30//inCurrentLife
		,1//inMoveCount
		,1//inRange
		,10//inAttackPower
		,0.85//inHitChance
		,0.075//inCritChance
		,0.05//inDodgeChance
		,0.10//inParryChance
		,'R'//inState
		,'R'//inType
		//,false//inMoveOnto
		)
		{}
		virtual void action(const Coord& coord, Map* caller){};
};

#endif
