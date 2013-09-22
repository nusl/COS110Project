#include <vector>
#include <stack>
#include <string>
#include <stdexcept>	//domain_error
#include <cassert>		//assert
#include <typeinfo>  	//typeid

#include "Map.h"

#include "Critter.h"
#include "Hammer.h"
#include "Hunter.h"
#include "Runner.h"
#include "Sleeper.h"
#include "Boulder.h"
#include "Wall.h"
#include "Waypoint.h"
#include "EmptySpace.h"


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
	typedef std::vector<std::vector<std::stack<Piece*> > >::iterator	mapIterator;
	typedef std::vector<std::stack<Piece*> >::iterator					rowIterator;
	
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
	//We cannot move an EmptySpace, the caller is broken if this happens.
	assert(typeid(*getHandleAt(from)) != typeid(EmptySpace));

	//Are we referring to a location on the map that exists?
	if(from.x >= map.size())
		return false;
	if(from.y == map.at(from.x).size())
		return false;
	if(to.x >= map.size())
		return false;
	if(to.y == map.at(to.x).size())
		return false;
	
	//Is the location that we want to move into occupied by a piece that we cannot stack on top of?
	if(!placePieceAt(map.at(from.x).at(from.y).top(), to))
		return false;
	map.at(from.x).at(from.y).pop();
	return true;
}

bool Map::placePieceAt(Piece* piece, const Coord& coord)
{
	//Does the piece at coord allow another piece to be placed on top of it?
	if(!(getHandleAt(coord)->canBeMovedOnto()))
		return false;
	
	map.at(coord.x).at(coord.y).push(piece);
	return true;
}

const Piece* Map::getHandleAt(const Coord& coord) const
{
	return map.at(coord.x).at(coord.y).top();
}
