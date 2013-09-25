#ifndef INVALID_PARAMETER_EXCEPTION_H
#define INVALID_PARAMETER_EXCEPTION_H

#include "Exception.h"

/** The InvalidParameterException class
 *
 *  Inherits from Exception class. Used in specific cases where an index
 *  is found to be out of bounds or invalid.
 *
 */
class InvalidParameterException : public Exception
{
    public:
        /** InvalidParameterException constructor.
         *
         *  Used to customize the description to allow for greater levels of error detail
         *  in specific cases.
         *
         * @param desc a constant std::string reference
         */
        InvalidParameterException(const std::string &desc);
};

#endif
