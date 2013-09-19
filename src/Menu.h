#ifndef MENU_H
#define MENU_H

#include <vector>
#include <iostream>

#include "MenuItem.h"

/** The Menu class.
 *
 *  Used to abstract the program's menu. Holds a list of pointers to menu items.
 *
 */
class Menu
{
    public:
        /** The Menu class' destructor.
         *
         *  Handles deletion of the MenuItem list.
         *
         */
        virtual ~Menu();

        /** Prints the menu to the supplied std::ostream.
         *
         *  @param outStream a constant std::ostream reference
         */
        void print(std::ostream& outStream);

        /** Subscript operator for the Menu class.
         *
         * @param index a constant int reference
         * @return A constant MenuItem reference
         */
        const MenuItem* operator[](const unsigned& index);

        /** Stream insertion operator for the Menu class.
         *
         *  Used to simplify printing of the Menu should someone want to use this.
         *
         * @param ostr a std::ostream reference
         * @param menu a Menu reference
         * @return An ostream reference
         */
        friend std::ostream& operator<<(std::ostream& ostr, Menu& menu);

    private:

        /** Vector holding pointers to MenuItem objects for the Menu. */
        std::vector<MenuItem*> items;

    protected:

        /** Add an item to the MenuItem list.
         *
         * @param item a constant MenuItem pointer
         */
        void addItem(MenuItem *item);
};

#endif
