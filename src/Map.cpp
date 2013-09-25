#include <vector>
#include <stack>
#include <string>
#include <stdexcept>	//domain_error
#include <cassert>		//assert
#include <typeinfo>  	//typeid
#include <ostream>

#include "Map.h"

#include "Sprite.h"//used in dynamic casting
#include "Critter.h"
#include "Hammer.h"
#include "Hunter.h"
#include "Runner.h"
#include "Sleeper.h"
#include "Boulder.h"
#include "Wall.h"
#include "Waypoint.h"
#include "EmptySpace.h"

typedef std::vector<std::vector<std::stack<Piece*> > >::const_iterator	const_mapIterator;
typedef std::vector<std::stack<Piece*> >::const_iterator				const_rowIterator;
typedef std::vector<std::vector<std::stack<Piece*> > >::iterator		mapIterator;
typedef std::vector<std::stack<Piece*> >::iterator						rowIterator;
typedef std::vector<std::vector<std::stack<Piece*> > >::size_type		mapSize;
typedef std::vector<std::stack<Piece*> >::size_type						rowSize;


Map::Map(const std::vector<std::string>& mapState)
{	
	for(std::vector<std::string>::const_iterator it = mapState.begin(); it!=mapState.end(); ++it)
	{
		std::vector<std::stack<Piece*> > rowOnMap;
		for(std::string::const_iterator it2 = it->begin(); it2!=it->end(); ++it2)
		{
			std::stack<Piece*> pointOnMap;
			pointOnMap.push(new EmptySpace());//all positions on the map has an EmptySpace in it
			
			switch(*it2)
			{
				case 'C':
					pointOnMap.push(new Critter());
					break;
				case 'H':
					pointOnMap.push(new Hammer());
					break;
				case 'U':
					pointOnMap.push(new Hunter());
					break;
				case 'R':
					pointOnMap.push(new Runner());
					break;
				case 'Z':
					pointOnMap.push(new Sleeper());
					break;
				case 'B':
					pointOnMap.push(new Boulder());
					break;
				case '/':
					pointOnMap.push(new Wall());
					break;
				case 'S':
				case 'E':
					pointOnMap.push(new Waypoint(*it2));
					break;
				case '.':
					//The first object created at the bottom of all stacks is an EmptySpace() object
					//So, do not create one here.
					break;
				default:
					deallocMap();
					throw std::domain_error("Map that was loaded specifies a board piece that does not exist");
			}
			rowOnMap.push_back(pointOnMap);
		}
		map.push_back(rowOnMap);
	}
}

Map::~Map()
{
	deallocMap();
}

void Map::deallocMap()
{	
	for(mapIterator it = map.begin(); it!=map.end(); ++it)
	{
		for(rowIterator it2 = it->begin(); it2!=it->end(); ++it2)
		{
			while(it2->size())
			{
				delete it2->top();
				it2->pop();
			}
		}
	}
}

bool Map::move(const Coord& from, const Coord& to)
{
	//Are we referring to a location on the map that exists?
	if(from.y >= map.size())
		return false;
	if(from.x >= map.at(from.y).size())
		return false;
	if(to.y >= map.size())
		return false;
	if(to.x >= map.at(to.y).size())
		return false;

	//We cannot move an EmptySpace, the caller is broken if this happens.
	assert(typeid(*getHandleAt(from)) != typeid(EmptySpace));
	
	//Is the location that we want to move into occupied by a piece that we cannot stack on top of?
	if(!placePieceAt(map.at(from.y).at(from.x).top(), to))
		return false;
	map.at(from.y).at(from.x).pop();
	return true;
}

bool Map::placePieceAt(Piece* piece, const Coord& coord)
{
	//Does the piece at coord allow another piece to be placed on top of it?
	if(!(getHandleAt(coord)->canBeMovedOnto()))
		return false;
	
	map.at(coord.y).at(coord.x).push(piece);
	return true;
}

void Map::destroyPieceAt(const Coord& coord)
{
	//We should not delete an EmptySpace except in the destructor, the caller is broken if this happens.
	assert(typeid(*getHandleAt(coord)) != typeid(EmptySpace));
	
	delete map.at(coord.y).at(coord.x).top();
	map.at(coord.y).at(coord.x).pop();
}

const inline Piece* Map::getHandleAt(const Coord& coord) const
{
	return map.at(coord.y).at(coord.x).top();
}

//Call action() of pieces on top of the stack at each coordinate.
//Actions are called on a row by row bases.
void Map::update()
{
	std::vector<std::vector<std::stack<Piece*> > > strictOrder = map;//FIXME: This could get expensive
	for(mapSize y = 0; y!=strictOrder.size(); ++y)
		for(rowSize x = 0; x!=strictOrder[y].size(); ++x)
			strictOrder[y][x].top()->action(Coord(y,x), this);
}

//Renders the map by calling getState()
void Map::render(std::ostream& os) const
{	
	os << " ";
	for(rowSize i = 0; i != map[0].size(); ++i)//NOTE: Does not work if the map is not of rectangular dimensions
		os << "-";
	os << std::endl;
	
	for(const_mapIterator it = map.begin(); it!=map.end(); ++it)
	{
		os << "|";
		for(const_rowIterator it2 = it->begin(); it2!=it->end(); ++it2)
				os << it2->top()->getState();
		os << "|" << '\n';
	}

	os << " ";
	for(rowSize i = 0; i != map[0].size(); ++i)
		os << "-";
	os << std::endl;
}

const Piece* Map::getHandleWaypointStart() const
{
	for(const_mapIterator it = map.begin(); it!=map.end(); ++it)
	{
		for(const_rowIterator it2 = it->begin(); it2!=it->end(); ++it2)
		{
			if(typeid(*(it2->top())) == typeid(Waypoint))
				if(it2->top()->getState() == 'S')//If the waypoint is start
					return it2->top();
		}
	}
	assert(false);//we should never fail to return a handle to a starting waypoint.
	//This function is solely used during setup phase. If an object is on the waypoint, we have passed setup phase.
}

const Coord Map::getCoordWaypointStart() const
{
	for(mapSize y = 0; y!=map.size(); ++y)
		for(rowSize x = 0; x!=map[y].size(); ++x)
			if(typeid(*map[y][x].top()) == typeid(Waypoint))
				if(map[y][x].top()->getState() == 'S')//If the waypoint is start
					return Coord(y,x);
	assert(false);//we should never fail to return a coordinate to a starting waypoint.
	//This function is solely used during setup phase. If an object is on the waypoint, we have passed setup phase.
}

const Coord Map::getSpriteCoord() const
{
	for(mapSize y = 0; y!=map.size(); ++y)
		for(rowSize x = 0; x!=map[y].size(); ++x)
			if(dynamic_cast<Sprite*>(map[y][x].top()))//TODO: This is expensive, if we need to optimise, put a coord in map that points to sprite.
				return Coord(y,x);
	assert(false);//we should never fail to return a coordinate to a sprite.	
}
