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

    for(unsigned i = 0; i < selectedMap.size(); ++i)
    {
        std::cout << selectedMap[i] << std::endl;
    }
    std::cout << std::endl << selectedMap.size() << std::endl;

    // DO STUFFS HURR
//test stuff
/******************************************************************************************************************************/
//Map()						--PASSED
//~Map();					--PASSED
//deallocMap();				--PASSED
//move() 					--PASSED
//placePieceAt()			--PASSED
//destroyPieceAt()			--PASSED
//getSpriteCoord()			--PASSED
//getHandleAt()				--PASSED
//getCoordOf()				--NOT TESTED
//update()					--PASSED
//render()					--PASSED
//getHandleWaypointStart()	--PASSED
//getCoordWaypointStart()	--PASSED
//getSpriteCoord()			--PASSED

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
    
    Coord someCoord(0, 6);
    std::cout << "Abitrary state of someobject: " << testMap.getHandleAt(someCoord)->getState() << std::endl;
    std::cout << "Abitrary state of waypoint start: " << testMap.getHandleWaypointStart()->getState() << std::endl;

    testMap.destroyPieceAt(testMap.getCoordWaypointStart());
    testMap.render(std::cout);
    
    testMap.update();
/******************************************************************************************************************************/
}
