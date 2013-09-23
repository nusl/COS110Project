#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <iostream>
#include <vector>

#include "Sprite.h"

class MenuItem
{
    public:
        explicit MenuItem(const std::string& nme);
        virtual ~MenuItem(){}

        virtual void execute(Sprite*&){}
        virtual void execute(std::vector<std::string>&){}

        const std::string& getName();

        friend std::ostream& operator<<(std::ostream& ostr, MenuItem& item);
    private:
        std::string name;
};

#endif // MENUITEM_H
