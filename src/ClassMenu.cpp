#include "ClassMenu.h"

#include "AssassinClassMenuItem.h"
#include "MageClassMenuItem.h"
#include "RangerClassMenuItem.h"
#include "WarriorClassMenuItem.h"

ClassMenu::ClassMenu()
{
    addItem(new AssassinClassMenuItem());
    addItem(new MageClassMenuItem());
    addItem(new RangerClassMenuItem());
    addItem(new WarriorClassMenuItem());
}

void ClassMenu::printPrompt(std::ostream &outStream)
{
    outStream << "Please select one of the following classes for your sprite.\n";
}
