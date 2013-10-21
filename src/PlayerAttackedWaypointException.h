#ifndef PLAYER_ATTACKED_WAYPOINT_EXCEPTION_H
#define PLAYER_ATTACKED_WAYPOINT_EXCEPTION_H

#include "Exception.h"

/** The PlayerAttackedWaypointException class
 *
 *  Inherits from Exception class. Used when the player has attacked a waypoint.
 *
 */
class PlayerAttackedWaypointException : public Exception
{
	public:
		/** PlayerAttackedWaypointException constructor.
		 *
		 *  Used to customize the description to allow for greater levels of error detail
		 *  in specific cases.
		 *
		 * @param desc a constant std::string reference
		 */
		PlayerAttackedWaypointException(const std::string& desc);
};

#endif
