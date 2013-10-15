#ifndef CRITTER_H
#define CRITTER_H

#include "Creep.h"

class Critter : public Creep
{
	public:
		Critter
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
		(5//inMaxLife
		,5//inCurrentLife
		,0//inMoveCount
		,1//inRange
		,10//inAttackPower
		,1.0//inHitChance
		,0.5//inCritChance
		,0.1//inDodgeChance
		,0.2//inParryChance
		,'C'//inState
		,'C'//inType
		//,false//inMoveOnto
		)
		{}
		virtual void action(const Coord& coord, Map* caller)
		{
			//Have I been attacked?
			if(!Piece::whoAttackedMe())
				return;

			Coord blip(0,0);
			//Is my attacker in range?
			if(radar(coord, blip, getAttackRange(), caller))
			{
				unsigned int totalDamage = totalAttackDamage();
				caller->getHandleAt(blip)->Piece::iAttackedYou(this, totalDamage, caller);//Attack him
			}
		};
};

#endif
