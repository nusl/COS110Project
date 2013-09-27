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

		myAssailant(0)
		,maxLife(inMaxLife)
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
		
        virtual ~Piece(){};


		virtual void action(const Coord& coord, Map* caller) = 0;
		virtual Piece* whoAttackedMe(){return myAssailant;}
		virtual void iAttackedYou(Piece* assailant, Map* caller){myAssailant = assailant;}
		
        const char getState() const {return state;}
        const char getType() const {return type;}
		const bool canBeMovedOnto() const{return moveOnto;}//can I be moved onto by another piece? Like a waypoint and an empty piece.

        const unsigned int getMaxLife() const {return maxLife;}
        const unsigned int getCurrentLife() const {return currentLife;}
        const unsigned int getMoveCount() const {return moveCount;}
        const unsigned int getRange() const {return range;}
        const unsigned int getAttackPower() const {return attackPower;}

        const double getHitChance() const {return hitChance;}
        const double getCritChance() const {return critChance;}
        const double getDodgeChance() const {return dodgeChance;}
        const double getParryChance() const {return parryChance;}

    protected:

		void setState(const char& inState){state = inState;}

	private:
		Piece* myAssailant;

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
