#ifndef TimeVal_h__
#define TimeVal_h__

class TimeVal
{
public:
	static TimeVal Zero;

public:
	long sec;
	long usec;

	TimeVal(long _sec = 0, long _usec = 0);
	TimeVal(const TimeVal &other);

	inline long to_us() const
	{
		return sec*1000000 + usec;
	}

	inline long to_ms() const
	{
		return sec*1000 + usec/1000;
	}

	inline float to_s() const
	{
		return sec + usec/1000000.0;
	}

	static void getTimeVal(TimeVal &tv);

	static inline void add(const TimeVal &tv1, const TimeVal &tv2, TimeVal &result)
	{
		result.sec = tv1.sec + tv2.sec;
		result.usec = tv1.usec + tv2.usec;
		TimeVal::_adjust(result);
	}

	static inline void sub(const TimeVal &tv1, const TimeVal &tv2, TimeVal &result)
	{
		result.sec = tv1.sec - tv2.sec;
		result.usec = tv1.usec - tv2.usec;
		TimeVal::_adjust(result);
	}

	inline void operator=(const TimeVal &other)
	{
		this->sec = other.sec;
		this->usec = other.usec;
	}
	inline bool operator==(const TimeVal &other) const
	{
		return TimeVal::_compare(*this, other) == 0;
	}
	inline bool operator!=(const TimeVal &other) const
	{
		return TimeVal::_compare(*this, other) != 0;
	}
	inline bool operator>(const TimeVal &other) const
	{
		return TimeVal::_compare(*this, other) > 0;
	}
	inline bool operator>=(const TimeVal &other) const
	{
		return TimeVal::_compare(*this, other) >= 0;
	}
	inline bool operator<(const TimeVal &other) const
	{
		return TimeVal::_compare(*this, other) < 0;
	}
	inline bool operator<=(const TimeVal &other) const
	{
		return TimeVal::_compare(*this, other) <= 0;
	}

private:
	static inline void _adjust(TimeVal &result)
	{
		// 进位;
		if (result.usec > 1000000)
		{
			long carry = result.usec / 1000000;
			result.sec += carry;
			result.usec = result.usec % 1000000;
		}
		else if (result.usec < -1000000)
		{
			long carry = (-result.usec) / 1000000;
			result.sec -= carry;
			result.usec = -((-result.usec) % 1000000);
		}

		// 统一符号;
		if (result.sec > 0 && result.usec < 0)
		{
			--result.sec;
			result.usec = 1000000 + result.usec;
		}
		else if (result.sec < 0 && result.usec > 0)
		{
			++result.sec;
			result.usec = result.usec - 1000000;
		}
	}

	static inline int _compare(const TimeVal &tv1, const TimeVal &tv2)
	{
		if (tv1.sec == tv2.sec && tv1.usec == tv2.usec)
		{
			return 0;
		}
		else if (tv1.sec > tv2.sec || (tv1.sec == tv2.sec && tv1.usec > tv2.usec))
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
};

#endif // TimeVal_h__
