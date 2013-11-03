#include "Hammer.h"

#include "Sprite.h"
#include <iostream>

void Hammer::action(const Coord& coord, Map* caller)
{
	Coord location(coord);

	if (whoAttackedMe())
	{
		Coord blip(coord);
		//std::cout << "Hammer will hunt down" << std::endl;
		if (crossRadar(location, blip, getAttackRange(), caller))
		{
			if (dynamic_cast<Sprite*>(caller->getHandleAt(blip)))
			{
				unsigned int totalDamage = totalAttackDamage();
				static_cast<Sprite*>(caller->getHandleAt(blip))->iAttackedYou(this, totalDamage, caller);
			}
		} else {
			huntDown(location, caller);
		}
	} else
	{
		//std::cout << "Hammer will wander" << std::endl;
		wander(location, caller);
	}
}

void Hammer::decreaseLife(const unsigned &howMuch, Map *caller)
{
	if (howMuch >= getCurrentLife())
	{
		if (dynamic_cast<Sprite*>(whoAttackedMe()))
		{
			static_cast<Sprite*>(caller->getHandleAt(caller->getSpriteCoord()))->addScore(150);
		}
	}
	Piece::decreaseLife(howMuch, caller);
}
