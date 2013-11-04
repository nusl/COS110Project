#include "Mage.h"
#include "Barrier.h"

#include <iostream>
bool Mage::performSpecial(Map& caller)
{
	Coord placementLocation = caller.getCoordOf(this);

	int myX = (getState() == Direction::right) ? 1 : (getState() == Direction::left ? -1 : 0);
	int myY = (getState() == Direction::down) ? 1 : (getState() == Direction::up ? -1 : 0);
	//((intent.getValue() > getAttackRange()) ? getAttackRange() : intent.getValue())

	placementLocation.x += myX;
	placementLocation.y += myY;
	
	if(!caller.inBoundary(placementLocation))
	{
		std::cout << "Tried to make a barrier that is not even inside the map!..Wow" << std::endl;
		return false;
	}
	
	Barrier* barrier = new Barrier();
	if(!caller.placePieceAt(barrier, placementLocation))
	{
		std::cout << "Rookie move: tried to make a barrier on top of another piece" << std::endl;
		return false;
	}
	barrier->build(caller.getCoordOf(this), placementLocation, &caller);

	return true;
}
