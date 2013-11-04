#ifndef VOID_BLOCK_H
#define VOID_BLOCK_H

#include "ImmovablePiece.h"
#include <iostream>
class Map;

class VoidBlock : public ImmovablePiece
{
	public:
		VoidBlock
		(
				Map* m
		):
		ImmovablePiece
		(0
		,0
		,' '//inState
		,' '//inType
		,false//inMoveOnto
		)
		,map(m)
		{}

		virtual void iAttackedYou(Piece* const assailant, unsigned int& damage, Map* caller){}

		virtual void decreaseLife(const unsigned &howMuch, Map *caller){}

		virtual void action(const Coord &coord, Map *caller){}

		virtual const char getState() const
		{
			Coord c = map->getCoordOf(this);

			// Check to my left
			if (map->inBoundary(Coord(c.y, c.x - 1)))
			{
				if (!(typeid(*map->getHandleAt(Coord(c.y, c.x - 1))) == typeid(VoidBlock)))
				{
					return '|';
				}
			}
			else
			{
				return '|';
			}

			// Check to my right
			if (map->inBoundary(Coord(c.y, c.x + 1)))
			{
				if (!(typeid(*map->getHandleAt(Coord(c.y, c.x + 1))) == typeid(VoidBlock)))
				{
					return '|';
				}
			}
			else
			{
				return '|';
			}

			// Check below me
			if (map->inBoundary(Coord(c.y + 1, c.x)))
			{
				if (!(typeid(*map->getHandleAt(Coord(c.y + 1, c.x))) == typeid(VoidBlock)))
				{
					return '_';
				}
			}
			else
			{
				return '_';
			}

			// Check above me
			if (map->inBoundary(Coord(c.y - 1, c.x)))
			{
				if (!(typeid(*map->getHandleAt(Coord(c.y - 1, c.x))) == typeid(VoidBlock)))
				{
					return '-';
				}
			}
			else
			{
				return '-';
			}

			return ' ';
		}

	private:

		Map* map;
};

#endif
