#include "Warrior.h"

#include "EmptySpace.h"

#include <iostream>
#include <typeinfo>

bool Warrior::attack(Map& caller)
{
	//std::cout << "attacking" << std::endl;
	Coord c = caller.getCoordOf(this);

	int myX = (getState() == Direction::right) ? 1 : (getState() == Direction::left ? -1 : 0);
	int myY = (getState() == Direction::down) ? 1 : (getState() == Direction::up ? -1 : 0);
	//std::cout << myX << " $ " << myY << std::endl;
	//std::cout << c.x << " % " << c.y << std::endl;
	for (unsigned i = 0; i < getAttackRange(); ++i)
	{
		c.x += myX;
		c.y += myY;
		//std::cout << c.x << " - " << c.y << std::endl;
		//std::cout << typeid(*caller.getHandleAt(c)).name() << std::endl;
		if (!caller.inBoundary(c))
		{
			break;
		}
		if (typeid(EmptySpace) != typeid(*caller.getHandleAt(c)))
		{
			//std::cout << "did attack on : " << typeid(*caller.getHandleAt(c)).name() << std::endl;
			// Attack stuff
			unsigned int totalDamage = totalAttackDamage();
			//std::cout << "Before attack: " << caller.getHandleAt(c)->getCurrentLife() << std::endl;
			caller.getHandleAt(c)->iAttackedYou(this, totalDamage, &caller);
			//std::cout << "After attack: " << caller.getHandleAt(c)->getCurrentLife() << std::endl;
			return true;
		}
	}

	return false;
}

bool Warrior::rotate(Map& caller)
{
    setState(getDirectionFromIntent());
    return false;
}

bool Warrior::move(Map& caller)
{
    Coord c = caller.getSpriteCoord();

	int moveDistance = (getIntent().getValue() <= getMoveRange() && getIntent().getValue() > 0) ? getIntent().getValue() : 1;

	switch (getState())
	{
		case Direction::up:
			c.y -= moveDistance;
			break;
		case Direction::down:
			c.y += moveDistance;
			break;
		case Direction::left:
			c.x -= moveDistance;
			break;
		case Direction::right:
			c.x += moveDistance;
			break;
	}

	return caller.move(caller.getSpriteCoord(), c);
}

bool Warrior::pass(Map& caller)
{
	std::cout << "Player has passed on their turn.\n";
    return true;
}
