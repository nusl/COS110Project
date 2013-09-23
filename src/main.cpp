// Incomplete main file
// Will change!

#include <iostream>
#include "Game.h"
#include "Mage.h"

int main()
{
	Piece *test = new Mage();
	std::cout << test->getType() << std::endl;
	Game g;
    g.start();
}
