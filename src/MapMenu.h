#ifndef MAPMENU_H
#define MAPMENU_H

#include "Menu.h"

class MapMenu : public Menu
{
    public:
        MapMenu();

    private:
        void getFilesInSaveDir(std::vector<std::string>& list);
};

#endif
