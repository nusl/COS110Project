#ifndef PIECE_H
#define PIECE_H

#include "RNG.h"
#include "Map.h"

class Map;
struct Coord;
class Piece: public RNG
{
	public:
		Piece
		(unsigned int inMaxLife
		,unsigned int inCurrentLife
		,unsigned int inMoveCount
		,unsigned int inAttackRange
		,unsigned int inAttackPower
		,unsigned int inMoveRange
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
		,attackRange(inAttackRange)
		,moveRange(inMoveRange)
		,attackPower(inAttackPower)
		,hitChance(inHitChance)
		,critChance(inCritChance)
		,dodgeChance(inDodgeChance)
		,parryChance(inParryChance)
		,state(inState)
		,type(inType)
		,moveOnto(inMoveOnto)
		{}

		virtual ~Piece(){}

		virtual void reset();

		virtual void action(const Coord& coord, Map* caller) = 0;

		virtual Piece* const whoAttackedMe()const{return myAssailant;}

		/** Used for interaction between pieces
		 *
         *  @param handle to the assailant
         *  @param Damage to be dealt to the victim. It is passed by non-const reference so that the victim can modify the damage
         *	depending on its abilities, such as dodge, parry, or simply invulnerability.
         *  @param handle to the assailant
         *  @return void
         */
		virtual void iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller);

		virtual unsigned int totalAttackDamage();

		/** Dodge and Parry chance are the defense modifiers. */
		virtual void defend(Piece* const assailant, unsigned int& damage, Map* caller);

		virtual const char getState() const {return state;}
        const char getType() const {return type;}
		const bool canBeMovedOnto() const{return moveOnto;}//can I be moved onto by another piece? Like a waypoint and an empty piece.

        const unsigned int getMaxLife() const {return maxLife;}
        const unsigned int getCurrentLife() const {return currentLife;}
        const unsigned int getMoveCount() const {return moveCount;}
        const unsigned int getAttackRange() const {return attackRange;}
        const unsigned int getMoveRange() const {return moveRange;}
        const unsigned int getAttackPower() const {return attackPower;}

        const double getHitChance() const {return hitChance;}
		virtual const double getCritChance() const {return critChance;}
        const double getDodgeChance() const {return dodgeChance;}
        const double getParryChance() const {return parryChance;}

		virtual void increaseLife(const unsigned& howMuch);
		virtual void decreaseLife(const unsigned& howMuch, Map* caller);

    protected:
		void setState(const char& inState){state = inState;}
		void setAssailant(Piece* who);
		
		void setAttackPower(const unsigned int& in){attackPower = in;}

		void setHitChance(const unsigned int& in)	{hitChance = in;}
		void setCritChance(const unsigned int& in)	{critChance = in;}
		void setDodgeChance(const unsigned int& in)	{dodgeChance = in;}
		void setParryChance(const unsigned int& in)	{parryChance = in;}

	private:
		Piece* myAssailant;

		unsigned int maxLife;
		unsigned int currentLife;
		unsigned int moveCount;
		unsigned int attackRange;
		unsigned int moveRange;
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
