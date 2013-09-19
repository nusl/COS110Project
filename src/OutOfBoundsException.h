#ifndef OUT_OF_BOUNDS_EXCEPTION_H
#define OUT_OF_BOUND_SEXCEPTION_H

#include "Exception.h"

/** The OutOfBoundsException class
 *
 *  Inherits from Exception class. Used in specific cases where an index
 *  is found to be out of bounds or invalid.
 *
 */
class OutOfBoundsException : public Exception
{
    public:
        /** OutOfBoundsException constructor.
         *
         *  Used to customize the description to allow for greater levels of error detail
         *  in specific cases.
         *
         * @param desc a constant std::string reference
         */
        OutOfBoundsException(const std::string &desc);
};

#endif
