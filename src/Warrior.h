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
		,1 //inMoveRange
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

		virtual void action(const Coord& coord, Map* caller){}

        virtual bool attack(Map& caller);
        virtual bool rotate(Map& caller);
        virtual bool move(Map& caller);
        virtual bool pass(Map& caller);
};

#endif
