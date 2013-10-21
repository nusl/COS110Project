#ifndef MAGE_H
#define MAGE_H

#include "RangedSprite.h"

class Mage : public RangedSprite
{
	public:
		Mage
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
		RangedSprite
		(100//inMaxLife
		,100//inCurrentLife
		,1//inMoveCount
		//,2//inRange
		,30//inAttackPower
		,3 //inMoveRange
		,0.80//inHitChance
		,0.35//inCritChance
		,0.05//inDodgeChance
		,0.0//inParryChance
		,'v'//inState
		,'m'//inType
		//,false//inMoveOnto
		,0.15//inRegenRate
		,7//inRegenCounter
		)
		{}

		virtual void action(const Coord& coord, Map* caller){}
};

#endif
