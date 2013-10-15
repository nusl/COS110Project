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
		,moveRange(1)//FIXME: All units have a movement range of 1, but this should probably propagate up to the constructor
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

		virtual void reset()
		{
			currentLife = maxLife;
			myAssailant = 0;
			//NOTE: State?
		}

		virtual void action(const Coord& coord, Map* caller) = 0;

		virtual Piece* const whoAttackedMe()const{return myAssailant;}		
		/** Used for interaction between pieces
		 *
		 *
         *  @param handle to the assailant
         *  @param Damage to be dealt to the victim. It is passed by non-const reference so that the victim can modify the damage
         *	depending on its abilities, such as dodge, parry, or simply invulnerability.
         *  @param handle to the assailant
         *  @return void
         */
		virtual void iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
		{
			defend(assailant, damage, caller);//Modifies the damage done.
			currentLife -= damage;
			myAssailant = assailant;
		}
		
		virtual unsigned int totalAttackDamage()
		{
			unsigned int damage = getAttackPower();
			
			unsigned int rng = static_cast<unsigned int>(this->random());//FIXME: RNG generates ints as per specification. The result is compared with uints.
			
		    if(rng <= getHitChance())
		        damage = 0;
		    if(rng <= getCritChance())
		    	damage *= 2;
		    
		    return damage;
		}

        //TODO: Move this to .cpp. Its getting crowded in here :p
		/** Dodge and Parry chance are the defense modifiers*/
		virtual void defend(Piece* const assailant, unsigned int& damage, Map* caller)
		{
		    unsigned int rng = static_cast<unsigned int>(this->random());//FIXME: RNG generates ints as per specification. The result is compared with uints.
		    if(rng == 0)
		        return;//disregard 0 value
		        
		    if(rng <= getDodgeChance())
		        damage = 0;

		    if(rng <= getParryChance())
    		    damage /= 2;
		}
		
        const char getState() const {return state;}
        const char getType() const {return type;}
		const bool canBeMovedOnto() const{return moveOnto;}//can I be moved onto by another piece? Like a waypoint and an empty piece.

        const unsigned int getMaxLife() const {return maxLife;}
        const unsigned int getCurrentLife() const {return currentLife;}
        const unsigned int getMoveCount() const {return moveCount;}
        const unsigned int getAttackRange() const {return attackRange;}
        const unsigned int getMoveRange() const {return moveRange;}
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
