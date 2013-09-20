#ifndef WARRIOR_CLASS_MENU_ITEM_H
#define WARRIOR_CLASS_MENU_ITEM_H

#include "ClassMenuItem.h"
#include "Warrior.h"

class WarriorClassMenuItem : public ClassMenuItem
{
    public:
        WarriorClassMenuItem();

        virtual void execute(Sprite*);
};

#endif
