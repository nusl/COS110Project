#ifndef RANGER_CLASS_MENU_ITEM_H
#define RANGER_CLASS_MENU_ITEM_H

#include "ClassMenuItem.h"
#include "Ranger.h"

class RangerClassMenuItem : public ClassMenuItem
{
    public:
        RangerClassMenuItem();

        virtual void execute(Sprite*&);
};

#endif
