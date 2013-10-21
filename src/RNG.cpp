#include "RNG.h"
#include <typeinfo>		//typeid
#include <stdexcept>	//domain_error
#include <cstdlib>		//srand() rand()
#include <vector>
#include <string>

#include "Boulder.h"
#include "Wall.h"
#include "Waypoint.h"
#include "Critter.h"
#include "Hammer.h"
#include "Hunter.h"
#include "Runner.h"
#include "Sleeper.h"
#include "Assassin.h"
#include "Mage.h"
#include "Ranger.h"
#include "Warrior.h"

RNG::RNG():seedSet(false){}

unsigned int RNG::type() const
{
	if(typeid(*this) == typeid(Boulder))
		return 0;
	if(typeid(*this) == typeid(Wall))
		return 1;
	if(typeid(*this) == typeid(Waypoint))
		return 2;
	if(typeid(*this) == typeid(Critter))
		return 3;
	if(typeid(*this) == typeid(Hammer))
		return 4;
	if(typeid(*this) == typeid(Hunter))
		return 5;
	if(typeid(*this) == typeid(Runner))
		return 6;
	if(typeid(*this) == typeid(Sleeper))
		return 7;
	if(typeid(*this) == typeid(Assassin))
		return 8;
	if(typeid(*this) == typeid(Mage))
		return 9;
	if(typeid(*this) == typeid(Ranger))
		return 10;
	if(typeid(*this) == typeid(Warrior))
		return 11;

    throw std::domain_error(std::string("A class has been included in the hierarchy that has not been registered in the RNG. Unregistered class name: ") + std::string(typeid(*this).name()));
}

//	FIXME:What if the number list runs out?
//	^ Have you ever heard the definition of insanity?
int RNG::random()
{
	if(!seedSet)
	{
		srand(type());
		seedSet = true;

		for(int i = 0; i < 10000; i++)//FIXME: This is expensive!
		{
			int num = rand() % 101;
			numberList.push_back(num);
		}
	}
	
	int randNum = numberList[0];
	numberList.erase(numberList.begin());
//	std::cout << "RNG_main: " << typeid(*this).name() << " : " << randNum << std::endl;
	return randNum;
}
