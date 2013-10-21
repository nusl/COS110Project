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
	//std::cout << "damage before: " << damage << std::endl;
	defend(assailant, damage, caller);//Modifies the damage done.
	//std::cout << "damage before: " << damage << std::endl;
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

	unsigned int rng;
	do
		rng = static_cast<unsigned int>(this->random());//FIXME: RNG generates ints as per specification. The result is compared with uints.
	while(!rng);//discard 0
	
	if(!(rng <= (getHitChance()*100)))//it misses
		damage = 0;
	if(rng <= (getCritChance()*100))
		damage *= 2;

	std::cout << "Damage: " << damage << " RNG: " << rng << " Hit chance: " << getHitChance() << " Crit chance: " << getCritChance() << std::endl;
	return damage;
}

void Piece::defend(Piece* const assailant, unsigned int& damage, Map* caller)
{
	unsigned int rng;
	do
		rng = static_cast<unsigned int>(this->random());//FIXME: RNG generates ints as per specification. The result is compared with uints.
	while(!rng);//discard 0

	if(rng <= (getDodgeChance()*100))
		damage = 0;

	if(rng <= (getParryChance()*100))
		damage /= 2;

	std::cout << "Defense: " << damage << " RNG: " << rng << " Dodge: " << getDodgeChance() << " Parry: " << getParryChance() << std::endl;
}

void Piece::decreaseLife(const unsigned& howMuch, Map *caller)
{
	if (howMuch >= getCurrentLife())
	{
		// I am dead. Sniff.
		caller->destroyPieceAt(caller->getCoordOf(this));
		static_cast<Sprite*>(caller->getHandleAt(caller->getSpriteCoord()))->getOwner()->addScore(5);
		return;
	}

	currentLife -= howMuch;
}
