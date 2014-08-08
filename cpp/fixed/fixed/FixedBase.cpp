#include "FixedBase.h"

#include <stdio.h>

#if defined( _FIXED_USE_DOUBLE ) || defined( _FIXED_USE_FLOAT )

const Fixed FixedZero = 0.0;
const Fixed FixedOne = 1.0;

#else

const Fixed FixedZero = Fixed();
const Fixed FixedOne = Fixed(1);

Fixed::Fixed()
	: m_intPart(0)
	, m_decPart(0)
{

}

Fixed::Fixed( int i )
{
	Fixed::_fromint(i, *this);
}

Fixed::Fixed( float f )
{
	Fixed::_fromfloat(f, *this);
}

Fixed::Fixed( double f )
{
	Fixed::_fromdouble(f, *this);
}

Fixed::Fixed( const Fixed &other )
{
	Fixed::_copy(other, *this);
}

Fixed::~Fixed()
{

}

void Fixed::_print( const Fixed &f )
{
	printf("Fixed{%+d %+f}", f.m_intPart, (float)f.m_decPart / Fixed::MultiplyFactor);
}

#endif
