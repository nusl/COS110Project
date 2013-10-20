#ifndef PLAYER_DIEDEXCEPTION_H
#define PLAYER_DIEDEXCEPTION_H

#include "Exception.h"

/** The PlayerDiedException class
 *
 *  Inherits from Exception class. Used when the player's Sprite dies.
 *
 */
class PlayerDiedException : public Exception
{
	public:
		/** PlayerDiedException constructor.
		 *
		 *  Used to customize the description to allow for greater levels of error detail
		 *  in specific cases.
		 *
		 * @param desc a constant std::string reference
		 */
		PlayerDiedException(const std::string& desc);
};

#endif
