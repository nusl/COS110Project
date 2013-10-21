#include "Piece.h"

#include "Sprite.h"

#include <iostream>
#include "Player.h"

void Piece::reset()
{
	currentLife = maxLife;
	myAssailant = 0;
	//NOTE: State?
}

void Piece::iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
{
	std::string attackMod = "attacks";

	if (damage > assailant->getAttackPower())
	{
		attackMod = "critical attacks";
	} else if (damage < assailant->getAttackPower())
	{
		attackMod = "misses";
	}

	// I check for damage greater than zero here since the Sprite's attack would have
	// missed should the damage be zero. Since the damage is zero and the attack missed,
	// the creep does not need to do any defending against a missed attack.
	if (damage > 0)
	{
		//Modifies the damage done.
		defend(assailant, damage, caller);

		// Defense is a dodge if the damage is zero.
		// Defense is a parry if the damage is halved(less than the original damage).
		if (damage == 0)
		{
			attackMod = "dodge";
		}
		if (damage < assailant->getAttackPower())
		{
			attackMod = "parry";
		}
	}

	if (dynamic_cast<Sprite*>(assailant))
	{
		std::cout << "Player " << attackMod << ", dealing a total damage amount of " << ((damage > getCurrentLife()) ? getCurrentLife() : damage) << ".\n";
	}

	decreaseLife(damage, caller);
	myAssailant = assailant;
}

unsigned int Piece::totalAttackDamage()
{
	unsigned int damage = getAttackPower();

	unsigned int rng;
	do
		rng = static_cast<unsigned int>(this->random());//FIXME: RNG generates ints as per specification. The result is compared with uints.
	while(!rng);//discard 0
	
	if(!(rng <= (getHitChance()*100)))
	{
		if(rng <= (getCritChance()*100))
		{
			damage *= 2;
		}
	}

	//std::cout << "Damage: " << damage << " RNG: " << rng << " Hit chance: " << getHitChance() << " Crit chance: " << getCritChance() << std::endl;
	return damage;
}

void Piece::defend(Piece* const assailant, unsigned int& damage, Map* caller)
{
	unsigned int rng;
	do
		rng = static_cast<unsigned int>(this->random());//FIXME: RNG generates ints as per specification. The result is compared with uints.
	while(!rng);//discard 0

	if((100 - rng) <= (getDodgeChance()*100))
		damage = 0;
	if((100 - rng) <= (getParryChance()*100))
		damage /= 2;

	//std::cout << "Defense: " << damage << " RNG: " << rng << " Dodge: " << getDodgeChance() << " Parry: " << getParryChance() << std::endl;
}

void Piece::increaseLife(const unsigned &howMuch)
{
	if (howMuch > 0)
	{
		currentLife += howMuch;
	}
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
