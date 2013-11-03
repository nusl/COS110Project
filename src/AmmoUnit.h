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

		void bang(unsigned int);
		void unBang(unsigned int);
		void reload();
		unsigned getAmmoPower();
		bool hasAmmo();

	protected:
		unsigned int maxAmmo;
		unsigned int currentAmmo;
		unsigned int powerIncrease;
};

#endif
