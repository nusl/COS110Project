#ifndef PLAYER_RESET_EXCEPTION_H
#define PLAYER_RESET_EXCEPTION_H

#include "Exception.h"

/** The PlayerResetException class
 *
 *  Inherits from Exception class. Used in specific cases where an index
 *  is found to be out of bounds or invalid.
 *
 */
class PlayerResetException : public Exception
{
    public:
        /** PlayerResetException constructor.
         *
         *  Used to customize the description to allow for greater levels of error detail
         *  in specific cases.
         *
         * @param desc a constant std::string reference
         */
        PlayerResetException(const std::string &desc);
};

#endif
