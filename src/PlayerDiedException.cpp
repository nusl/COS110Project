#include "PlayerDiedException.h"

PlayerDiedException::PlayerDiedException(const std::string &desc) : Exception("Player lost the game by dying!", desc)
{
};
