#include "Assassin.h"

bool Assassin::attack(Map& caller)
{
    return true;
}

bool Assassin::rotate(Map& caller)
{
    setState(getDirectionFromIntent());
    return false;
}

bool Assassin::move(Map& caller)
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

bool Assassin::pass(Map& caller)
{
    return true;
}
