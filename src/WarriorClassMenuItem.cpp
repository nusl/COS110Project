#include "WarriorClassMenuItem.h"

WarriorClassMenuItem::WarriorClassMenuItem() : ClassMenuItem("Warrior")
{
}

void WarriorClassMenuItem::execute(Sprite* s)
{
    s = new Warrior();
}
