#include "FixedRect.h"

FixedRect::FixedRect()
	: x(0)
	, y(0)
	, w(0)
	, h(0)
{

}

FixedRect::FixedRect( const Fixed &_x, const Fixed &_y, const Fixed &_w, const Fixed &_h )
	: x(_x)
	, y(_y)
	, w(_w)
	, h(_h)
{

}

FixedRect::FixedRect( const FixedPoint &_point, const FixedSize &_size )
	: x(_point.x)
	, y(_point.y)
	, w(_size.x)
	, h(_size.y)
{

}
