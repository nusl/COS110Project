#ifndef CREEP_H
#define CREEP_H

#include <deque>
#include "MovablePiece.h"


/** Offset struct constructor.
 *	FIXME: Traditional x y coordinates will not suffice since it would be prone to overflow. This is due to the fact that coordinates are unsigned.
 *  @param inX a constant integer reference
 *  @param inY a constant integer reference
 */
struct Offset
{
	public:
		Offset():offsetY(0), offsetX(0){}

		Offset(const Coord& from, const Coord& to)
		{
			offsetY = static_cast<int>(to.y) - static_cast<int>(from.y);
			offsetX = static_cast<int>(to.x) - static_cast<int>(from.y);
		}
		int offsetY;
		int offsetX;
		
		Offset operator+(const Offset& rhs)
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
		,inHitChance
		,inCritChance
		,inDodgeChance
		,inParryChance
		,inState
		,inType
		//,false//inMoveOnto
		)
		{
			offsetHistory.push_back(Offset());
		}
		
	bool move(const Coord& from, const Coord& to, Map* caller);
		
	private:
		std::deque<Offset> offsetHistory;
};

#endif
