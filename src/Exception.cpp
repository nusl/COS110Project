#include "Exception.h"

Exception::Exception(const std::string& inMsg, const std::string& desc)
{
    message = inMsg;
    description = desc;
}

const std::string Exception::getMessage()
{
    return message + " Description: " + description;
}
