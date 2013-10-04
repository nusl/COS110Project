#ifndef PLAYER_QUIT_EXCEPTION_H
#define PLAYER_QUIT_EXCEPTION_H

#include "Exception.h"

/** The PlayerQuitException class
 *
 *  Inherits from Exception class. Used in specific cases where an index
 *  is found to be out of bounds or invalid.
 *
 */
class PlayerQuitException : public Exception
{
    public:
        /** PlayerQuitException constructor.
         *
         *  Used to customize the description to allow for greater levels of error detail
         *  in specific cases.
         *
         * @param desc a constant std::string reference
         */
        PlayerQuitException(const std::string &desc);
};

#endif
