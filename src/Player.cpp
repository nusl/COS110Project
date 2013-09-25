#include "Player.h"

#include "InvalidParameterException.h"

Player::Player(Sprite* s)
{
    sprite = s;
}

Player::~Player()
{
    if (sprite)
    {
        delete sprite;
        sprite = 0;
    }
}

void Player::addScore(const int& value)
{
    if (value < 0)
    {
        throw InvalidParameterException("Attempted to add a score value of less than zero.");
    }

    score += value;
}

void Player::removeScore(const int& value)
{
    if (value < 0)
    {
        throw InvalidParameterException("Attempted to remove a score value of less than zero.");
    }

    score -= value;
}

const int& Player::getScore() const
{
    return score;
}

bool Player::executeCommand(Map &caller, const char& c, const int& attempt)
{
    if (!(sprite->command(c)))
    {
        return false;
    }

    return sprite->attemptAction(caller, attempt);
}

const Sprite* Player::getSpriteHandle() const
{
    return sprite;
}

bool Player::placeSprite(Map& map) const
{
    return map.placePieceAt(sprite, map.getCoordWaypointStart());
}

bool Player::moveSprite(Map& map, const Coord& coord) const
{
    return map.move(map.getSpriteCoord(), coord);
}
