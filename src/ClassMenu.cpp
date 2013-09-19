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
