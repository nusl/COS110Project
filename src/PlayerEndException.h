#ifndef PLAYER_END_EXCEPTION_H
#define PLAYER_END_EXCEPTION_H

#include "Exception.h"

/** The PlayerEndException class
 *
 *  Inherits from Exception class. Used in specific cases where an index
 *  is found to be out of bounds or invalid.
 *
 */
class PlayerEndException : public Exception
{
    public:
        /** PlayerEndException constructor.
         *
         *  Used to customize the description to allow for greater levels of error detail
         *  in specific cases.
         *
         * @param desc a constant std::string reference
         */
        PlayerEndException(const std::string &desc);
};

#endif
