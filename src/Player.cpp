#include "Player.h"

#include "InvalidParameterException.h"
#include "PlayerQuitException.h"

const std::string Player::commands = "Q";

Player::Player(Sprite* s) : score(0)
{
    sprite = s;
}

Player::~Player()
{
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

bool Player::executeCommand(Map &caller, const Intent& intent, const unsigned& attempt)
{
	if (command(intent.getIntent()))
    {
		switch (toupper(intent.getIntent()))
        {
            case 'Q':
                quit();
                break;
        }
    }

	if (!(sprite->command(intent)))
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

bool Player::command(const char& c) const
{
    return commands.find(toupper(c), 0) != std::string::npos;
}

void Player::quit() const
{
    throw PlayerQuitException("Player quit");
}
