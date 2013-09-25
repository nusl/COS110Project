#include "Sprite.h"

const std::string Sprite::commandList = "WASDKP";

bool Sprite::command(const char& in)
{
    bool valid = commandList.find(toupper(in), 0) != std::string::npos;

    if (!valid)
    {
        return valid;
    }

    intent = in;

    return valid; //return true if command exists
}
