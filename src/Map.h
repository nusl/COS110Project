#ifndef MAP_H
#define MAP_H
#include <vector>
#include "Piece.h"

class Map
{
public:
	bool move(const int& fromX, const int& fromY, const int& toX, const int& toY);
	void getSpriteRelativeCoord(int& x, int& y) const;//not as generic as it could be
	void setPieceAt(const Piece* ,const int& x, const int& y);
	Piece& getHandleAt(const int& x, const int& y);//might need to be a pointer, we'll see
	
	void runAction();

private:
	std::vector<std::vector<Piece*> > map;
};

#endif
