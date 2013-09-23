#ifndef MAP_MENU_ITEM_H
#define MAP_MENU_ITEM_H

#include "MenuItem.h"

#include <string>
#include <vector>

class MapMenuItem : public MenuItem
{
    public:
        MapMenuItem(const std::string& name);

        virtual void execute(std::vector<std::string> &);
};

#endif
