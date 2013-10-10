#include "Menu.h"

#include "OutOfBoundsException.h"

Menu::~Menu()
{
    // Not doing safety checks because I want it to break if we stuff something up elsewhere.
    for (unsigned i = 0; i < items.size(); ++i)
    {
        delete items[i];
        items[i] = 0;
    }
}

MenuItem& Menu::operator[](const unsigned& index)
{
    if (index < 0 || index >= items.size())//FIXME: Index can never be less than 0. It is unsigned.
    {
        throw OutOfBoundsException("Index was invalid or out of bounds when attempting to access a menu item in the Menu class.");
    }

    return *(items.at(index));
}

void Menu::print(std::ostream& outStream)
{
    // This calls the internal stream insertion operator.
    outStream << *this;
}

std::ostream& operator<<(std::ostream& ostr, Menu& menu)
{
    menu.printPrompt(ostr);
    for (unsigned i = 0; i < menu.items.size(); ++i)
    {
        ostr << (i + 1) << ". " << *menu.items[i] << '\n';
    }
    return ostr;
}

void Menu::addItem(MenuItem* item)
{
    items.push_back(item);
}
