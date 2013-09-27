#include "Warrior.h"

bool Warrior::attack(Map& caller)
{
    return true;
}

bool Warrior::rotate(Map& caller)
{
    setState(getDirectionFromIntent());
    return false;
}

bool Warrior::move(Map& caller)
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

bool Warrior::pass(Map& caller)
{
    return true;
}
