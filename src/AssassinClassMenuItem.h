#ifndef ASSASSIN_CLASS_MENU_ITEM_H
#define ASSASSIN_CLASS_MENU_ITEM_H

#include "ClassMenuItem.h"
#include "Assassin.h"

class AssassinClassMenuItem : public ClassMenuItem
{
    public:
        AssassinClassMenuItem();

        virtual void execute(Sprite*&);
};

#endif
