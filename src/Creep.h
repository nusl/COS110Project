#ifndef CREEP_H
#define CREEP_H

#include <deque>
#include "MovablePiece.h"


/** Offset struct.
 *	FIXME: Traditional x y coordinates will not suffice since it would be prone to overflow.
 *	This is due to the fact that coordinates are unsigned.
 *	Even though this would only occur on a map that has a few billion pieces, it can still happen.
 *  @param coordinate from
 *  @param coordinate to
 */
struct Offset
{
	public:
		Offset():offsetY(0), offsetX(0){}

		Offset(const Coord& from, const Coord& to)
		{
			offsetY = static_cast<int>(to.y) - static_cast<int>(from.y);
			offsetX = static_cast<int>(to.x) - static_cast<int>(from.x);
		}
		int offsetY;
		int offsetX;
		
		Offset operator+(const Offset& rhs) const
		{
			Offset temp;
			temp.offsetY = this->offsetY + rhs.offsetY;
			temp.offsetX = this->offsetX + rhs.offsetX;
			return temp;
		}
		
		bool operator==(const Offset& rhs)
		{
			if(this->offsetY != rhs.offsetY) return false;
			if(this->offsetX != rhs.offsetX) return false;
			return true;
		}
};

class Creep : public MovablePiece
{
	public:
		Creep
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
		):
		MovablePiece
		(inMaxLife
		,inCurrentLife
		,inMoveCount
		,inRange
		,inAttackPower
		,1 //inMoveRange - FIXME: May need to propogate this through the Creep derivative constructors.
		,inHitChance
		,inCritChance
		,inDodgeChance
		,inParryChance
		,inState
		,inType
		//,false//inMoveOnto
		)
		,canGoOutOfRange(false)
		{
			offsetHistory.push_back(Offset());
		}

		virtual void reset();

	protected:

		bool huntDown	(Coord& from, Map* caller);
		void wander		(Coord& from, Map* caller);
		void forget();
		bool crossRadar		(const Coord& from, Coord& blip, const size_t& range, Map* caller) const;
		bool squareRadar	(const Coord& from, Coord& blip, const size_t& range, Map* caller) const;
		
		bool moveLeft	(Coord& from, Map* caller);
		bool moveRight	(Coord& from, Map* caller);
		bool moveUp		(Coord& from, Map* caller);
		bool moveDown	(Coord& from, Map* caller);
		
		std::deque<Offset> offsetHistory;
		bool canGoOutOfRange;
	private:
		bool move(const Coord& from, const Coord& to, Map* caller);
};

#endif
