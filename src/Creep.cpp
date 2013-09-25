#include <algorithm>
#include <cassert>
#include "Creep.h"

bool Creep::move(const Coord& from, const Coord& to, Map* caller)
{
	Offset newOffset(from, to);
	
	newOffset = newOffset + offsetHistory.back();

	//is the location we want to go in history?
	if(find(offsetHistory.begin(), offsetHistory.end(), newOffset) != offsetHistory.end())
		return false;//cannot move there, it is in history
	
	offsetHistory.push_back(newOffset);	
	if(offsetHistory.size() == 4)//The last 3 positions are remembered
		offsetHistory.pop_front();
	assert(offsetHistory.size() <= 3);//sanity check

	return caller->move(from, to);
}
