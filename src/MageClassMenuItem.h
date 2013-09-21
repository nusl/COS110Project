#ifndef MAGE_CLASS_MENU_ITEM_H
#define MAGE_CLASS_MENU_ITEM_H

#include "ClassMenuItem.h"
#include "Mage.h"

class MageClassMenuItem : public ClassMenuItem
{
    public:
        MageClassMenuItem();

        virtual void execute(Sprite*&);
};

#endif
