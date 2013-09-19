#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

#include "Map.h"
#include "Player.h"

class Game
{
    public:

        /** The Game class' constructor.
         *
         *  @param fileName a constant std::string reference
         */
        Game(const std::string& fileName);

        /** The Game class' destructor. */
        ~Game();

        /** Start the game. */
        void start();

    private:


        void readFromFile(const std::string& fileName);

        /** A list of strings representing the possible map choices from file.
         *
         *  Maps will be read from file as strings into this vector, from which
         *  the player will be able to choose a map to play.
         */
        std::vector<std::string> mapList;

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
