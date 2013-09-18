#ifndef MAP_H
#define MAP_H

/** Struct to hold coordinates of objects in the Map.
 *  This struct inherits from std::pair to enable the functionality that might be attractive in doing so.
 *
 *  Also, it keeps Lyle happy. He wanted the pair, and I wanted the struct. It's a middle-ground! :D
 *  Besides, Lyle, a pair is just a struct with some bolted-on stuffs anyway;
 *
 *  template <class T1, class T2> struct pair;
 *  www.cplusplus.com/reference/utility/pair/
 *
 *  ---
 *
 *  Use of this struct would be as follows;
 *
 *  Coord c;
 *
 *  c.x() = 4;
 *  c.y() = 5;
 *
 *  int x = c.x();
 *  int y = c.y();
 *
 *  etc.
 *
 *  It's pretty nifty, yes?
 */
struct Coord : public std::pair<int, int>
{
    int& x()
    {
        return first;
    }
    int& y()
    {
        return second;
    }
};

class Map
{

};

#endif
