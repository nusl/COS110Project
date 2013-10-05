#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "Sprite.h"

class Player
{
    public:
        Player(Sprite *sprite);
        virtual ~Player();

        void addScore(const int& value);
        void removeScore(const int& value);
        const int& getScore() const;

        const Sprite* getSpriteHandle() const;
        bool placeSprite(Map& map) const;

        bool executeCommand(Map& caller, const char& c, const int &attempt);

    private:
        bool command(const char& c) const;
        void quit() const;

        Sprite *sprite;

        int score;

        static const std::string commands;
};

#endif
