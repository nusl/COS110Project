#include "MenuItem.h"

MenuItem::MenuItem(const std::string& nme)
{
    name = nme;
}

const std::string& MenuItem::getName()
{
    return name;
}

std::ostream& operator<<(std::ostream& ostr, MenuItem& item)
{
    ostr << item.name;
    return ostr;
}
