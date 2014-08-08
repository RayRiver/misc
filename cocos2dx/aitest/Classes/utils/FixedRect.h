#ifndef FixedRect_h__
#define FixedRect_h__

#include "FixedVec2.h"

class FixedRect
{
public:
	Fixed x, y, w, h;

	FixedRect();
	FixedRect(const Fixed &_x, const Fixed &_y, const Fixed &_w, const Fixed &_h);
	FixedRect(const FixedPoint &_point, const FixedSize &_size);

	// 相等;
	inline bool operator==(const FixedRect &rect) const
	{
		return x==rect.x && y==rect.y && w==rect.w && h==rect.h;
	}
	inline bool operator!=(const FixedRect &rect) const
	{
		return x!=rect.x || y!=rect.y || w!=rect.w || h!=rect.h;
	}
    inline bool equals(const FixedRect &rect) const
	{
		return *this == rect;
	}

	// 包含点;
    inline bool containsPoint(const FixedPoint &point) const
	{
		return (point.x >= x && point.x <= x+w && point.y >= y && point.y <= y+h);
	}

	// 矩形相交;
    inline bool intersectsRect(const FixedRect &rect) const
	{
		return !(x+w<rect.x || x>rect.x+rect.w || y+h<rect.y || y>rect.y+rect.h);
	}
};

#endif // FixedRect_h__
