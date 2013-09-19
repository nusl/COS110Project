#include "OutOfBoundsException.h"

OutOfBoundsException::OutOfBoundsException(const std::string& desc) : Exception("Invalid index. Index was out of bounds.", desc)
{
}
