#include "Game.h"
#include "Map.h"

#include <vector>
#include <iostream>
#include <cassert>
#include <limits>

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

    testMap.render(std::cout);

    /* Using a string(as suggested by Lyle) rather than a char prevents undefined input behavior,
     * as inputting multiple characters would cause the game to loop again for each of those characters.
     */
    std::string intent;

    unsigned attempt = 1;

    while (true)
    {
        // Start of global turn

        std::cout << "GLOBAL TURN COMMENCED" << std::endl;

        /* CAUTION/WARNING AHEAD:
         * ('caution' is a REALLY ugly looking-and-feeling word, wow.)
         *
         * Undefined behavior could result when the user somehow manages to input more than one line,
         * as getline will read each line individually and therefore trigger a new game loop for each
         * line it finds. I spent a number of hours trying to find a good solution(like flushing cin buffer
         * after a read, or reading the entire buffer, thereby grabbing everything at once) but the solutions
         * I tried didn't really work. Use with caution, and take note.
         */
        while ((attempt <= p.getSpriteHandle()->getMoveCount()))
        {
            // Start of player turn

            std::cout << "PLAYER TURN COMMENCED" << std::endl;

            std::cin >> intent;

            if(p.executeCommand(testMap, intent[0], attempt))
            {
                ++attempt;
            }

            testMap.render(std::cout);
        }

        testMap.render(std::cout);
        attempt = 1;
    }

}
