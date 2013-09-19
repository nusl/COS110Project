#include "MapMenu.h"

#include <dirent.h>

#include "MapMenuItem.h"

MapMenu::MapMenu()
{
    std::vector<std::string> fileNames;
    getFilesInSaveDir(fileNames);

    for (unsigned i = 0; i < fileNames.size(); ++i)
    {
        addItem(new MapMenuItem(fileNames[i]));
    }
}

void MapMenu::getFilesInSaveDir(std::vector<std::string>& list)
{
    DIR *dir;
    struct dirent *file;

    dir = opendir("./");

    if (dir != NULL){
       while ((file = readdir(dir))){
          list.push_back(file->d_name);
       }
    }

    closedir(dir);
}
