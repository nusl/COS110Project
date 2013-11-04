#include "Warrior.h"
#include "Bridge.h"

#include <iostream>
bool Warrior::performSpecial(Map& caller)
{
	if(specialActionCounter == 0)
	{
		std::cout << "Your special ability has been depleted" << std::endl;
		return false;
	}
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

	caller.placePieceAtForce(new Bridge(), placementLocation);
	
	--specialActionCounter;
	std::cout << "You have " << specialActionCounter << " shots left of your special ability." << std::endl;
	return true;
}

void Warrior::reset()
{
	specialActionCounter = 5;
	Sprite::reset();
}
