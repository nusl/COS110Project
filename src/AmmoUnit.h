#ifndef AMMO_UNIT_H
#define AMMO_UNIT_H

class AmmoUnit
{
	public:

	AmmoUnit(unsigned int inMaxAmmo
			,unsigned int inCurrentAmmo
			,unsigned int inPowerIncrease)
			:
			maxAmmo(inMaxAmmo)
			,currentAmmo(inCurrentAmmo)
			,powerIncrease(inPowerIncrease)
			{}

	protected:
		unsigned int maxAmmo;
		unsigned int currentAmmo;
		unsigned int powerIncrease;
};

#endif
