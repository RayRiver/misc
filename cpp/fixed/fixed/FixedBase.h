// ������ʵ��;
// see http://blog.sina.com.cn/s/blog_6e22f4ce0101s70i.html for details;

#ifndef FixedBase_h__
#define FixedBase_h__

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#if defined( _FIXED_USE_DOUBLE ) || defined( _FIXED_USE_FLOAT )

#include <float.h>

#if defined( _FIXED_USE_FLOAT )
	typedef float Fixed;
#else
	typedef double Fixed;
#endif

extern const Fixed FixedZero;
extern const Fixed FixedOne;

inline Fixed FixedSqrt(const Fixed &f)
{
	return ::sqrt(f);
}
inline Fixed FixedAbs(const Fixed &f)
{
	return ::fabs(f);
}
inline void FixedPrint(const Fixed &f)
{
	printf("%lf", f);
}
inline bool FixedEqual(const Fixed &f, const Fixed &other)
{
	return ::fabs(f-other) < FLT_EPSILON;
}

#else

class Fixed;
extern const Fixed FixedZero;
extern const Fixed FixedOne;

class Fixed
{
public:
	Fixed();

	Fixed(int i);
	Fixed(float f);
	Fixed(double f);

	Fixed(const Fixed &other);

	~Fixed();



	inline Fixed operator-() const
	{
		Fixed result;
		Fixed::_rev(*this, result);
		return result;
	}

	// ��ֵ����;
	inline void operator=(int i)
	{
		Fixed::_fromint(i, *this);
	}
	inline void operator=(float f)
	{
		Fixed::_fromfloat(f, *this);
	}
	inline void operator=(double f)
	{
		Fixed::_fromdouble(f, *this);
	}
	inline void operator=(const Fixed &other)
	{
		Fixed::_copy(other, *this);
	}

	// ���㷽��;
	inline Fixed operator+(const Fixed &other) const
	{
		Fixed result;
		Fixed::_add(*this, other, result);
		return result;
	}
	inline void operator+=(const Fixed &other)
	{
		Fixed::_add(*this, other, *this);
	}
	inline void operator+=(int val)
	{
		Fixed::_add(*this, Fixed(val), *this);
	}
	inline void operator+=(float val)
	{
		Fixed::_add(*this, Fixed(val), *this);
	}
	inline void operator+=(double val)
	{
		Fixed::_add(*this, Fixed(val), *this);
	}
	inline Fixed operator-(const Fixed &other) const
	{
		Fixed result;
		Fixed::_sub(*this, other, result);
		return result;
	}
	inline void operator-=(const Fixed &other)
	{
		Fixed::_sub(*this, other, *this);
	}
	inline void operator-=(int val)
	{
		Fixed::_sub(*this, Fixed(val), *this);
	}
	inline void operator-=(float val)
	{
		Fixed::_sub(*this, Fixed(val), *this);
	}
	inline void operator-=(double val)
	{
		Fixed::_sub(*this, Fixed(val), *this);
	}
	inline Fixed operator*(const Fixed &other) const
	{
		Fixed result;
		Fixed::_mul(*this, other, result);
		return result;
	}
	inline void operator*=(const Fixed &other)
	{
		Fixed::_mul(*this, other, *this);
	}
	inline void operator*=(int val)
	{
		Fixed::_mul(*this, Fixed(val), *this);
	}
	inline void operator*=(float val)
	{
		Fixed::_mul(*this, Fixed(val), *this);
	}
	inline void operator*=(double val)
	{
		Fixed::_add(*this, Fixed(val), *this);
	}
	inline Fixed operator/(const Fixed &other) const
	{
		Fixed result;
		Fixed::_div(*this, other, result);
		return result;
	}
	inline void operator/=(const Fixed &other)
	{
		Fixed::_div(*this, other, *this);
	}
	inline void operator/=(int val)
	{
		Fixed::_div(*this, Fixed(val), *this);
	}
	inline void operator/=(float val)
	{
		Fixed::_div(*this, Fixed(val), *this);
	}
	inline void operator/=(double val)
	{
		Fixed::_div(*this, Fixed(val), *this);
	}

	// ++i
	inline Fixed &operator++()
	{
		Fixed::_add(*this, FixedOne, *this);
		return *this;
	}
	// i++
	const Fixed operator++(int)
	{
		Fixed result = *this;
		Fixed::_add(*this, FixedOne, *this);
		return result;
	}
	// --i
	inline Fixed &operator--()
	{
		Fixed::_sub(*this, FixedOne, *this);
		return *this;
	}
	// i--
	const Fixed operator--(int)
	{
		Fixed result = *this;
		Fixed::_sub(*this, FixedOne, *this);
		return result;
	}

	// �ȽϷ���;
	inline bool operator==(const Fixed &other) const
	{
		return Fixed::_cmp(*this, other) == 0;
	}
	inline bool operator==(int val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) == 0;
	}
	inline bool operator==(float val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) == 0;
	}
	inline bool operator==(double val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) == 0;
	}
	inline bool operator!=(const Fixed &other) const
	{
		return Fixed::_cmp(*this, other) != 0;
	}
	inline bool operator!=(int val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) != 0;
	}
	inline bool operator!=(float val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) != 0;
	}
	inline bool operator!=(double val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) != 0;
	}
	inline bool operator<(const Fixed &other) const
	{
		return Fixed::_cmp(*this, other) < 0;
	}
	inline bool operator<(int val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) < 0;
	}
	inline bool operator<(float val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) < 0;
	}
	inline bool operator<(double val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) < 0;
	}
	inline bool operator<=(const Fixed &other) const
	{
		return Fixed::_cmp(*this, other) <= 0;
	}
	inline bool operator<=(int val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) <= 0;
	}
	inline bool operator<=(float val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) <= 0;
	}
	inline bool operator<=(double val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) <= 0;
	}
	inline bool operator>(const Fixed &other) const
	{
		return Fixed::_cmp(*this, other) > 0;
	}
	inline bool operator>(int val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) > 0;
	}
	inline bool operator>(float val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) > 0;
	}
	inline bool operator>(double val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) > 0;
	}
	inline bool operator>=(const Fixed &other) const
	{
		return Fixed::_cmp(*this, other) >= 0;
	}
	inline bool operator>=(int val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) >= 0;
	}
	inline bool operator>=(float val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) >= 0;
	}
	inline bool operator>=(double val) const
	{
		return Fixed::_cmp(*this, Fixed(val)) >= 0;
	}

	// ǿת����;
	inline operator int() const
	{
		return Fixed::_toint(*this);	
	}
	inline operator float() const
	{
		return Fixed::_tofloat(*this);	
	}
	inline operator double() const
	{
		return Fixed::_todouble(*this);	
	}


	friend inline Fixed FixedSqrt(const Fixed &f)
	{
		Fixed result;
		Fixed::_sqrt(f, result);
		return result;	
	}

	friend inline Fixed FixedAbs(const Fixed &f)
	{
		Fixed result;
		Fixed::_abs(f, result);
		return result;
	}

	friend inline void FixedPrint(const Fixed &f)
	{
		Fixed::_print(f);
	}

	friend inline bool FixedEqual(const Fixed &f, const Fixed &val)
	{
		return f == val;
	}
	friend inline bool FixedEqual(const Fixed &f, int val)
	{
		return f == Fixed(val);
	}
	friend inline bool FixedEqual(const Fixed &f, float val)
	{
		return f == Fixed(val);
	}
	friend inline bool FixedEqual(const Fixed &f, double val)
	{
		return f == Fixed(val);
	}

private:
	typedef int32_t IntPart;
	typedef int32_t DecPart;

	enum 
	{
		MultiplyFactor = 0x7FFF,    // ������������;
		ShiftFactor = 15,           // ��������λ;
		MaxInt = 2147483647,
	};

private:
	// ����һ�´���;
	inline static void _signProcess(Fixed &f)
	{
		if (f.m_intPart > 0 && f.m_decPart < 0)
		{
			// ����Ϊ����С��Ϊ������λ;
			f.m_intPart -= 1;	
			f.m_decPart += Fixed::MultiplyFactor;
		}
		else if (f.m_intPart < 0 && f.m_decPart > 0)
		{
			// ����Ϊ����С��Ϊ������λ;
			f.m_intPart += 1;
			f.m_decPart -= Fixed::MultiplyFactor;
		}
	}

	// ���㶨����������λ���λ������λ�������;
	inline static int32_t _divShiftCalc(const Fixed &f)
	{
		if (0 == f.m_intPart)
		{
			return Fixed::ShiftFactor;
		}

		int32_t den = Fixed::MaxInt / ::abs(f.m_intPart);
		for (int32_t i=31; i>0; --i)
		{
			if ( ((0x01u << i) & den) == (0x01u << i) ) 
			{
				return i;
			}
		}

		assert(false);
		return 0;
	}

	// ���������������С�����֣������������֣�;
	inline static void _decNumCalc(Fixed &f, int32_t num, int32_t den)
	{
		if (::abs(num) < Fixed::MultiplyFactor)
		{
			f.m_decPart = (num * Fixed::MultiplyFactor) / den;
			return;
		}

		int32_t div = Fixed::MaxInt / ::abs(num);

		int32_t sft = 0;
		for (int32_t i=15; i>0; --i)
		{
			if ( ((0x01u << i) & div) == (0x01u << i) )  
			{
				sft = i;                         
				break;                         
			}
		}

		f.m_decPart = (num << sft) / den;
		f.m_decPart <<= (Fixed::ShiftFactor - sft);
	}


	// �ӷ�;
	inline static void _add(const Fixed &f1, const Fixed &f2, Fixed &result) 
	{
		// С�����;
		DecPart decPart = f1.m_decPart + f2.m_decPart;

		// ��λ;
		int32_t carry = decPart / Fixed::MultiplyFactor;

		// С������;
		decPart = decPart % Fixed::MultiplyFactor;

		// �����������, ����λλ;
		IntPart intPart = f1.m_intPart + f2.m_intPart + carry;

		// ��������Ŵ���;
		result.m_intPart = intPart;
		result.m_decPart = decPart;
		Fixed::_signProcess(result);
	}

	// ����;
	inline static void _sub(const Fixed &f1, const Fixed &f2, Fixed &result)
	{
		// С�����;
		DecPart decPart = f1.m_decPart - f2.m_decPart;

		// ��λ;
		int32_t carry = decPart / Fixed::MultiplyFactor;

		// С������;
		decPart = decPart % Fixed::MultiplyFactor;

		// �����������, ����λλ;
		IntPart intPart = f1.m_intPart - f2.m_intPart + carry;

		// ��������Ŵ���;
		result.m_intPart = intPart;
		result.m_decPart = decPart;
		Fixed::_signProcess(result);
	}

	// �˷�;
	inline static void _mul(const Fixed &f1, const Fixed &f2, Fixed &result)
	{
		// ���������ǣ�������λ�˷�����¼��λ��־��������λ�˷��������Ͻ�λ��־;
		// 1. С�����ֳ�С������;
		// 2. �������ֳ�С������;
		// 3. �������ֳ���������;

		// С���������;
		int32_t micro = (f1.m_decPart * f2.m_decPart) >> Fixed::ShiftFactor;

		int32_t sft_num = Fixed::_divShiftCalc(f1);
		int32_t sft_den = Fixed::_divShiftCalc(f2);

		int32_t sft = (sft_num < sft_den) ? sft_num : sft_den;
		sft = (sft < Fixed::ShiftFactor) ? sft : Fixed::ShiftFactor;

		DecPart decPart = f1.m_intPart * ( f2.m_decPart >> (Fixed::ShiftFactor - sft) ) +
			f2.m_intPart * (f1.m_decPart >> (Fixed::ShiftFactor - sft)) +
			(micro >> (Fixed::ShiftFactor - sft));

		int32_t carry = decPart / ( Fixed::MultiplyFactor >> (Fixed::ShiftFactor - sft) );
		decPart = decPart % ( Fixed::MultiplyFactor >> (Fixed::ShiftFactor - sft) );

		decPart <<= (Fixed::ShiftFactor - sft);

		// �����������, ���Ͻ�λ;
		IntPart intPart = f1.m_intPart * f2.m_intPart + carry;

		// ��������Ŵ���;
		result.m_intPart = intPart;
		result.m_decPart = decPart;
		Fixed::_signProcess(result);
	}

	// ����;
	inline static void _div(const Fixed &f1, const Fixed &f2, Fixed &result)
	{
		int32_t sft_num = Fixed::_divShiftCalc(f1);
		int32_t sft_den = Fixed::_divShiftCalc(f2);

		int32_t sft = (sft_num < sft_den) ? sft_num : sft_den;

		IntPart num;
		DecPart den;
		if (sft < Fixed::ShiftFactor)
		{
			num = (f1.m_intPart << sft) + (f1.m_decPart >> (Fixed::ShiftFactor - sft));
			den = (f2.m_intPart << sft) + (f2.m_decPart >> (Fixed::ShiftFactor - sft));
		}
		else
		{
			num = (f1.m_intPart << Fixed::ShiftFactor) + f1.m_decPart;
			den = (f2.m_intPart << Fixed::ShiftFactor) + f2.m_decPart;
		}

		if (0 == den)
		{
			result.m_intPart = (f1.m_intPart > 0) ? Fixed::MultiplyFactor : -Fixed::MultiplyFactor;
			result.m_decPart = (f1.m_decPart > 0) ? Fixed::MultiplyFactor : -Fixed::MultiplyFactor;
			assert(false);
		}

		IntPart intPart = num / den;
		IntPart redu = num - den * intPart;

		result.m_intPart = intPart;
		Fixed::_decNumCalc(result, redu, den);
		_signProcess(result);
	}

	// ����;
	inline static void _sqrt(const Fixed &f, Fixed &result)
	{
		int32_t sft = _divShiftCalc(f);

		// ��λ����, ����λ3��1, ����λ;
		int32_t redu = sft % 2;

		IntPart tmp = (f.m_intPart << (sft - redu));

		if (sft < Fixed::ShiftFactor)
		{
			tmp += (f.m_decPart >> (Fixed::ShiftFactor + redu - sft));
		}
		else
		{
			tmp += (f.m_decPart << (sft - Fixed::ShiftFactor - redu));
		}
		// ����;
		tmp = (IntPart)::sqrt((double)tmp);

		// ������, ת���ɶ������ķ�ĸ;
		int32_t den = 1 << (sft/2); 

		result.m_intPart = tmp / den;
		Fixed::_decNumCalc(result, (tmp%den), den);
	}

	// ȡ�෴��;
	inline static void _rev(const Fixed &f, Fixed &result)
	{
		result.m_intPart = -f.m_intPart;
		result.m_decPart = -f.m_decPart;
	}

	// ����ֵ;
	inline static void _abs(const Fixed &f, Fixed &result)
	{
		result.m_intPart = ::abs(f.m_intPart);
		result.m_decPart = ::abs(f.m_decPart);
	}

	// �Ƚ�����;
	inline static int _cmp(const Fixed &f1, const Fixed &f2) 
	{
		if (f1.m_intPart > f2.m_intPart)
		{
			return 1;
		}
		else if (f1.m_intPart < f2.m_intPart) 
		{
			return -1;
		}

		if (f1.m_decPart > f2.m_decPart)
		{
			return 1;
		}
		else if (f1.m_decPart < f2.m_decPart)
		{
			return -1;
		}

		return 0;
	}

	// ����;
	inline static void _copy(const Fixed &f, Fixed &result)
	{
		result.m_intPart = f.m_intPart;
		result.m_decPart = f.m_decPart;
	}
	
	// ������������֮���ת��;
	inline static float _tofloat(const Fixed &f)
	{
		return (float)f.m_intPart + (float)f.m_decPart / Fixed::MultiplyFactor;
	}
	inline static double _todouble(const Fixed &f)
	{
		return (double)f.m_intPart + (double)f.m_decPart / Fixed::MultiplyFactor;
	}
	inline static int _toint(const Fixed &f)
	{
		return (int)f.m_intPart;
	}
	inline static void _fromfloat(float f, Fixed &result)
	{
		result.m_intPart = (IntPart)f;
		result.m_decPart = (DecPart)( (f - result.m_intPart) * Fixed::MultiplyFactor );
	}
	inline static void _fromdouble(double f, Fixed &result)
	{
		result.m_intPart = (IntPart)f;
		result.m_decPart = (DecPart)( (f - result.m_intPart) * Fixed::MultiplyFactor );
	}
	inline static void _fromint(int i, Fixed &result)
	{
		result.m_intPart = (IntPart)i;
		result.m_decPart = 0;
	}

	// ��ӡ;
	static void _print(const Fixed &f);

private:
	IntPart m_intPart;
	DecPart m_decPart;

};


// ���ؼӷ�;
inline Fixed operator+(const Fixed &f, int val)
{
	return f + Fixed(val);
}
inline Fixed operator+(int val, const Fixed &f)
{
	return f + Fixed(val);
}
inline Fixed operator+(const Fixed &f, float val)
{
	return f + Fixed(val);
}
inline Fixed operator+(float val, const Fixed &f)
{
	return f + Fixed(val);
}
inline Fixed operator+(const Fixed &f, double val)
{
	return f + Fixed(val);
}
inline Fixed operator+(double val, const Fixed &f)
{
	return f + Fixed(val);
}

// ���ؼ���;
inline Fixed operator-(const Fixed &f, int val)
{
	return f - Fixed(val);
}
inline Fixed operator-(int val, const Fixed &f)
{
	return f - Fixed(val);
}
inline Fixed operator-(const Fixed &f, float val)
{
	return f - Fixed(val);
}
inline Fixed operator-(float val, const Fixed &f)
{
	return f - Fixed(val);
}
inline Fixed operator-(const Fixed &f, double val)
{
	return f - Fixed(val);
}
inline Fixed operator-(double val, const Fixed &f)
{
	return f - Fixed(val);
}

// ���س˷�;
inline Fixed operator*(const Fixed &f, int val)
{
	return f * Fixed(val);
}
inline Fixed operator*(int val, const Fixed &f)
{
	return f * Fixed(val);
}
inline Fixed operator*(const Fixed &f, float val)
{
	return f * Fixed(val);
}
inline Fixed operator*(float val, const Fixed &f)
{
	return f * Fixed(val);
}
inline Fixed operator*(const Fixed &f, double val)
{
	return f * Fixed(val);
}
inline Fixed operator*(double val, const Fixed &f)
{
	return f * Fixed(val);
}

// ���س���;
inline Fixed operator/(const Fixed &f, int val)
{
	return f / Fixed(val);
}
inline Fixed operator/(int val, const Fixed &f)
{
	return Fixed(val) / f;
}
inline Fixed operator/(const Fixed &f, float val)
{
	return f / Fixed(val);
}
inline Fixed operator/(float val, const Fixed &f)
{
	return Fixed(val) / f;
}
inline Fixed operator/(const Fixed &f, double val)
{
	return f / Fixed(val);
}
inline Fixed operator/(double val, const Fixed &f)
{
	return Fixed(val) / f;
}

// ���ص���;
inline bool operator==(const Fixed &f, int val) 
{
	return f == Fixed(val);
}
inline bool operator==(int val, const Fixed &f)
{
	return Fixed(val) == f;
}
inline bool operator==(const Fixed &f, float val)
{
	return f == Fixed(val);
}
inline bool operator==(float val, const Fixed &f)
{
	return Fixed(val) == f;
}
inline bool operator==(const Fixed &f, double val)
{
	return f == Fixed(val);
}
inline bool operator==(double val, const Fixed &f)
{
	return Fixed(val) == f;
}

// ���ز���;
inline bool operator!=(const Fixed &f, int val) 
{
	return f != Fixed(val);
}
inline bool operator!=(int val, const Fixed &f)
{
	return Fixed(val) != f;
}
inline bool operator!=(const Fixed &f, float val)
{
	return f != Fixed(val);
}
inline bool operator!=(float val, const Fixed &f)
{
	return Fixed(val) != f;
}
inline bool operator!=(const Fixed &f, double val)
{
	return f != Fixed(val);
}
inline bool operator!=(double val, const Fixed &f)
{
	return Fixed(val) != f;
}

// ����С��;
inline bool operator<(const Fixed &f, int val) 
{
	return f < Fixed(val);
}
inline bool operator<(int val, const Fixed &f)
{
	return Fixed(val) < f;
}
inline bool operator<(const Fixed &f, float val)
{
	return f < Fixed(val);
}
inline bool operator<(float val, const Fixed &f)
{
	return Fixed(val) < f;
}
inline bool operator<(const Fixed &f, double val)
{
	return f < Fixed(val);
}
inline bool operator<(double val, const Fixed &f)
{
	return Fixed(val) < f;
}

// ����С�ڵ���;
inline bool operator<=(const Fixed &f, int val) 
{
	return f <= Fixed(val);
}
inline bool operator<=(int val, const Fixed &f)
{
	return Fixed(val) <= f;
}
inline bool operator<=(const Fixed &f, float val)
{
	return f <= Fixed(val);
}
inline bool operator<=(float val, const Fixed &f)
{
	return Fixed(val) <= f;
}
inline bool operator<=(const Fixed &f, double val)
{
	return f <= Fixed(val);
}
inline bool operator<=(double val, const Fixed &f)
{
	return Fixed(val) <= f;
}

// ���ش���;
inline bool operator>(const Fixed &f, int val) 
{
	return f > Fixed(val);
}
inline bool operator>(int val, const Fixed &f)
{
	return Fixed(val) > f;
}
inline bool operator>(const Fixed &f, float val)
{
	return f > Fixed(val);
}
inline bool operator>(float val, const Fixed &f)
{
	return Fixed(val) > f;
}
inline bool operator>(const Fixed &f, double val)
{
	return f > Fixed(val);
}
inline bool operator>(double val, const Fixed &f)
{
	return Fixed(val) > f;
}

// ���ش��ڵ���;
inline bool operator>=(const Fixed &f, int val) 
{
	return f >= Fixed(val);
}
inline bool operator>=(int val, const Fixed &f)
{
	return Fixed(val) >= f;
}
inline bool operator>=(const Fixed &f, float val)
{
	return f >= Fixed(val);
}
inline bool operator>=(float val, const Fixed &f)
{
	return Fixed(val) >= f;
}
inline bool operator>=(const Fixed &f, double val)
{
	return f >= Fixed(val);
}
inline bool operator>=(double val, const Fixed &f)
{
	return Fixed(val) >= f;
}

#endif

#endif // FixedBase_h__
