#ifndef MAP_H
#define MAP_H

#include <vector>
#include <stack>
#include <string>

#include "Piece.h"


struct Coord
{
    /** Coord struct constructor.
     *
     *  @param inX a constant integer reference
     *  @param inY a constant integer reference
     */
    Coord(const unsigned int& inX, const unsigned int& inY)
    {
        x = inX;
        y = inY;
    }
    unsigned int x;
    unsigned int y;
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
        Map(const std::vector<std::string>& mapState);

        /** The Map class' descructor.
         *
         *  Cleanup of the Map class occurs here.
         */
        ~Map();
        void deallocMap();

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

        /** Set the piece at the coordinate on the map to the provided piece.
         *
         *  @param piece a constant Piece pointer.
         *  @param coord a constant Coord reference.
         *  @return void
         */
        bool placePieceAt(Piece* piece, const Coord& coord);

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
        
       /*NON GENERICS:*/
       
		/** Get a handle on the waypoint with state S, which is start.
		 *
		 *
         *  @param void
         *  @return Handle(pointer) to Waypoint with state start of type Piece.
         */
   		const Piece* getHandleWaypointStart();

        /** Get the Player Sprite's relative coordinates to the provided coordinates.
         *
         *  Not as generic as it could be.
         *
         *  @param coord a constant Coord reference.
         *  @return The relative coordinate to the Player's Sprite on the map as a const Coord copy.
         */
        const Coord getSpriteRelativeCoord(const Coord& coord) const;

    private:

        /** A 2D vector of a stack of pointers to pieces present on the map.
         *
         *  This vector represents the current state of the map in terms of
         *  its pieces. Pieces can be stacked on top of each other at any one location on the map.
         *	This way it is easy to put a sprite on a waypoint and move it off a waypoint.
         *	It also makes it simpler when we need to move objects from one place to another, or when we need to destroy them.
         */
        std::vector<std::vector<std::stack<Piece*> > > map;

        /** Castrate the copy constructor.
         *
         *  We do this to prevent copies of the Map being made.
         *
         * @param other a constant Map reference
         */
        Map(const Map& other);
};

#endif
