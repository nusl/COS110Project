#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

class Player
{
    public:
        Player(Sprite *);
        virtual ~Player();

        void addScore(const int& value);
        void removeScore(const int& value);
        const int& getScore() const;

        bool move(const Coord& coord, Map* caller, const char& c);

    private:
        Sprite *sprite;

        int score;
};

#endif
