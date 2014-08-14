#include "TimeVal.h"

#include "cocos2d.h"
USING_NS_CC;

TimeVal TimeVal::Zero = TimeVal(0, 0);

void TimeVal::getTimeVal( TimeVal &tv )
{
	LARGE_INTEGER liTime, liFreq;
	QueryPerformanceFrequency( &liFreq );
	QueryPerformanceCounter( &liTime );
	tv.sec  = (long)( liTime.QuadPart / liFreq.QuadPart );
	tv.usec = (long)( liTime.QuadPart * 1000000.0 / liFreq.QuadPart - tv.sec * 1000000.0 );
}

TimeVal::TimeVal( long _sec /*= 0*/, long _usec /*= 0*/ )
	: sec(_sec)
	, usec(_usec)
{
	TimeVal::_adjust(*this);
}

TimeVal::TimeVal( const TimeVal &other )
	: sec(other.sec)
	, usec(other.usec)
{

}
