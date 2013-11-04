#ifndef SLEEPER_H
#define SLEEPER_H

#include "Creep.h"

#include <iostream>

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

		virtual void iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
		{	
//		std::cout << "sleeper damage: " << damage << std::endl;
			if(!whoAttackedMe())//holds null if it has no assialant. Therefore it is sleeping
			{//take full damage if sleeping
				decreaseLife(damage, caller);
				setAssailant(assailant);
			}
			else
				Piece::iAttackedYou(assailant, damage, caller);
			/*
			After each time the Sleeper creep takes damage, including the time it wakes up:
			Its attack power doubles; and
			Its hit chance, critical hit chance, dodge chance and parry chance all increase by 5%
			The percentages can’t increase more than 100% but the attack power has no upper bound!
			*/
			setAttackPower(getAttackPower()*2);

			if(getHitChance() != 1.0)
				setHitChance(getHitChance()+0.05);

			if(getCritChance() != 1.0)
				setCritChance(getCritChance()+0.05);

			if(getDodgeChance() != 1.0)
				setDodgeChance(getDodgeChance()+0.05);
			
			if(getParryChance() != 1.0)
				setParryChance(getParryChance()+0.05);
		}

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
					/*
					After each time the Sleeper attacks, regardless of whether damage is dealt or not:
					Its attack power halves; and 
					Its hit chance, critical hit chance, dodge chance and parry chance all decrease by 5%.
					All of the stats for a Sleeper can never drop below their original values.
					*/
					setAttackPower(getAttackPower()/2);
					//FIXME: These values should actually be encoded as modifiers. No time though.
					if(getHitChance() != 0.75)
						setHitChance(getHitChance()-0.05);

					if(getCritChance() != 0.10)
						setCritChance(getCritChance()-0.05);

					if(getDodgeChance() != 0.10)
						setDodgeChance(getDodgeChance()-0.05);
		
					if(getParryChance() != 0.20)
						setParryChance(getParryChance()-0.05);					
				}
				else
					huntDown(location, caller);
			}
		}
};

#endif
