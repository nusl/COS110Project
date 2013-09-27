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
		/** Used for interaction between pieces
		 *
		 *
         *  @param handle to the assailant
         *  @param Damage to be dealt to the victim. It is passed by non-const reference so that the victim can modify the damage
         *	depending on its abilities, such as dodge, parry, or simply invulnerability.
         *  @param handle to the assailant
         *  @return void
         */
		virtual void iAttackedYou(Piece* assailant, unsigned int& damage, Map* caller){myAssailant = assailant;}
		
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
