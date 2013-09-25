#include "Game.h"
#include "Map.h"

#include <vector>
#include <iostream>
#include <cassert>


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

    std::vector<std::string> selectedMap;

    menuDone = false;

    while(!menuDone)
    {
        std::cout << "Map number:" << std::endl;

        std::cin >> selection;
        tutils::convert<std::string, int>(selection, iSel);

        try
        {
            mMenu[iSel - 1].execute(selectedMap);
            menuDone = true;
        } catch(OutOfBoundsException ex){}
    }

    // DO STUFFS HURR

    Map testMap(selectedMap);
    testMap.render(std::cout);

    std::cout << testMap.getCoordWaypointStart().x << " " << testMap.getCoordWaypointStart().y << std::endl;

    Player p(sprite);
    assert(p.placeSprite(testMap));

    char intent;
    while (std::cin >> intent)
    {
        if(!p.executeCommand(testMap, intent, 1))
            std::cout << "cannot move" << std::endl;

        testMap.render(std::cout);
    }

}
