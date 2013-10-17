#include "Piece.h"

void Piece::reset()
{
	currentLife = maxLife;
	myAssailant = 0;
	//NOTE: State?
}

void Piece::iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
{
	defend(assailant, damage, caller);//Modifies the damage done.
	currentLife -= damage;
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
