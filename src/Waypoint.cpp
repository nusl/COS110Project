#include "Waypoint.h"

#include "Sprite.h"
#include "Player.h"
#include "PlayerAttackedWaypointException.h"

void Waypoint::iAttackedYou(Piece * const assailant, unsigned int &damage, Map *caller)
{
	//caller->destroyPieceAt(caller->getCoordOf(this));
	Piece::iAttackedYou(assailant, damage, caller);
	static_cast<Sprite*>(assailant)->getOwner()->removeScore(250);//FIXME: This can segfault if assailant is not Sprite
	throw PlayerAttackedWaypointException("Player attacked a waypoint.");
}
