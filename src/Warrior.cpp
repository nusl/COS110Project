#include "Warrior.h"
#include "Bridge.h"

#include <iostream>
bool Warrior::performSpecial(Map& caller)
{
	Coord placementLocation = caller.getCoordOf(this);

	int myX = (getState() == Direction::right) ? 1 : (getState() == Direction::left ? -1 : 0);
	int myY = (getState() == Direction::down) ? 1 : (getState() == Direction::up ? -1 : 0);
	//((intent.getValue() > getAttackRange()) ? getAttackRange() : intent.getValue())

	placementLocation.x += myX;
	placementLocation.y += myY;
	
	if(!caller.inBoundary(placementLocation))
	{
		std::cout << "Explain to me how you are going to build a bridge to nothing?" << std::endl;
		return false;
	}

	if(!caller.placePieceAtForce(new Bridge(), placementLocation))
	{
		std::cout << "Rookie move: tried to make a barrier on top of another piece" << std::endl;
		return false;
	}
	return true;
}
