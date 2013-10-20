#include "Piece.h"

#include "Sprite.h"

#include <iostream>

void Piece::reset()
{
	currentLife = maxLife;
	myAssailant = 0;
	//NOTE: State?
}

void Piece::iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
{
	std::cout << "damage before: " << damage << std::endl;
	defend(assailant, damage, caller);//Modifies the damage done.
	std::cout << "damage before: " << damage << std::endl;
	if (dynamic_cast<Sprite*>(assailant))
	{
		std::string attackMod = "attacks";
		if (damage > assailant->getAttackPower())
		{
			attackMod = "critical attacks";
		} else if (damage < assailant->getAttackPower())
		{
			attackMod = "misses";
		}
		std::cout << "Player " << attackMod << ", dealing a total damage amount of " << ((damage > getCurrentLife()) ? getCurrentLife() : damage) << ".\n";
	}

	decreaseLife(damage, caller);
	myAssailant = assailant;
}

unsigned int Piece::totalAttackDamage()
{
	unsigned int damage = getAttackPower();

	unsigned int rng = static_cast<unsigned int>(this->random());//FIXME: RNG generates ints as per specification. The result is compared with uints.

	if(rng <= getHitChance())
		damage = 0;
	if(rng <= getCritChance())
		damage *= 2;

	return damage;
}

void Piece::defend(Piece* const assailant, unsigned int& damage, Map* caller)
{
	unsigned int rng = static_cast<unsigned int>(this->random());//FIXME: RNG generates ints as per specification. The result is compared with uints.
	if(rng == 0)
		return;//disregard 0 value

	if(rng <= getDodgeChance())
		damage = 0;

	if(rng <= getParryChance())
		damage /= 2;
}

void Piece::decreaseLife(const unsigned& howMuch, Map *caller)
{
	if (howMuch >= getCurrentLife())
	{
		// I am dead. Sniff.
		caller->destroyPieceAt(caller->getCoordOf(this));
		return;
	}

	currentLife -= howMuch;
}
