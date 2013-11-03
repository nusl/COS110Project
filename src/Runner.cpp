#include "Runner.h"
#include <cstdlib>
#include <cassert>

//RAII construct that temporarily negates a value until it goes out of scope
struct Negate
{
	Negate(bool& inboolean, const bool& value):boolean(&inboolean)
	{
		if(inboolean == value)
			return;
		*boolean = !(*boolean);//negate it
	}
	~Negate(){*boolean = !(*boolean);}//negate it back
	bool* boolean;
};

void Runner::iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
{
	Piece::iAttackedYou(assailant, damage, caller);
	wasAttackedLastTurn = true;	
}

void Runner::moveBack(Coord& coord, Map* caller)
{
	//Relinquish range boundary enforcement temporarily. Otherwise all moves will be illegal since we are already out of range
	Negate scoped(canGoOutOfRange,true);
	
	const int columnOffset	= offsetHistory.back().offsetY;
	const int rowOffset		= offsetHistory.back().offsetX;
	
	const int myMoveRange = static_cast<int>(getMoveRange());
	
	const bool isAboveRange = (columnOffset > myMoveRange);
	const bool isBelowRange = ((columnOffset < 0) && (::abs(columnOffset) > myMoveRange));
	const bool isRightRange	= (rowOffset > myMoveRange);
	const bool isLeftRange	= ((rowOffset < 0) && (::abs(rowOffset) > myMoveRange));
	
	if(isAboveRange)
	{
		moveDown(coord, caller);
		return;
	}
	if(isBelowRange)
	{
		moveUp(coord, caller);
		return;
	}
	if(isRightRange)
	{
		moveLeft(coord, caller);
		return;
	}
	if(isLeftRange)
	{
		moveRight(coord, caller);
		return;
	}
	return;
}

void Runner::runAway(const Coord& victim, Coord& me, Map* caller)
{
	//There is a 3 liner to make this shorter, but this is slightly clearer
	Offset direction(me, victim);
	const bool isAbove = (direction.offsetY < 0);
	const bool isBelow = (direction.offsetY > 0);
	const bool isLeft = (direction.offsetX < 0);
	const bool isRight = (direction.offsetX > 0);
	assert(((isAbove||isBelow||isLeft||isRight),"we should be running away from something"));
	
	bool (Runner::*execMove)(Coord&, Map*);
	if(isAbove)
		execMove = &Runner::moveDown;
	else
	if(isBelow)
		execMove = &Runner::moveUp;
	else
	if(isLeft)
		execMove = &Runner::moveRight;
	else
	if(isRight)
		execMove = &Runner::moveLeft;
	
	//try to make the move twice	
	for(size_t i = 0; i!=2; ++i)
		(this->*execMove)(me, caller);
}

void Runner::action(const Coord& coord, Map* caller)
{
	const unsigned int damageToSelf = 5;

	/*
	In the event that the Runner creep ends up being further than range 1 of its initial
	position, it will first attempt to return to its initial position before resuming its random
	movement but attacking/running away will take precedence if the sprite attacks again.
	*/
	Coord location(coord);
	if(!inComfortZone && !wasAttackedLastTurn)
		moveBack(location, caller);

	if(Piece::whoAttackedMe())//do I have an assailant?
	{	
		Coord blip(0,0);
		if(crossRadar(coord, blip, getAttackRange(), caller))//Is the assailant close enough
		{
			unsigned int totalDamage = totalAttackDamage();
			caller->getHandleAt(blip)->iAttackedYou(this, totalDamage, caller);//Attack him
			if(critChanceDoubled)
				setHitChance(getHitChance()/2.0);
			
			/*If no damage is dealt after attacking, the Runner creep will run away from the
			sprite by two blocks in panic, dealing 5 damage to itself but doubles its critical hit
			chance for its next attack. The critical hit chance will return to normal after the
			next attack regardless of whether that attack deals damage or not.
			*/
			if(totalDamage == 0)
			{
				decreaseLife(damageToSelf, caller);
				runAway(blip, location, caller);
				setHitChance(getHitChance()*2.0);
				critChanceDoubled = true;
			}
			setAssailant(0);
			wasAttackedLastTurn = false;
		}
	}
	else
		Creep::wander(location, caller);
}
