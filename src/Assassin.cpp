#include "Assassin.h"

bool Assassin::attack(Map &caller)
{
	if (hasAmmo())
	{
		bang(1);
	} else
	{
		setAttackPower(5);
	}
	return Sprite::attack(caller);
}

void Assassin::reset()
{
	reload();
	Sprite::reset();
}
