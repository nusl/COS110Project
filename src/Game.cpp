#include "Game.h"

#include "OutOfBoundsException.h"

Game::Game()
{

}

Game::~Game()
{
    //delete handleMap;
    //delete handlePlayer;
}

void Game::start()
{
    std::cout << "Please select a class:" << std::endl;
    ClassMenu* cMenu = new ClassMenu();
    cMenu->print(std::cout);

    int selection;
    std::cin >> selection;

    try
    {
        Sprite* s = 0;
        (*cMenu)[selection - 1]->execute(s);
        std::cout << s << std::endl;
    } catch(OutOfBoundsException ex)
    {
        std::cout << "Invalid selection" << std::endl;
    }

    MapMenu* mMenu = new MapMenu();
    mMenu->print(std::cout);
}
