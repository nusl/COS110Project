#ifndef HUNTER_H
#define HUNTER_H

#include "Creep.h"

class Hunter : public Creep
{
	public:
		Hunter
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
		(25//inMaxLife
		,25//inCurrentLife
		,1//inMoveCount
		,1//inRange
		,10//inAttackPower
		,0.75//inHitChance
		,0.10//inCritChance
		,0.10//inDodgeChance
		,0.20//inParryChance
		,'U'//inState
		,'U'//inType
		//,false//inMoveOnto
		)
		,wasAttackedLastTurn(false)
		{}
		
		virtual void iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
		{
			wasAttackedLastTurn = true;
			/*
			 It is not immune to damage while stealthed and can take damage if the sprite manages to attack it.
			 When a Hunter creep takes damage while in stealth, it will become visible again and takes double damage 
			 AFTER hit chance and critical chance has been calculated
			*/
			if(getState() == '.')//Stealthed
			{
				damage = damage*2;//takes double damage AFTER hit chance and critical chance has been calculated from the sprite
				setState('U');//it will become visible again
			}
			
			Piece::iAttackedYou(assailant, damage, caller);
			
		}

		virtual void action(const Coord& coord, Map* caller)
		{
			//Hunter always needs a victim
			if(!whoAttackedMe())
				setAssailant(caller->getHandleAt(caller->getSpriteCoord()));


			const unsigned int stealthRange = 2;
			
			Coord blip(0,0);

			//and it will never choose to stealth if it can attack instead.
			if(crossRadar(coord, blip, getAttackRange(), caller))
			{
				unsigned int totalDamage = totalAttackDamage();//FIXME: It seems the double thing is not true //Either it must attack a player – doing double damage AFTER hit chance and critical chance has been calculated - and lose its stealth
				
				caller->getHandleAt(blip)->iAttackedYou(this, totalDamage, caller);//Attack him
				setState(getType());//'U'
			}
			else
			{
				//A Hunter creep will become stealthed – visually disappearing from the map - when a sprite comes within a range of 2 of it
				if(crossRadar(coord, blip, stealthRange, caller) && !wasAttackedLastTurn)//A Hunter creep can only stealth if it went undamaged in the player’s last turn
					setState('.');//I am stealth now
				// and will remain in its position while stealthed
				if(getState() != '.')//Not stealthed
				{
					Coord location(coord);
					huntDown(location,caller);
				}
			}
			wasAttackedLastTurn = false;
		};
		private:
			bool wasAttackedLastTurn;
};

#endif
