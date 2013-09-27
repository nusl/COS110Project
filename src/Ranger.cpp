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

    return caller.move(caller.getSpriteCoord(), c);
}

bool Ranger::pass(Map& caller)
{
    return true;
}
