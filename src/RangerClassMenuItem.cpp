#include "RangerClassMenuItem.h"

RangerClassMenuItem::RangerClassMenuItem() : ClassMenuItem("Ranger")
{
}

void RangerClassMenuItem::execute(Sprite *&s)
{
	s = new Ranger();
}
