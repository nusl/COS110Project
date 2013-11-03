#include "AmmoUnit.h"


void AmmoUnit::bang(unsigned int howMuchToBang)
{
	if ((currentAmmo - howMuchToBang) < 0)
	{
		// Already at zero ammo
		return;
	}
	currentAmmo -= howMuchToBang;
}

void AmmoUnit::unBang(unsigned int howMuchToUnBang)
{
	if ((currentAmmo + howMuchToUnBang) > maxAmmo)
	{
		// Already at max ammo
		return;
	}
	currentAmmo += howMuchToUnBang;
}

void AmmoUnit::reload()
{
	currentAmmo = maxAmmo;
}

unsigned AmmoUnit::getAmmoPower()
{
	return powerIncrease;
}

bool AmmoUnit::hasAmmo()
{
	return (currentAmmo > 0);
}
