#ifndef CLASS_MENU_H
#define CLASS_MENU_H

#include "Menu.h"
#include "ClassMenuItem.h"

/** The ClassMenu class inheriting from the Menu class.
 *
 *  Used to specialize menu behavior for the Class menu.
 *
 */
class ClassMenu : public Menu
{
    public:
        /** ClassMenu constructor.
         *
         *  Initializes the item list to ClassMenuItem objects according to the project
         *  specification or as we feel like it.
         *
         */
        ClassMenu();

        virtual void printPrompt(std::ostream &outStream);
};

#endif
