#ifndef SPRITE_H
#define SPRITE_H

#include "MovablePiece.h"

// Forward declare class Player to avoid circular inheritance and hence
// absolute compiler suicide.
class Player;

namespace Direction
{
        const char left = '{';
        const char right = '}';
        const char up = '^';
        const char down = 'v';
        const char invalid = '!';
}

struct Intent
{
	public:
		Intent() : intent(' '), value(0)
		{

		}

		Intent(const char& it, const int& val = 1) : intent(it), value(val)
		{
		}

		Intent& operator=(const Intent& other)
		{
			this->intent = other.intent;
			this->value = other.value;
			return *this;
		}

		const char& getIntent() const
		{
			return intent;
		}

		const unsigned& getValue() const
		{
			return value;
		}

	private:
		char intent;
		unsigned value;
};

class Sprite : public MovablePiece
{
	public:
		Sprite
		(unsigned int inMaxLife
		,unsigned int inCurrentLife
		,unsigned int inMoveCount
		,unsigned int inRange
		,unsigned int inAttackPower
		,unsigned int inMoveRange
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
		,inMoveRange
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
		,turnsSinceLastRegen(0)
		{}

		Intent getIntent() const;
        const char getDirectionFromIntent() const;

		//Recieves a command, validates if it exists(return bool), sets the intent. Afterward, action() is called. 
		bool command(const Intent& inIntent);

        // Returns true if a turn-consuming action was performed, otherwise returns false
        bool attemptAction(Map& caller, const int& attempt);

        bool isAttackIntent() const;
        bool isRotateIntent() const;
        bool isMoveIntent() const;
        bool isPassIntent() const;

        // Returns true if attack successful, as any valid attack counts as a turn
		virtual bool attack(Map& caller);

        // Always return false, as no move is made when rotating
		virtual bool rotate(Map& caller);

        // Returns true if move was made, as a move counts as a turn
		virtual bool move(Map& caller);

        // Always returns true, as pass counts as a turn
		virtual bool pass(Map& caller);
        
		virtual void reset();//Specialised from Piece implementation

		virtual void knockBack(Map* caller);

		Player* getOwner();

		virtual void decreaseLife(const unsigned& howMuch, Map* caller);

		void regenerateLife();

    private:

		void setOwner(Player* who);

		double regenRate;
		unsigned int regenCounter;
		unsigned int turnsSinceLastRegen;
		Intent intent;
		Player* owner;

        static const std::string commandIntentList;
        static const std::string attackIntentList;
        static const std::string passIntentList;

	friend class Player;
};

#endif
