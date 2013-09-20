#include "MapMenuItem.h"

MapMenuItem::MapMenuItem(const std::string& name) : MenuItem(name)
{
}

void MapMenuItem::execute(std::string& s)
{
    // Open the file, get its contents, return as one string
    s = "dummy MapMenuItem";
}
