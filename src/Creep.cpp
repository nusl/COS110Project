#include <algorithm>
#include <cassert>
#include <cmath>
#include "Creep.h"
#include "Waypoint.h"
#include <typeinfo>

#include <iostream>

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

//This is the most butt ugly function in the code-base
bool Creep::huntDown (Coord& from, Map* caller)
{
	//Nothing to pursue
	if(!whoAttackedMe())
		return false;

	//Relinquish range boundary enforcement temporarily
	Negate scoped(canGoOutOfRange,true);

	Coord victim( caller->getCoordOf(whoAttackedMe()) );
	Offset distanceFromMe(from, victim);
	assert(distanceFromMe.offsetX!=0 || distanceFromMe.offsetY!=0);//the offset cannot be zero
	
	//Makes it clearer
	const bool isAbove = (distanceFromMe.offsetY < 0);
	const bool isBelow = (distanceFromMe.offsetY > 0);
	const bool isLeft = (distanceFromMe.offsetX < 0);
	const bool isRight = (distanceFromMe.offsetX > 0);
	
	const bool isSameColumn	= !(isLeft || isRight);
	const bool isSameRow	= !(isAbove|| isBelow);

	if(isAbove)
	{
		if(moveUp(from, caller))
			return true;
			
		if(isLeft || isSameColumn)
		{
			if(moveLeft(from, caller))
				return true;
			if(moveRight(from, caller))
				return true;
			if(moveDown(from, caller))
				return true;
			return false;
		}
		else
		{
			if(isRight)
			{
				if(moveRight(from, caller))
					return true;
				if(moveLeft(from, caller))
					return true;
				if(moveDown(from, caller))
					return true;
				return false;
			}
		}
	}
	else
	if(isBelow)
	{
		if(moveDown(from, caller))
			return true;
			
		if(isLeft || isSameColumn)
		{
			if(moveLeft(from, caller))
				return true;
			if(moveRight(from, caller))
				return true;
			if(moveUp(from, caller))
				return true;
			return false;
		}
		else
		{
			if(isRight)
			{
				if(moveRight(from, caller))
					return true;
				if(moveLeft(from, caller))
					return true;
				if(moveUp(from, caller))
					return true;
				return false;
			}
		}
	}
	else
	if(isLeft)
	{
		if(moveLeft(from, caller))
			return true;
			
		if(isAbove || isSameRow)
		{
			if(moveUp(from, caller))
				return true;
			if(moveDown(from, caller))
				return true;
			if(moveRight(from, caller))
				return true;
			return false;
		}
		else
		{
			if(isBelow)
			{
				if(moveDown(from, caller))
					return true;
				if(moveUp(from, caller))
					return true;
				if(moveRight(from, caller))
					return true;
				return false;
			}
		}
	}
	else
	if(isRight)
	{
		if(moveRight(from, caller))
			return true;
			
		if(isAbove || isSameRow)
		{
			if(moveUp(from, caller))
				return true;
			if(moveDown(from, caller))
				return true;
			if(moveLeft(from, caller))
				return true;
			return false;
		}
		else
		{
			if(isBelow)
			{
				if(moveDown(from, caller))
					return true;
				if(moveUp(from, caller))
					return true;
				if(moveLeft(from, caller))
					return true;
				return false;
			}
		}
	}
	return false;
}

void Creep::wander(Coord& from, Map* caller)
{

	//get initial move from the random number generator
	unsigned int rndval = random();
	if(rndval == 0)//discard 0 because the rng is broken
		return;
	--rndval;//make it 0-99 instead of 1-100

	//assign the move a value 0-3 where, up=0, down=1, left=2, right=3	
	const unsigned int initialMove = (rndval/25);

std::cout << "Moveid: " << initialMove << std::endl;
	/*Depending on the initial move, the order of the move tries will be the following:
	
		up=0	down=1	left=2	right=3
		0		1		2		3
		1		2		3		0
		2		3		0		1
		3		0		1		2
	*/
	const unsigned int numPossibleMoves = 4;
	for(unsigned int i = 0; i!=numPossibleMoves; ++i)
	{
		if(((initialMove+i)%numPossibleMoves) == 0)
			if(moveUp(from, caller))
				return;

		if(((initialMove+i)%numPossibleMoves) == 1)
			if(moveDown(from, caller))
				return;

		if(((initialMove+i)%numPossibleMoves) == 2)
			if(moveLeft(from, caller))
				return;
			
		if(((initialMove+i)%numPossibleMoves) == 3)
			if(moveRight(from, caller))
				return;
	}
	
	//pg17: The creep must forget its history if it is stuck.
	forget();
}

void Creep::forget()
{
	Offset lastPosition(offsetHistory.back());
	offsetHistory.clear();
	offsetHistory.push_back(lastPosition);
}

/*
Checks if a sprite is in range, if it is, return a blip by reference.
* * * * *
* * + * *
* + P + *
* * + * *
* * * * *
*/
bool Creep::crossRadar(const Coord& from, Coord& blip, const size_t& range, Map* caller) const
{
	Coord victim(0,0);
	if(whoAttackedMe())
		victim = caller->getCoordOf(whoAttackedMe());
	else
		victim = caller->getSpriteCoord();

	Offset distanceFromMe(from, victim);
	assert(distanceFromMe.offsetX!=0 || distanceFromMe.offsetY!=0);//the offset cannot be zero

	//Is it in range, if not return false?
	// NOTE: Frank- Added (unsigned) here as a warning was raised for comparing uint(abs()) with sint(range) below.
	if(!(distanceFromMe.offsetY == 0) ^ (distanceFromMe.offsetX == 0))
		return false;
	if(((unsigned)::abs(distanceFromMe.offsetY) > range)
	|| ((unsigned)::abs(distanceFromMe.offsetX) > range))
		return false;

	blip = victim;
	return true;
}

/*
Checks if a sprite is in range, if it is, return a blip by reference.
* * * * *
* + + + *
* + P + *
* + + + *
* * * * *
*/
bool Creep::squareRadar(const Coord& from, Coord& blip, const size_t& range, Map* caller) const
{
	Coord victim(0,0);
	if(whoAttackedMe())
		victim = caller->getCoordOf(whoAttackedMe());
	else
		victim = caller->getSpriteCoord();

	Offset distanceFromMe(from, victim);
	assert(distanceFromMe.offsetX!=0 || distanceFromMe.offsetY!=0);//the offset cannot be zero

	//Is it in range, if not return false?
	// NOTE: Frank- Added (unsigned) here as a warning was raised for comparing uint(abs()) with sint(range) below.
	if(((unsigned)::abs(distanceFromMe.offsetY) > range)
	|| ((unsigned)::abs(distanceFromMe.offsetX) > range))
		return false;

	blip = victim;
	return true;
}

//TODO: Check that creep does not wander too far from origin
bool Creep::move(const Coord& from, const Coord& to, Map* caller)
{
	Offset newOffset(from, to);
	newOffset = newOffset + offsetHistory.back();
	//std::cout << "newOffset: y:" << newOffset.offsetY << " x:" << newOffset.offsetX << std::endl;
	//std::cout << "newCoord: y:" << to.y << " x:" << to.x << std::endl;

	//is the location we want to go in history?
	if(find(offsetHistory.begin(), offsetHistory.end(), newOffset) != offsetHistory.end())
		return false;//cannot move there, it is in history

	if(!canGoOutOfRange)
	{
		//Stay within range
		// NOTE: Frank- Added (unsigned) here as a warning was raised for comparing uint(abs()) with sint(range) below.
		if(((unsigned)::abs(newOffset.offsetY) > this->getMoveRange()) || ((unsigned)::abs(newOffset.offsetX) > this->getMoveRange()))
			return false;
	}

	if(!caller->Map::inBoundary(to))
		return false;
	//Avoid waypoints
	if(typeid(*caller->Map::getHandleAt(to)) == typeid(Waypoint))
		return false;

	//Evaluate map based movement rules and move
	if(!caller->Map::move(from, to))
		return false;

	//std::cout << "MovedOffset: y:" << newOffset.offsetY << " x:" << newOffset.offsetX << std::endl;

//	for(std::deque<Offset>::iterator it = offsetHistory.begin(); it!=offsetHistory.end(); ++it)
	//std::cout << "Move offset: y:" << it->offsetY << " x:" << it->offsetX << std::endl;
	offsetHistory.push_back(newOffset);	
	if(offsetHistory.size() == 4)//The last 3 positions are remembered
		offsetHistory.pop_front();
	assert(offsetHistory.size() <= 3);//sanity check
	
	return true;
}

//TODO:There could be a clean way to remove some of this duplicate code
bool Creep::moveLeft(Coord& coord, Map* caller)
{
	std::cout << typeid(*this).name() << ": Tried to move left"<< std::endl;
	const Coord from(coord);
	const Coord to((from-Coord(0,1)));
	if(!move(from, to, caller))
		return false;
	coord = to;//update the current location
	std::cout << typeid(*this).name() << ": Moved left"<< std::endl;
	return true;
}

bool Creep::moveRight(Coord& coord, Map* caller)
{
	std::cout << typeid(*this).name() << ": Tried to move right"<< std::endl;

	const Coord from(coord);
	const Coord to((from+Coord(0,1)));
	if(!move(from, to, caller))
		return false;
	coord = to;//update the current location

	std::cout << typeid(*this).name() << ": Moved right"<< std::endl;
	return true;
}

bool Creep::moveUp(Coord& coord, Map* caller)
{
	std::cout << typeid(*this).name() << ": Tried to move up"<< std::endl;
	const Coord from(coord);
	const Coord to((from-Coord(1,0)));
	if(!move(from, to, caller))
		return false;
	coord = to;//update the current location
	std::cout << typeid(*this).name() << ": Moved up"<< std::endl;
	return true;
}

bool Creep::moveDown(Coord& coord, Map* caller)
{
	std::cout << typeid(*this).name() << ": Tried to move down"<< std::endl;
	const Coord from(coord);
	const Coord to((from+Coord(1,0)));
	if(!move(from, to, caller))
		return false;
	coord = to;//update the current location
	std::cout << typeid(*this).name() << ": Moved down"<< std::endl;
	return true;
}
