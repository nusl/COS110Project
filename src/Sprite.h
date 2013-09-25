#ifndef SPRITE_H
#define SPRITE_H

#include "MovablePiece.h"

namespace Direction
{
        const char left = '{';
        const char right = '}';
        const char up = '^';
        const char down = 'v';
        const char invalid = '!';
}

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

        char getIntent() const;
        const char getDirectionFromIntent() const;

		//Recieves a command, validates if it exists(return bool), sets the intent. Afterward, action() is called. 
        bool command(const char& in);

        virtual void attack(Map& caller){};
        virtual void rotate(Map& caller){};
        virtual void move(Map& caller){};
        virtual void pass(Map& caller){};

        bool attemptAction(Map& caller, const int& attempt);

        bool isAttackIntent() const;
        bool isRotateIntent() const;
        bool isMoveIntent() const;
        bool isPassIntent() const;

	private:
		double regenRate;
		unsigned int regenCounter;
        char intent;

        static const std::string commandIntentList;
        static const std::string attackIntentList;
        static const std::string passIntentList;
};

#endif
