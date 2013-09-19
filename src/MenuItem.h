#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <iostream>

class MenuItem
{
    public:
        MenuItem(const std::string& nme);

        friend std::ostream& operator<<(std::ostream& ostr, MenuItem& item);
    private:
        std::string name;
};

#endif // MENUITEM_H
