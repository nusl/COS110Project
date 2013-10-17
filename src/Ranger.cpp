#include "Ranger.h"

bool Ranger::attack(Map& caller)
{
    return true;
}

bool Ranger::rotate(Map& caller)
{
    setState(getDirectionFromIntent());
    return false;
}

bool Ranger::move(Map& caller)
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

bool Ranger::pass(Map& caller)
{
    return true;
}
