#include "Wall.h"

#include "Sprite.h"

#include <iostream>

void Wall::iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
{
	std::cout << "wall attacked" << std::endl;
	static_cast<Sprite*>(assailant)->knockBack(caller);
}
