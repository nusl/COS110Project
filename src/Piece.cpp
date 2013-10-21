#include "Piece.h"

#include "Sprite.h"

#include <iostream>
#include "Player.h"

void Piece::reset()
{
	currentLife = maxLife;
	myAssailant = 0;
	RNG::resetRNG();
	//NOTE: State?
}

void Piece::iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
{
	std::string attackMod = "attacks";

	if (damage > assailant->getAttackPower())
	{
		attackMod = "critical attacks";
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
	unsigned int damage = 0;
	
	unsigned int hitRng = static_cast<unsigned int>(this->random());
	unsigned int critRng = static_cast<unsigned int>(this->random());
	
	if((hitRng) <= static_cast<unsigned int>(getHitChance()*100) && (hitRng!=0))
	{
		damage = getAttackPower();
		if((critRng) <= static_cast<unsigned int>(getCritChance()*100) && (critRng!=0))
		{
			damage *= 2;
		}
	} else
	{
		damage = 0;
	}
//	std::cout <<std::boolalpha << "Damage: " << damage << " Hit chance: " << getHitChance()<< std::endl
//	<< " Crit chance: " << getCritChance() << std::endl;
	return damage;
}

void Piece::defend(Piece* const assailant, unsigned int& damage, Map* caller)
{
	if(static_cast<unsigned int>(this->random()) <= static_cast<unsigned int>(getDodgeChance()*100))
	{
		damage = 0;
	}
	else
	{
		if(static_cast<unsigned int>(this->random()) <= static_cast<unsigned int>(getParryChance()*100))
		{
			damage /= 2;
		}
	}

//	std::cout << "Defense: " << damage << " Dodge: " << getDodgeChance() << " Parry: " << getParryChance() << std::endl;
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
