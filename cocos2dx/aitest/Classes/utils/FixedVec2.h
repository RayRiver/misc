#ifndef FixedVec2_h__
#define FixedVec2_h__

#include <math.h>

#include "FixedBase.h"

class FixedVec2
{
public:
	static const FixedVec2 ZERO;

public:
	Fixed x, y;

	FixedVec2();
	FixedVec2(const Fixed &_x, const Fixed &_y);

	// 拷贝构造;
	FixedVec2(const FixedVec2 &other);

	~FixedVec2();

	// 赋值;
	inline void operator=(const FixedVec2 &v) 
	{
		FixedVec2::_copy(v, *this);
	}

	// 向量长度;
	inline Fixed length() const 
	{
		return FixedSqrt(x * x + y * y);
	}
	inline Fixed lengthSquared() const 
	{
		return (x * x + y * y);
	}

	// 两点间距离;
	inline Fixed distance(const FixedVec2& v) const
	{
		Fixed dx = v.x - x;
		Fixed dy = v.y - y;
		return FixedSqrt(dx * dx + dy * dy);
	}
	inline Fixed distanceSquared(const FixedVec2& v) const
	{
		Fixed dx = v.x - x;
		Fixed dy = v.y - y;
		return (dx * dx + dy * dy);
	}

	// 规格化;
	inline void normalize()
	{
		FixedVec2::_normalize(*this, *this);
	}
	inline FixedVec2 getNormalized()
	{
		FixedVec2 result;
		FixedVec2::_normalize(*this, result);
		return result;
	}

	// 运算;
	inline FixedVec2 operator+(const FixedVec2 &v) const
	{
		FixedVec2 result;
		FixedVec2::_add(*this, v, result);
		return result;
	}
	inline void operator+=(const FixedVec2 &v)
	{
		FixedVec2::_add(*this, v, *this);
	}

	inline FixedVec2 operator-(const FixedVec2 &v) const
	{
		FixedVec2 result;
		FixedVec2::_sub(*this, v, result);
		return result;
	}
	inline void operator-=(const FixedVec2 &v)
	{
		FixedVec2::_sub(*this, v, *this);
	}

	inline FixedVec2 operator*(const Fixed &f) const
	{
		FixedVec2 result;
		FixedVec2::_scale(*this, f, result);
		return result;
	}
	inline void operator*=(const Fixed &f)
	{
		FixedVec2::_scale(*this, f, *this);
	}
	inline void operator*=(int val)
	{
		FixedVec2::_scale(*this, Fixed(val), *this);
	}
	inline void operator*=(float val)
	{
		FixedVec2::_scale(*this, Fixed(val), *this);
	}
	inline void operator*=(double val)
	{
		FixedVec2::_scale(*this, Fixed(val), *this);
	}

	inline FixedVec2 operator/(const Fixed &f) const
	{
		if (FixedEqual(f, FixedZero)) assert(false);
		FixedVec2 result;
		FixedVec2::_scale(*this, f, result);
		return result;
	}
	inline void operator/=(const Fixed &f)
	{
		if (FixedEqual(f, FixedZero)) assert(false);
		FixedVec2::_scale(*this, f, *this);
	}
	inline void operator/=(int val)
	{
		if (val == 0) assert(false);
		FixedVec2::_scale(*this, Fixed(val), *this);
	}
	inline void operator/=(float val)
	{
		if (val == 0) assert(false);
		FixedVec2::_scale(*this, Fixed(val), *this);
	}
	inline void operator/=(double val)
	{
		if (val == 0) assert(false);
		FixedVec2::_scale(*this, Fixed(val), *this);
	}

	friend inline FixedVec2 operator*(const Fixed &f, const FixedVec2 &v)
	{
		FixedVec2 result;
		FixedVec2::_scale(v, f, result);
		return result;
	}
	friend inline FixedVec2 operator*(int val, const FixedVec2 &v)
	{
		FixedVec2 result;
		FixedVec2::_scale(v, Fixed(val), result);
		return result;
	}
	friend inline FixedVec2 operator*(float val, const FixedVec2 &v)
	{
		FixedVec2 result;
		FixedVec2::_scale(v, Fixed(val), result);
		return result;
	}
	friend inline FixedVec2 operator*(double val, const FixedVec2 &v)
	{
		FixedVec2 result;
		FixedVec2::_scale(v, Fixed(val), result);
		return result;
	}

	// 比较;
	inline bool operator==(const FixedVec2 &v) const
	{
		return FixedVec2::_equal(*this, v);
	}
	inline bool operator!=(const FixedVec2 &v) const
	{
		return !FixedVec2::_equal(*this, v);
	}

	// 打印;
	void print();

private:
	// 复制;
	inline static void _copy(const FixedVec2 &v, FixedVec2 &result)
	{
		result.x = v.x;
		result.y = v.y;
	}

	// 运算;
	inline static void _add(const FixedVec2 &v1, const FixedVec2 &v2, FixedVec2 &result)
	{
		result.x = v1.x + v2.x;
		result.y = v1.y + v2.y;
	}
	inline static void _sub(const FixedVec2 &v1, const FixedVec2 &v2, FixedVec2 &result)
	{
		result.x = v1.x - v2.x;
		result.y = v1.y - v2.y;
	}
	inline static void _scale(const FixedVec2 &v, const Fixed &f, FixedVec2 &result)
	{
		result.x = v.x * f;
		result.y = v.y * f;
	}


	// 比较;
	inline static bool _equal(const FixedVec2 &v1, const FixedVec2 &v2)
	{
		if (v1.x == v2.x && v1.y == v2.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline static void _normalize(const FixedVec2 &v, FixedVec2 &result)
	{
		Fixed n = v.x * v.x + v.y * v.y;

		// Already normalized.
		if (n == FixedOne)
		{
			if (result != v) result = v;
			return;
		}

		n = FixedSqrt(n);

		// Too close to zero.
		if (FixedEqual(n, FixedZero))
		{
			return;
		}

		n = 1.0 / n;
		result.x = v.x * n;
		result.y = v.y * n;	
	}
};

typedef FixedVec2 FixedPoint;
typedef FixedVec2 FixedSize;

#endif // FixedVec2_h__
