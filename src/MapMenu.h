#ifndef MAPMENU_H
#define MAPMENU_H

#include "Menu.h"

class MapMenu : public Menu
{
    public:
        MapMenu();
        virtual void printPrompt(std::ostream &outStream);

    private:
        void getFilesInDir(std::vector<std::string>& outList, const std::string rootPath);
};

#endif
