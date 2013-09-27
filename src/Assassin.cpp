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

bool Assassin::pass(Map& caller)
{
    return true;
}
