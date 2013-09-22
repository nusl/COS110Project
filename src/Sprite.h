#ifndef SPRITE_H
#define SPRITE_H

#include "MovablePiece.h"

class Sprite : public MovablePiece
{
	public:
		Sprite
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
		//,bool inMoveOnto
		,double inRegenRate
		,double inRegenCounter
		):
		MovablePiece
		(inMaxLife
		,inCurrentLife
		,inMoveCount
		,inRange
		,inAttackPower
		,inHitChance
		,inCritChance
		,inDodgeChance
		,inParryChance
		,inState
		,inType
		//,false//inMoveOnto
		)
		,regenRate(inRegenRate)
		,regenCounter(inRegenCounter)
		{}
		
		//Recieves a command, validates if it exists(return bool), sets the intent. Afterward, action() is called. 
		bool command(const char& in)
		{
			intent = in;
			return true;//return true if command exists
		}
	private:
		double regenRate;
		unsigned int regenCounter;
		char intent;
};

#endif
