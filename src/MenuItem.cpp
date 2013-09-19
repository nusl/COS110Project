#include "MenuItem.h"

MenuItem::MenuItem(const std::string& nme)
{
    name = nme;
}

std::ostream& operator<<(std::ostream& ostr, MenuItem& item)
{
    ostr << item.name;
    return ostr;
}
