#include "Sprite.h"

#include "InvalidParameterException.h"

#include "PlayerResetException.h"
#include "PlayerEndException.h"
#include "PlayerDiedException.h"
#include "Waypoint.h"
#include "Creep.h"
#include "Player.h"
#include "EmptySpace.h"

#include <iostream>
#include <typeinfo>
#include <cmath>

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

		checkWaypoint(&caller);
    }
    else if (isPassIntent())
    {
		success = pass(caller);
    }

	return success;
}

bool Sprite::isAttackIntent() const
{
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

bool Sprite::attack(Map &caller)
{
	Coord c = caller.getCoordOf(this);

	int myX = (getState() == Direction::right) ? 1 : (getState() == Direction::left ? -1 : 0);
	int myY = (getState() == Direction::down) ? 1 : (getState() == Direction::up ? -1 : 0);

	for (unsigned i = 0; i < ((intent.getValue() > getAttackRange()) ? getAttackRange() : intent.getValue()); ++i)
	{
		c.x += myX;
		c.y += myY;

		if (!caller.inBoundary(c))
		{
			std::cout << "Player tries to attack nothing and wastes a turn." << std::endl;
			return true;
		}
		if (typeid(EmptySpace) != typeid(*caller.getHandleAt(c)))
		{
			unsigned int totalDamage = totalAttackDamage();
			caller.getHandleAt(c)->iAttackedYou(this, totalDamage, &caller);
			return true;
		}
	}

	// Attempted attacking nothing, which wastes a turn. Return true.
	std::cout << "Player tries to attack nothing and wastes a turn." << std::endl;
	return true;
}

bool Sprite::rotate(Map &caller)
{
	setState(getDirectionFromIntent());
	return false;
}

bool Sprite::move(Map &caller)
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

bool Sprite::pass(Map &caller)
{
	std::cout << "Player has passed on their turn.\n";
	return true;
}

void Sprite::reset()
{
	Piece::reset();
	setState('v');
	shouldRegen = false;
	turnsSinceLastRegen = 0;
}

void Sprite::knockBack(Map* caller)
{
	const unsigned KNOCKBACK_RANGE = 2;
	const unsigned KNOCKBACK_BASE_SPRITE_DAMAGE = 10;
	const unsigned KNOCKBACK_BASE_CREEP_DAMAGE = 20;
	const unsigned KNOCKBACK_BASE_SCORE = 10;

	Coord c = caller->getCoordOf(this);

	int myX = (getState() == Direction::right) ? -1 : (getState() == Direction::left ? 1 : 0);
	int myY = (getState() == Direction::down) ? -1 : (getState() == Direction::up ? 1 : 0);

	for (unsigned i = 1; i <= KNOCKBACK_RANGE; ++i)
	{
		c.x += myX;
		c.y += myY;
		if (!caller->inBoundary(c))
		{
			caller->getHandleAt(caller->getSpriteCoord())->decreaseLife(KNOCKBACK_BASE_SPRITE_DAMAGE / i, caller);
			static_cast<Sprite*>(caller->getHandleAt(caller->getSpriteCoord()))->getOwner()->removeScore(KNOCKBACK_BASE_SCORE / i);
			return;
		}

		if (!caller->move(caller->getCoordOf(this), c))
		{
			caller->getHandleAt(caller->getSpriteCoord())->decreaseLife(KNOCKBACK_BASE_SPRITE_DAMAGE / i, caller);

			static_cast<Sprite*>(caller->getHandleAt(caller->getSpriteCoord()))->getOwner()->removeScore(KNOCKBACK_BASE_SCORE / i);

			// Is the piece that blocked us a creep?
			if (dynamic_cast<Creep*>(caller->getHandleAt(c)))
			{
				unsigned dmg = KNOCKBACK_BASE_CREEP_DAMAGE / i;
				caller->getHandleAt(c)->iAttackedYou(caller->getHandleAt(caller->getSpriteCoord()), dmg, caller);
			}
			return;
		}
	}

	checkWaypoint(caller);
}

Player* Sprite::getOwner()
{
	return owner;
}

void Sprite::decreaseLife(const unsigned &howMuch, Map *caller)
{
	if (howMuch >= getCurrentLife())
	{
		throw PlayerDiedException("Player was killed by taking too much damage.");
	}

	// Since the player has lost life, we can now start regenerating life.
	shouldRegen = true;
	Piece::decreaseLife(howMuch, caller);
}

void Sprite::regenerateLife()
{
	if (shouldRegen)
	{
		if (turnsSinceLastRegen == (regenCounter - 1))
		{
			unsigned regenAmount = floor(getMaxLife() * regenRate);
			if (regenAmount > (getMaxLife() - getCurrentLife()))
			{
				//std::cout << "Regenning: " << getMaxLife() - getCurrentLife() << ", Curr:" << getCurrentLife() << ", Max:" << getMaxLife() << std::endl;
				increaseLife(getMaxLife() - getCurrentLife());
			} else
			{
				increaseLife(regenAmount);
			}
			turnsSinceLastRegen = 0;
		} else
		{
			++turnsSinceLastRegen;
		}
	}
}

void Sprite::defend(Piece * const assailant, unsigned int &damage, Map *caller)
{
	std::cout << "Player defends against a total damage amount of " << damage << "." << std::cout;
	Piece::defend(assailant, damage, caller);
}

void Sprite::checkWaypoint(Map *caller)
{
	const Piece* waypoint = caller->getHandleBelowOfType(caller->getSpriteCoord(), typeid(Waypoint).name());

	if(waypoint)
	{
		if(waypoint->getState() == 'S')
			throw PlayerResetException("Player moved over the Start waypoint.");
		if(waypoint->getState() == 'E')
			throw PlayerEndException("Player moved over the End waypoint.");
	}
}

void Sprite::setOwner(Player *who)
{
	owner = who;
}

