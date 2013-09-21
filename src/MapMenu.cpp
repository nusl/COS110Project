#include "MapMenu.h"

#include "MapMenuItem.h"
#include "tutils.h"

#include <algorithm>

MapMenu::MapMenu()
{
    unsigned lastSortLoc = 0;

    std::vector<std::string> fileNames;

    tutils::getFilesInDirRecursive(fileNames, "Maps/Easy", ".txt");
    std::sort(fileNames.begin(), fileNames.end());
    lastSortLoc = fileNames.size();

    tutils::getFilesInDirRecursive(fileNames, "Maps/Medium", ".txt");
    std::sort(fileNames.begin() + lastSortLoc, fileNames.end());
    lastSortLoc = fileNames.size();

    tutils::getFilesInDirRecursive(fileNames, "Maps/Hard", ".txt");
    std::sort(fileNames.begin() + lastSortLoc, fileNames.end());

    for (unsigned i = 0; i < fileNames.size(); ++i)
    {
        addItem(new MapMenuItem(fileNames[i]));
    }
}

void MapMenu::printPrompt(std::ostream &outStream)
{
    outStream << "Please select a map to play.\n";
}
