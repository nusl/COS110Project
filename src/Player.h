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
        bool placeSprite(Map* map) const;

        bool move(const Coord& coord, Map* caller, const char& c);

    private:
        bool moveSprite(Map& map, const Coord& coord) const;

        Sprite *sprite;

        int score;
};

#endif
