#ifndef MAP_H
#define MAP_H

#include <vector>
#include <stack>
#include <string>
#include <ostream>

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

struct Offset
{
    /** Offset struct constructor.
     *
     *  @param inX a constant integer reference
     *  @param inY a constant integer reference
     */
    Offset(const int& inX, const int& inY)
    {
        x = inX;
        y = inY;
    }
    int x;
    int y;
};

/** The Map class.
 *
 *  Holds the current state of the game's map as well as some functions to
 *  facilitate actions on the map itself.
 */
class Piece;

//Map takes ownership of all pointers that are passed to it.
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
         *  Cleanup of the Map class occurs here. Calls deallocMap().
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
         *  @return bool indicating if it is possible to place a piece on top of whatever piece is already in place at coord.
         */
        bool placePieceAt(Piece* piece, const Coord& coord);

        /** Destroys piece at coord.
         *
         *	Deletes the memory location pointed to, by the top pointer on the stack at that particular location, indicated by coord.
         *	It then pops the invalidated pointer of the stack.
         *
         *  @param coord a constant Coord reference.
         *  @return void
         */
		void destroyPieceAt(const Coord& coord);

        /** Get handle of piece at a coordinate on the map.
         *
         *  @param coord a constant Coord reference.
         *  @return The Piece object at the coordinate on the map as a constant Piece pointer.
         */
        const Piece* getHandleAt(const Coord& coord) const;
        
        /** Update the current state of the map.
         *
         *  This update calls action() on every piece on the board that is at the top of the board stack.
         *  Action(), implemented in Piece hierarchy, defines the behaviour for that piece.
         *	Actions are called on a row by row bases.
         *
         *  @return void
         */
        void update();

		/** Renders the map by reading the state of every piece on top of the stack.
		 *
         *  @param ostream&
         *  @return void
         */
		void render(std::ostream& os) const;
        
       /*NON GENERICS:*/
       
		/** Get a handle on the waypoint with state S, which is start.
		 *
		 *
         *  @param void
         *  @return Handle(pointer) to Waypoint with state start of type Piece.
         */
   		const Piece* getHandleWaypointStart() const;

        /** Get the Player Sprite's coordinates.
         *
         *  Not as generic as it could be.
         *
         *  @param coord a constant Coord reference.
         *  @return The coordinate to the Player's Sprite on the map as a const Coord copy.
         */
        const Coord getSpriteCoord() const;

    private:

        /** A 2D vector of a stack of pointers to pieces present on the map.
         *
         *  This vector represents the current state of the map in terms of
         *  its pieces. Pieces can be stacked on top of each other at any one location on the map.
         *	This way, it is easy to put a sprite on a waypoint and move it off a waypoint.
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
