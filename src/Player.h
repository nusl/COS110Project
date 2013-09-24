#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

class Player
{
    public:
        Player(Sprite *);

        void addScore(const int& value);
        void removeScore(const int& value);
        const int& getScore() const;

        virtual ~Player();
    private:
        Sprite *sprite;

        int score;
};

#endif
