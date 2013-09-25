#include "InvalidParameterException.h"

InvalidParameterException::InvalidParameterException(const std::string& desc) : Exception("Invalid parameter. Parameter was out of bounds.", desc)
{
}
