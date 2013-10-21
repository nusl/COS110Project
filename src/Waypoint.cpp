#include "Waypoint.h"

#include "Sprite.h"
#include "Player.h"
#include "PlayerAttackedWaypointException.h"

void Waypoint::iAttackedYou(Piece * const assailant, unsigned int &damage, Map *caller)
{
	caller->destroyPieceAt(caller->getCoordOf(this));
	static_cast<Sprite*>(assailant)->getOwner()->removeScore(250);
	throw PlayerAttackedWaypointException("Player attacked a waypoint.");
}
