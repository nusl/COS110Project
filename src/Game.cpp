#include "Game.h"

#include "OutOfBoundsException.h"
#include "tutils.h"

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
    ClassMenu cMenu;
    cMenu.print(std::cout);

    Sprite* sprite = 0;

    bool menuDone = false;
    std::string selection;
    int iSel = 0;

    while(!menuDone)
    {
        std::cout << "Option:" << std::endl;

        std::cin >> selection;
        tutils::convert<std::string, int>(selection, iSel);

        try
        {
            cMenu[iSel - 1].execute(sprite);
            menuDone = true;
        } catch(OutOfBoundsException ex){}
    }

    MapMenu mMenu;
    mMenu.print(std::cout);

    std::string s;

    menuDone = false;

    while(!menuDone)
    {
        std::cout << "Map number:" << std::endl;

        std::cin >> selection;
        tutils::convert<std::string, int>(selection, iSel);

        try
        {
            mMenu[iSel - 1].execute(s);
            menuDone = true;
        } catch(OutOfBoundsException ex){}
    }

    // DO STUFFS HURR
}
