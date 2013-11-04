#include "Barrier.h"
#include "Offset.h"

#include <iostream>
void Barrier::build(const Coord& myMaster, const Coord& myLocation, Map* caller)
{
	Offset directionFromMaster(myMaster, myLocation);
	
	Coord placementLocation(myLocation.y + directionFromMaster.offsetY, myLocation.x + directionFromMaster.offsetX);
	
	if(!caller->inBoundary(placementLocation))
		return;

	Barrier* childBarrier = new Barrier();
	if(caller->placePieceAt(childBarrier, placementLocation))
		childBarrier->build(myLocation, placementLocation, caller);
	return;
}
