#ifndef SLEEPER_H
#define SLEEPER_H

#include "Creep.h"

class Sleeper : public Creep
{
	public:
		Sleeper
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
		(40//inMaxLife
		,40//inCurrentLife
		,1//inMoveCount
		,1//inRange
		,5//inAttackPower
		,0.75//inHitChance
		,0.10//inCritChance
		,0.10//inDodgeChance
		,0.20//inParryChance
		,'Z'//inState
		,'Z'//inType
		//,false//inMoveOnto
		)
		{}

		virtual void action(const Coord& coord, Map* caller)
		{
			if(whoAttackedMe())
			{
				Coord blip(0,0);
				Coord location(coord);
				
				if(crossRadar(coord, blip, getAttackRange(), caller))
				{
					unsigned int totalDamage = totalAttackDamage();
					caller->getHandleAt(blip)->iAttackedYou(this, totalDamage, caller);//Attack him
				}
				else
					huntDown(location, caller);
			}
		}
};

#endif
