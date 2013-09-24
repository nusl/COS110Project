#include "Player.h"

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
        return;
    }
}

void Player::removeScore(const int& value)
{

}

const int& Player::getScore() const
{
    return score;
}
