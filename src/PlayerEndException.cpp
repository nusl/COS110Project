#include "PlayerEndException.h"

PlayerEndException::PlayerEndException(const std::string &desc) : Exception("Player finishes the map with a final score of ", desc)
{
};
