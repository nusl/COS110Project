#ifndef PIECE_H
#define PIECE_H

#include "Map.h"

class Map;
struct Coord;
class Piece
{
	public:
		Piece
		(unsigned int inMaxLife
		,unsigned int inCurrentLife
		,unsigned int inMoveCount
		,unsigned int inRange
		,unsigned int inAttackPower
		,double inHitChance
		,double inCritChance
		,double inDodgeChance
		,double inParryChance
		,char inState
		,char inType
		,bool inMoveOnto):

		 maxLife(inMaxLife)
		,currentLife(inCurrentLife)
		,moveCount(inMoveCount)
		,range(inRange)
		,attackPower(inAttackPower)
		,hitChance(inHitChance)
		,critChance(inCritChance)
		,dodgeChance(inDodgeChance)
		,parryChance(inParryChance)
		,state(inState)
		,type(inType)
		,moveOnto(inMoveOnto)
		{}
		

		~Piece(){};
		
		//we can change this if needed. I know Frank, just bare with me bro... We can make it a member with 2 line changes.
		virtual void action(const Coord& coord, Map* caller) = 0;
		
		const char getState(){return state;}
		const char getType(){return type;}
		const bool canBeMovedOnto() const{return moveOnto;}//can I be moved onto by another piece? Like a waypoint and an empty piece.

	protected:
	//TODO: Some of these functions can be moved to a lower level in the hierarchy. But later...
	
		void setState(const char& inState){state = inState;}

		const unsigned int getMaxLife(){return maxLife;}
		const unsigned int getCurrentLife(){return currentLife;}
		const unsigned int getMoveCount(){return moveCount;}
		const unsigned int getRange(){return range;}
		const unsigned int getAttackPower(){return attackPower;}

		const double getHitChance(){return hitChance;}
		const double getCritChance(){return critChance;}
		const double getDodgeChance(){return dodgeChance;}
		const double getParryChance(){return parryChance;}
		
	private:
	
		unsigned int maxLife;
		unsigned int currentLife;
		unsigned int moveCount;
		unsigned int range;
		unsigned int attackPower;

		double hitChance;
		double critChance;
		double dodgeChance;
		double parryChance;

		char state;
		char type;
		
		bool moveOnto;
};

#endif
