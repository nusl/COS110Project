#ifndef RANGER_H
#define RANGER_H

#include "RangedSprite.h"
#include "AmmoUnit.h"

class Ranger : public RangedSprite, public AmmoUnit
{
	public:
		Ranger
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
		(200//inMaxLife
		,200//inCurrentLife
		,1//inMoveCount
		//,2//inRange
		,15//inAttackPower
		,1 //inMoveRange
		,0.75//inHitChance
		,0.15//inCritChance
		,0.15//inDodgeChance
		,0.05//inParryChance
		,'v'//inState
		,'m'//inTypes
		//,false//inMoveOnto
		,0.07//inRegenRate
		,3//inRegenCounter
		),
		AmmoUnit
		(30//inMaxAmmo
		,30//inCurrentAmmo
		,10//inpPowerIncrease
		)
		,critTurnCounter(0)
		{}

		virtual void action(const Coord& coord, Map* caller){}

		virtual void iAttackedYou(Piece * const assailant, unsigned int &damage, Map *caller);

		virtual void tick();

		virtual const double getCritChance() const;

	private:
		unsigned critTurnCounter;
};
#endif
