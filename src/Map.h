#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "Piece.h"

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
    /** Coord struct constructor.
     *
     *  @param inX a constant integer reference
     *  @param inY a constant integer reference
     */
    Coord(const int& inX, const int& inY)
    {
        x() = inX;
        y() = inY;
    }

    /** The x coordinate.
     *
     * @return An integer reference.
     */
    int& x()
    {
        return first;
    }

    /** The y coordinate.
     *
     * @return An integer reference.
     */
    int& y()
    {
        return second;
    }
};

/** The Map class.
 *
 *  Holds the current state of the game's map as well as some functions to
 *  facilitate actions on the map itself.
 */
class Piece;
class Map
{
    public:

        /** The constructor for the map class accepting a std::string representing the map state.
         *
         *  The given map state will be used to initialize the Map class' internal vector of Pieces.
         *
         *  @param mapState a constant std::string reference.
         */
        Map(const std::string& mapState);

        /** The Map class' descructor.
         *
         *  Cleanup of the Map class occurs here.
         */
        ~Map();

        /** Move the piece at the first coordinate on the map to the location of the second coordinate on the map.
         *
         *  The function will perform the actual move on the map should the move be valid and possible,
         *  and then return true. Should the move not be valid and possible, the function will return
         *  false and not perform any moves.
         *
         *  @param from a constant Coord reference.
         *  @param to a constant Coord reference.
         *  @return A boolean signifying whether or not the move is possible.
         */
        bool move(const Coord& from, const Coord& to);

        /** Get the Player Sprite's relative coordinates to the provided coordinates.
         *
         *  Not as generic as it could be.
         *
         *  @param coord a constant Coord reference.
         *  @return The relative coordinate to the Player's Sprite on the map as a const Coord copy.
         */
        const Coord getSpriteRelativeCoord(const Coord& coord) const;

        /** Set the piece at the coordinate on the map to the provided piece.
         *
         *  @param piece a constant Piece pointer.
         *  @param coord a constant Coord reference.
         *  @return void
         */
        void setPieceAt(const Piece* piece, const Coord& coord);

        /** Get handle of piece at a coordinate on the map.
         *
         *  @param coord a constant Coord reference.
         *  @return The Piece object at the coordinate on the map as a constant Piece pointer.
         */
        const Piece* getHandleAt(const Coord& coord) const;

        /** Update the current state of the map.
         *
         *  This update performs any moves or actions necessary and updates the map accordingly
         *  before ending the function.
         *
         *  @return void
         */
        void update();

    private:

        /** A 2D vector of pointers to pieces present on the map.
         *
         *  This vector represents the current state of the map in terms of
         *  its pieces.
         */
        std::vector<std::vector<Piece*> > map;

        /** Castrate the copy constructor.
         *
         *  We do this to prevent copies of the Map being made.
         *
         * @param other a constant Map reference
         */
        Map(const Map& other);
};

#endif
