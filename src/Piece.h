#ifndef PIECE_H
#define PIECE_H

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
		,char inType):

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
		,type(inType){}
		

		virtual ~Piece() = 0;
		
		void action(const int& x, const int& y);
		
		const char getState(){return state;}
		const char getType(){return type;}
		
	protected:
	
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
};

#endif
