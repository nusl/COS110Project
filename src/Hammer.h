#ifndef HAMMER_H
#define HAMMER_H

#include <iostream>
#include "Creep.h"

class Hammer : public Creep
{
	public:
		Hammer
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
		(100//inMaxLife
		,100//inCurrentLife
		,1//inMoveCount
		,2//inRange
		,40//inAttackPower
		,0.5//inHitChance
		,0.05//inCritChance
		,0.025//inDodgeChance
		,0.05//inParryChance
		,'H'//inState
		,'H'//inType
		//,false//inMoveOnto
		)
		{}

		virtual void action(const Coord& coord, Map* caller)
		{
			Coord location(coord);
/*
			moveDown(location,caller);
			moveRight(location,caller);
			moveUp(location,caller);
			moveLeft(location,caller);
*/
			moveLeft(location,caller);
			if(!moveLeft(location,caller))
				std::cout << "cannot move left" << std::endl;
			else
				std::cout << "moved left" << std::endl;

		};
};

#endif
