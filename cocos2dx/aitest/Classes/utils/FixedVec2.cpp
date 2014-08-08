#include "FixedVec2.h"

FixedVec2::FixedVec2()
	: x(FixedZero)
	, y(FixedZero)
{

}

FixedVec2::FixedVec2( const Fixed &_x, const Fixed &_y )
	: x(_x)
	, y(_y)
{

}

FixedVec2::FixedVec2( const FixedVec2 &other )
{
	FixedVec2::_copy(other, *this);
}

FixedVec2::~FixedVec2()
{

}

void FixedVec2::print()
{
	printf("(");
	FixedPrint(this->x);
	printf(", ");
	FixedPrint(this->y);
	printf(")");
}
