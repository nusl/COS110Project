#include "Game.h"

#include <vector>
#include <iostream>

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

    std::vector<std::string> s;

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

    for(unsigned i = 0; i < s.size(); ++i)
    {
        std::cout << s[i] << std::endl;
    }
    std::cout << std::endl << s.size() << std::endl;

    // DO STUFFS HURR
    //test stuff
    /******************************************************************************************************************************/
        Map testMap(selectedMap);
        testMap.render(std::cout);

        std::cout << testMap.getCoordWaypointStart().x << " " << testMap.getCoordWaypointStart().y << std::endl;

        if(!testMap.placePieceAt(sprite, testMap.getCoordWaypointStart()))
            assert(false);
        testMap.render(std::cout);

        std::cout << "Sprite Coord:" << testMap.getSpriteCoord().y << testMap.getSpriteCoord().x << std::endl;

        Coord spriteCoord(testMap.getSpriteCoord());
        spriteCoord.y += 0;
        spriteCoord.x += 2;

        if(!testMap.move(testMap.getSpriteCoord(), spriteCoord))
            std::cout << "cannot move" << std::endl;
        testMap.render(std::cout);
    /******************************************************************************************************************************/
}
