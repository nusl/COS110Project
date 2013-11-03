#ifndef MAP_H
#define MAP_H

#include <vector>
#include <list>
#include <stack>
#include <string>
#include <ostream>
#include <typeinfo>  	//typeid

#include "Piece.h"

struct Coord
{
    /** Coord struct constructor.
     *
     *  @param inX a constant integer reference
     *  @param inY a constant integer reference
     */
    Coord(const unsigned int& inY, const unsigned int& inX):
    y(inY),
 	x(inX){}

 	bool operator==(const Coord& rhs) const
 	{
 		if(this->y != rhs.y) return false;
 		if(this->x != rhs.x) return false;
		return true;
 	}
 	
 	Coord operator+(const Coord& rhs) const
 	{
 		Coord temp(0,0);
 		temp.y = this->y + rhs.y;
 		temp.x = this->x + rhs.x;
 		return temp;
 	}
 	Coord operator-(const Coord& rhs) const
 	{
 		Coord temp(0,0);
 		temp.y = this->y - rhs.y;
 		temp.x = this->x - rhs.x;
 		return temp;
 	}
	
    size_t y;
    size_t x;
};


class Piece;

/** Map class.
 *
 *  Stores the different pieces in the game on a cartesian map.
 *	It provides a platform that pieces can interact with each other with the provided functions.
 *	It updates the map, which gives each piece to perform its own actions, as well as rendering the map.
 *	The map reads as a book does, that is, row by row.
 *	Each line has is a unique y, and each element on a line is a unique x value.
 *	
 *	The datastructure that holds the pieces is a 2d vector with a stack of pointers at each coordinate.
 *
 *
 *	NOTE: This class takes ownership of all pointers that is placed in the map datastructure.
 */

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
        
        void saveState();
        void resetState();

		
		bool inBoundary(const Coord& in) const;

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
        Piece* const getHandleAt(const Coord& coord) const;
        
        /** Get the coordinate of a Piece.
         *	Not needed yet.
         *	Searches for an object by address.
         *  @param coord a constant Coord reference.
         *  @return The coordinate to the Player's Sprite on the map as a const Coord copy.
         */

         const Coord getCoordOf(const Piece* const piece) const;

        
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
   		Piece* const getHandleWaypointStart() const;
   		
		/** Get a coord on the waypoint with state S, which is start.
		 *
		 *
         *  @param void
         *  @return Coord to Waypoint with state start of type Piece.
         */
   		const Coord getCoordWaypointStart() const;

        /** Get the Player Sprite's coordinates.
         *
         *  Not as generic as it could be.
         *
         *  @param coord a constant Coord reference.
         *  @return The coordinate to the Player's Sprite on the map as a const Coord copy.
         */
        const Coord getSpriteCoord() const;
        
        Piece* const getHandleBelowOfType(const Coord& coord, const char* const type) const;

    private:

        /** A 2D vector of a stack of pointers to pieces present on the map.
         *
         *  This vector represents the current state of the map in terms of
         *  its pieces. Pieces can be stacked on top of each other at any one location on the map.
         *	This way, it is easy to put a sprite on a waypoint and move it off a waypoint.
         *	It also makes it simpler when we need to move objects from one place to another, or when we need to destroy them.
         */
        std::vector<std::vector<std::stack<Piece*> > > map;
        std::vector<std::vector<std::stack<Piece*> > > savedMap;
        std::list<Piece*> creepOrder;//FIXME: Remove for Phase 4
};

#endif

//test stuff
/******************************************************************************************************************************/
//Map()						--PASSED
//~Map();					--PASSED
//deallocMap();				--PASSED
//move() 					--PASSED
//placePieceAt()			--PASSED
//destroyPieceAt()			--PASSED
//getSpriteCoord()			--PASSED
//getHandleAt()				--PASSED
//getCoordOf()				--NOT TESTED
//update()					--PASSED
//render()					--PASSED
//getHandleWaypointStart()	--PASSED
//getCoordWaypointStart()	--PASSED
//getSpriteCoord()			--PASSED
