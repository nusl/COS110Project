#include "PlayerAttackedWaypointException.h"

PlayerAttackedWaypointException::PlayerAttackedWaypointException(const std::string &desc) : Exception("Player lost the game by attacking a waypoint! Final score is ", desc)
{
};
