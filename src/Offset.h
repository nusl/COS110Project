#ifndef OFFSET_H
#define OFFSET_H

#include "Map.h"

/** Offset struct.
 *	FIXME: Traditional x y coordinates will not suffice since it would be prone to overflow.
 *	This is due to the fact that coordinates are unsigned.
 *	Even though this would only occur on a map that has a few billion pieces, it can still happen.
 *  @param coordinate from
 *  @param coordinate to
 */
struct Offset
{
	public:
		Offset():offsetY(0), offsetX(0){}

		Offset(const Coord& from, const Coord& to)
		{
			offsetY = static_cast<int>(to.y) - static_cast<int>(from.y);
			offsetX = static_cast<int>(to.x) - static_cast<int>(from.x);
		}
		int offsetY;
		int offsetX;
		
		Offset operator+(const Offset& rhs) const
		{
			Offset temp;
			temp.offsetY = this->offsetY + rhs.offsetY;
			temp.offsetX = this->offsetX + rhs.offsetX;
			return temp;
		}
		
		bool operator==(const Offset& rhs)
		{
			if(this->offsetY != rhs.offsetY) return false;
			if(this->offsetX != rhs.offsetX) return false;
			return true;
		}
};

#endif
