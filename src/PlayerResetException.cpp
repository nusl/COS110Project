#include "PlayerResetException.h"

PlayerResetException::PlayerResetException(const std::string &desc) : Exception("==================== Map has been reset ====================", desc)
{
};
