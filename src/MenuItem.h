#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

class MenuItem
{
    public:
        MenuItem(const std::string& nme);
    private:
        std::string name;
};

#endif // MENUITEM_H
