#include "Game.h"
#include "Map.h"

#include <vector>
#include <iostream>
#include <cassert>

#include "OutOfBoundsException.h"
#include "PlayerQuitException.h"
#include "PlayerEndException.h"
#include "PlayerResetException.h"
#include "PlayerDiedException.h"
#include "PlayerAttackedWaypointException.h"

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
            if (!sprite)
            {
            	menuDone = false;
            	continue;
            }
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
		} catch(OutOfBoundsException ex)
		{
			continue;
		}
    }

    Map map(selectedMap);

    Player p(sprite);
    assert(p.placeSprite(map));
    map.saveState();

    map.render(std::cout);

    /* Using a string(as suggested by Lyle) rather than a char prevents undefined input behavior,
     * as inputting multiple characters would cause the game to loop again for each of those characters.
     */
    std::string intent;

    unsigned attempt = 1;
	unsigned moveValue;

    try
    {
        while (true)
        {
        
			try
			{
		        // Start of global turn

		        std::cout << "Player's turn has begun." << std::endl;

				p.getSpriteHandle()->regenerateLife();
				p.getSpriteHandle()->tick();

		        while ((attempt <= p.getSpriteHandle()->getMoveCount()))
		        {
		            // Start of player turn
		            map.render(std::cout);

		            std::cout << "Player currently has a life amount of " << p.getSpriteHandle()->getCurrentLife() << "." << std::endl;

		            std::cin >> intent;

					// Build the player's intent

					tutils::convert<char, unsigned>(intent[1], moveValue);
					Intent playerIntent(intent[0], (intent.length() > 1 && isdigit(intent[1])) ? moveValue : 1);

					if(p.executeCommand(map, playerIntent, attempt))
		            {
						++attempt;
		            }
		        }

				std::cout << "Player's turn has ended." << std::endl;

				map.update();//we need allow pieces to act before rendering the new board state
			}
		    catch (PlayerResetException pqex)
			{
				std::cout << pqex.getMessage() << std::endl;
				map.resetState();
			}
			
            // Reset the current attempt to the first attempt(used in player's turn)
            attempt = 1;
        }
    }
    catch (PlayerQuitException pqex)
    {
        std::cout << pqex.getMessage() << std::endl;
    }
    catch (PlayerEndException peex)
    {
    	p.addScore(250);
        std::cout << peex.getMessage() << p.getScore() << "." << std::endl;
        map.render(std::cout);
    }
	catch (PlayerDiedException pdx)
	{
		std::cout << pdx.getMessage() << std::endl;
		map.render(std::cout);
	}
	catch (PlayerAttackedWaypointException pawex)
	{
		std::cout << pawex.getMessage() << p.getScore() << "." << std::endl;
		map.render(std::cout);
	}

}
