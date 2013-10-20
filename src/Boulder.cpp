#include "Boulder.h"

#include "Sprite.h"

void Boulder::iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller)
{
	static_cast<Sprite*>(assailant)->knockBack(caller);
}
