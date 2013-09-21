#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "MeleeSprite.h"
#include "AmmoUnit.h"

class Assassin : public MeleeSprite, public AmmoUnit
{
	public:
		Assassin
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
		MeleeSprite
		(250//inMaxLife
		,250//inCurrentLife
		,1//inMoveCount
		//,1//inRange
		,20//inAttackPower
		,0.95//inHitChance
		,0.05//inCritChance
		,0.025//inDodgeChance
		,0.25//inParryChance
		,'v'//inState
		,'a'//inType
		//,false//inMoveOnto
		,0.10//inRegenRate
		,10//inRegenCounter
		),
		AmmoUnit
		(25//inMaxAmmo
		,25//inCurrentAmmo
		,20//inPowerIncrease
		)
		{}
};

#endif
