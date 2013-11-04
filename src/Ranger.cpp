#include "Ranger.h"

#include "Hammer.h"
#include "Hunter.h"
#include "Runner.h"
#include "Sleeper.h"

#include <typeinfo>
#include <iostream>

bool Ranger::performSpecial(Map& caller)
{	
	if(specialActionCounter == 0)
	{
		std::cout << "Your special ability has been depleted" << std::endl;
		return false;
	}
	
	if(!whoAttackedMe())
	{
		std::cout << "Nothing has attacked you" << std::endl;
		return false;
	}
	if(!caller.exists(whoAttackedMe()))
	{
		std::cout << "Your enemy has been destroyed. There is nothing to make a pet of" << std::endl;
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
		std::cout << "How do you expect to put a pet there?" << std::endl;
		return false;
	}
	
	Piece* pet(0);
	if(typeid(*whoAttackedMe()) == typeid(Hammer))
		pet = new Hammer();
	else
	if(typeid(*whoAttackedMe()) == typeid(Hunter))
		pet = new Hunter();
	else
	if(typeid(*whoAttackedMe()) == typeid(Runner))
		pet = new Runner();
	else
	if(typeid(*whoAttackedMe()) == typeid(Sleeper))
		pet = new Sleeper();
	else
	{
		std::cout << "You can't make a pet of whatever attacked you O.o" << std::endl;
		return false;
	}
	pet->setAssailant(whoAttackedMe());//Fetch

	if(!caller.placePieceAtForce(pet, placementLocation))
	{
		std::cout << "Poor pet:( You can't put it there, you cruel person!" << std::endl;
		return false;
	}
	
	--specialActionCounter;
	std::cout << "You have " << specialActionCounter << " shots left of your special ability." << std::endl;
	return true;
}

void Ranger::iAttackedYou(Piece * const assailant, unsigned int &damage, Map *caller)
{
	critTurnCounter = 1;
	Sprite::iAttackedYou(assailant, damage, caller);
}

void Ranger::tick()
{
	++critTurnCounter;
	if (critTurnCounter == 3)
	{
		critTurnCounter = 0;
	}
}

const double Ranger::getCritChance() const
{
	switch (critTurnCounter)
	{
		case 1:
			return Piece::getCritChance() * 2;
			break;
		case 2:
			return Piece::getCritChance() / 2;
			break;
		case 3:
			return Piece::getCritChance();
			break;
		default:
			return Piece::getCritChance();
			break;
	}
	return Piece::getCritChance();
}

bool Ranger::attack(Map &caller)
{
	if (hasAmmo())
	{
		bang(1);
	} else
	{
		setAttackPower(15);
	}
	return Sprite::attack(caller);
}

void Ranger::reset()
{
	reload();
	specialActionCounter = 1;
	Sprite::reset();
}
