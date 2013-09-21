#include "MapMenuItem.h"

#include <fstream>
#include <streambuf>

MapMenuItem::MapMenuItem(const std::string& name) : MenuItem(name)
{
}

void MapMenuItem::execute(std::string& s)
{
    // Open the file, get its contents, return as one string

    std::ifstream stream(getName().c_str());
    std::string nStr((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    s = nStr;
}
