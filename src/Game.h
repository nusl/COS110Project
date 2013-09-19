#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <iostream>

#include "Map.h"
#include "Player.h"
#include "ClassMenu.h"

class Game
{
    public:

        /** The Game class' constructor.
         *
         *  @param fileName a constant std::string reference
         */
        Game();

        /** The Game class' destructor. */
        ~Game();

        /** Start the game. */
        void start();

    private:

        void readFromFile(const std::string& fileName);

        /** A handle on the chosen map to be used for the game.
         *
         *  This is used by the game to interact with the current map,
         *  as well as get the game started.
         */
        Map* handleMap;

        /** A handle on the current player. */
        Player* handlePlayer;

        /** Castrate the copy constructor.
         *
         *  We do this to prevent copies of the Map being made.
         *
         * @param other a constant Map reference
         */
        Game(const Game& other);

        /** Castrate the assignment operator.
         *
         *  We do this to prevent copies of the Map being made.
         *
         * @param other a constant Map reference
         */
        Game& operator=(const Game& other);
};

#endif
