#include "Exception.h"

Exception::Exception(const std::string& inMsg, const std::string& desc)
{
    message = inMsg;
    description = desc;
}

const std::string& Exception::getMessage() const
{
    return message;
}

const std::string& Exception::getDescription() const
{
    return description;
}
