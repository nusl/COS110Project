#include "MapMenuItem.h"

#include "tutils.h"

#include <fstream>
#include <streambuf>
#include <sstream>

MapMenuItem::MapMenuItem(const std::string& name) : MenuItem(name)
{
}

void MapMenuItem::execute(std::vector<std::string>& s)
{
    // Open the file, get its contents, return as a vector of strings

    std::ifstream stream(getName().c_str());
    std::string nStr((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    std::string temp;
    std::stringstream strStream(nStr);

    // Kill the first line(contains useless map dimension information)
    std::getline(strStream, temp);

    while(std::getline(strStream, temp))
    {
		// Windows likes putting CR-LF in their files. We remove that here.
        tutils::sanitize(temp, "\r\n");
        s.push_back(temp);
    }
}
