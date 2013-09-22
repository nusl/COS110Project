#include <stdexcept>

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
					//TODO:deallocMap();
					throw std::domain_error("Map that was loaded specifies a board piece that does not exist");
			}
			rowOnMap.push_back(pointOnMap);
		}
		map.push_back(rowOnMap);
	}
}
