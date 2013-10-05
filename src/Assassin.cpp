#include "Assassin.h"

#include "PlayerResetException.h"
#include "PlayerEndException.h"
#include "Waypoint.h"

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

    switch (getState())
    {
        case Direction::up:
            c.y -= 1;
            break;
        case Direction::down:
            c.y += 1;
            break;
        case Direction::left:
            c.x -= 1;
            break;
        case Direction::right:
            c.x += 1;
            break;
    }

    bool success = caller.move(caller.getSpriteCoord(), c);

	if (success)
	{
		const Piece* waypoint = caller.getHandleBelowOfType(c, typeid(Waypoint).name());

		if(waypoint)
		{
			if(waypoint->getState() == 'S')
		  		throw PlayerResetException("Player moved over the Start waypoint.");
			if(waypoint->getState() == 'E')
		  		throw PlayerEndException("Player moved over the End waypoint.");
	  	}	
  	}

	return success;
}

bool Assassin::pass(Map& caller)
{
    return true;
}
