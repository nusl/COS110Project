#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <iostream>
#include "Sprite.h"

class MenuItem
{
    public:
        MenuItem(const std::string& nme);
        virtual ~MenuItem(){}

        virtual void execute(Sprite*){}
        virtual void execute(std::string&){}

        friend std::ostream& operator<<(std::ostream& ostr, MenuItem& item);
    private:
        std::string name;
};

#endif // MENUITEM_H
