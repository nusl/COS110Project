#ifndef WARRIOR_H
#define WARRIOR_H

#include "MeleeSprite.h"

class Warrior : public MeleeSprite
{
	public:
		Warrior
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
		,'w'//inType
		//,false//inMoveOnto
		,0.10//inRegenRate
		,10//inRegenCounter
		)
		{}
		virtual void action(const int& x, const int& y, Map* caller){};
};

#endif
