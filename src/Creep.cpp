#include <algorithm>
#include <cassert>
#include "Creep.h"

#include <iostream>
/*
void wander(Coord& from, Map* caller)
{

	//get initial move from the random number generator
	//assign the move a value 0-3 where, up=0, down=1, left=2, right=3
	const unsigned int numPossibleMoves = 4;
	for(unsigned int i = 0; i!=numPossibleMoves; ++i)
	{
		if((i%initialMove) == 0)
			if(moveUp(from, caller))
				return;

		if((i%initialMove) == 1)
			if(moveDown(from, caller))
				return;

		if((i%initialMove) == 2)
			if(moveLeft(from, caller))
				return;
			
		if((i%initialMove) == 3)
			if(moveRight(from, caller))
				return;
	}
}
*/

//TODO: Check that creep does not wander too far from origin
bool Creep::move(const Coord& from, const Coord& to, Map* caller)
{
	Offset newOffset(from, to);
	newOffset = newOffset + offsetHistory.back();
	std::cout << "newOffset: y:" << newOffset.offsetY << " x:" << newOffset.offsetX << std::endl;

	//is the location we want to go in history?
	if(find(offsetHistory.begin(), offsetHistory.end(), newOffset) != offsetHistory.end())
		return false;//cannot move there, it is in history
	for(std::deque<Offset>::iterator it = offsetHistory.begin(); it!=offsetHistory.end(); ++it)
		std::cout << "Move offset: y:" << it->offsetY << " x:" << it->offsetX << std::endl;
	offsetHistory.push_back(newOffset);	
	if(offsetHistory.size() == 4)//The last 3 positions are remembered
		offsetHistory.pop_front();
	assert(offsetHistory.size() <= 3);//sanity check

	return caller->move(from, to);
}


//TODO:There could be a clean way to remove some of this duplicate code
bool Creep::moveLeft(Coord& coord, Map* caller)
{
	const Coord from(coord);
	const Coord to((from-Coord(0,1)));
	if(!move(from, to, caller))
		return false;
	coord = to;//update the current location
	return true;
}
bool Creep::moveRight(Coord& coord, Map* caller)
{
	const Coord from(coord);
	const Coord to((from+Coord(0,1)));
	if(!move(from, to, caller))
		return false;
	coord = to;//update the current location
	return true;
}
bool Creep::moveUp(Coord& coord, Map* caller)
{
	const Coord from(coord);
	const Coord to((from-Coord(1,0)));
	if(!move(from, to, caller))
		return false;
	coord = to;//update the current location
	return true;
}
bool Creep::moveDown(Coord& coord, Map* caller)
{
	const Coord from(coord);
	const Coord to((from+Coord(1,0)));
	if(!move(from, to, caller))
		return false;
	coord = to;//update the current location
	return true;
}
