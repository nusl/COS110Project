#include "Sprite.h"

#include "InvalidParameterException.h"

#include "PlayerResetException.h"
#include "PlayerEndException.h"
#include "Waypoint.h"

const std::string Sprite::commandIntentList = "WASDKP";
const std::string Sprite::attackIntentList = "K";
const std::string Sprite::passIntentList = "P";

Intent Sprite::getIntent() const
{
    return intent;
}

const char Sprite::getDirectionFromIntent() const
{
	switch (toupper(intent.getIntent()))
    {
        case 'W':
            return Direction::up;
            break;
        case 'A':
            return Direction::left;
            break;
        case 'S':
            return Direction::down;
            break;
        case 'D':
            return Direction::right;
            break;
        default:
            return Direction::invalid;
            break;
    }
    return Direction::invalid;
}

bool Sprite::command(const Intent& inIntent)
{
	bool valid = commandIntentList.find(toupper(inIntent.getIntent()), 0) != std::string::npos;

    if (!valid)
    {
        return valid;
    }

	intent = inIntent;

    return valid; //return true if command exists
}

bool Sprite::attemptAction(Map& caller, const int& attempt)
{
    if (attempt == 0)
    {
        throw InvalidParameterException("Sprite::customAction() - attempt parameter of value zero received.");
    }

    // Cannot make more moves than possible move count
    if ((getMoveCount() - attempt) < 0)//FIXME: Subtracting an int from an unsigned int can never be less than 0. The result is unsigned.
    {
        return false;
    }

	bool success = false;

    // If you're going to mess with this if-stack please expect weird behavior.
    // Removing the 'else's will cause undefined behavior because the isMoveIntent()
    // function is dependant on the current state of the Sprite, which would be changed by
    // the rotate() function, thus allowing the piece to both rotate and move in one turn.
    // Rather leave it like this, mmkay?
    if (isRotateIntent())
    {
		success = rotate(caller);
    }
    else if (isAttackIntent())
    {
		success = attack(caller);
    }
    else if (isMoveIntent())
    {
		success = move(caller);

		const Piece* waypoint = caller.getHandleBelowOfType(caller.getSpriteCoord(), typeid(Waypoint).name());

		if(waypoint)
		{
			if(waypoint->getState() == 'S')
				throw PlayerResetException("Player moved over the Start waypoint.");
			if(waypoint->getState() == 'E')
				throw PlayerEndException("Player moved over the End waypoint.");
		}
    }
    else if (isPassIntent())
    {
		success = pass(caller);
    }

	return success;
}

bool Sprite::isAttackIntent() const
{
    // You cannot attack in the direction you are not looking in
    if (getDirectionFromIntent() != getState())
    {
        return false;
    }

	return attackIntentList.find(toupper(intent.getIntent()), 0) != std::string::npos;
}

bool Sprite::isRotateIntent() const
{
    if (getDirectionFromIntent() == Direction::invalid)
    {
        return false;
    }

    if (getDirectionFromIntent() != getState())
    {
        return true;
    }

    return false;
}

bool Sprite::isMoveIntent() const
{
    if (getDirectionFromIntent() == Direction::invalid)
    {
        return false;
    }

    if (getDirectionFromIntent() == getState())
    {
        return true;
    }

    return false;
}

bool Sprite::isPassIntent() const
{
	return passIntentList.find(toupper(intent.getIntent()), 0) != std::string::npos;
}

void Sprite::reset()
{
	Piece::reset();
	setState('v');
}
