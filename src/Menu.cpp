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

const MenuItem* Menu::operator[](const unsigned& index)
{
    if (index < 0 || index >= items.size())
    {
        throw new OutOfBoundsException("Index was invalid or out of bounds when attempting to access a menu item in the Menu class.");
    }

    return items[index];
}

void Menu::print(std::ostream& outStream)
{
    // This calls the internal stream insertion operator.
    outStream << *this;
}

std::ostream& operator<<(std::ostream& ostr, Menu& menu)
{
    // TODO: Implement this!
    return ostr;
}

void Menu::addItem(MenuItem* item)
{
    items.push_back(item);
}
