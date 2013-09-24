#ifndef CREEP_H
#define CREEP_H

#include "MovablePiece.h"

struct Offset
{
    /** Offset struct default constructor. */
    Offset()
    {
        x = 0;
        y = 0;
    }

    /** Offset struct constructor.
     *
     *  @param inX a constant integer reference
     *  @param inY a constant integer reference
     */
    Offset(const int& inX, const int& inY)
    {
        x = inX;
        y = inY;
    }

    int x;
    int y;
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
		{}

    private:
        Offset offset;
};

#endif
