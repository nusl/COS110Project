#include "Sprite.h"

#include "InvalidParameterException.h"

const std::string Sprite::commandIntentList = "WASDKP";
const std::string Sprite::attackIntentList = "K";
const std::string Sprite::passIntentList = "P";

char Sprite::getIntent() const
{
    return intent;
}

const char Sprite::getDirectionFromIntent() const
{
    switch (toupper(intent))
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

bool Sprite::command(const char& in)
{
    bool valid = commandIntentList.find(toupper(in), 0) != std::string::npos;

    if (!valid)
    {
        return valid;
    }

    intent = in;

    return valid; //return true if command exists
}

bool Sprite::attemptAction(Map& caller, const int& attempt)
{
    if (attempt == 0)
    {
        throw InvalidParameterException("Sprite::customAction() - attempt parameter of value zero received.");
    }

    if ((getMoveCount() - attempt) < 0)
    {
        throw InvalidParameterException("Sprite::customAction() - sprite action attempts exceeded number of possible moves.");
    }

    if (isRotateIntent())
        rotate(caller);
    if (isAttackIntent())
        attack(caller);
    if (isMoveIntent())
        move(caller);

    return ((getMoveCount() - attempt) == 0);
}

bool Sprite::isAttackIntent() const
{
    // You cannot attack in the direction you are not looking in
    if (getDirectionFromIntent() != getState())
    {
        return false;
    }

    return attackIntentList.find(toupper(intent), 0) != std::string::npos;
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
    return passIntentList.find(toupper(intent), 0) != std::string::npos;
}
