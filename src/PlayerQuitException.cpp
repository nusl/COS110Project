#include "PlayerQuitException.h"

PlayerQuitException::PlayerQuitException(const std::string &desc) : Exception("Player quit the game!", desc)
{
}
