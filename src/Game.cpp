#include "Game.h"

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
    ClassMenu* cMenu = new ClassMenu();
    cMenu->print(std::cout);
}
