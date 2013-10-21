#include "Runner.h"

void Runner::action(const Coord& coord, Map* caller)
{
	Coord location(coord);
	Creep::wander(location, caller);
}
