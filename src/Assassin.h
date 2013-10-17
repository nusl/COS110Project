#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "MeleeSprite.h"
#include "AmmoUnit.h"

#include <iostream>

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
        (150//inMaxLife
        ,150//inCurrentLife
        ,2//inMoveCount
		//,1//inRange
        ,5   //inAttackPower
		,1 //inMoveRange
		,0.95//inHitChance
        ,0.20//inCritChance
        ,0.50//inDodgeChance
        ,0.20//inParryChance
		,'v'//inState
		,'a'//inType
		//,false//inMoveOnto
		,0.10//inRegenRate
        ,5//inRegenCounter
		),
		AmmoUnit
		(25//inMaxAmmo
		,25//inCurrentAmmo
		,20//inPowerIncrease
		)
		{}

		virtual void action(const Coord& coord, Map* caller){}

        virtual bool attack(Map& caller);
        virtual bool rotate(Map& caller);
        virtual bool move(Map& caller);
        virtual bool pass(Map& caller);

};

#endif
