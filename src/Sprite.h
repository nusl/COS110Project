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

        // Returns true if a turn-consuming action was performed, otherwise returns false
        bool attemptAction(Map& caller, const int& attempt);

        bool isAttackIntent() const;
        bool isRotateIntent() const;
        bool isMoveIntent() const;
        bool isPassIntent() const;

        // Returns true if attack successful, as any valid attack counts as a turn
        virtual bool attack(Map& caller) = 0;

        // Always return false, as no move is made when rotating
        virtual bool rotate(Map& caller) = 0;

        // Returns true if move was made, as a move counts as a turn
        virtual bool move(Map& caller) = 0;

        // Always returns true, as pass counts as a turn
        virtual bool pass(Map& caller) = 0;
        
        virtual void reset();//Specialised from Piece implementation

    private:

		double regenRate;
		unsigned int regenCounter;
        char intent;

        static const std::string commandIntentList;
        static const std::string attackIntentList;
        static const std::string passIntentList;
};

#endif
