// testmap.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>

#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

#include "Fixed.h"

unsigned int ip2int(const char *ip_string)
{
	unsigned int result = 0;

	char *pResult = (char *)&result;
	size_t index = 3;

	char *p = (char *)ip_string;
	char *pBegin = p;
	char *pEnd = p;
	while (true)	
	{
		if (!*p)
		{
			char s[16];
			memset(s, 0x00, sizeof(s));
			memcpy(s, pBegin, p-pBegin);
			int val = atoi(s);
			pResult[index] = val;
			break;
		}

		if (*p != '.')
		{
			++p;
			continue;
		}

		pEnd = p;
		char s[16];
		memset(s, 0x00, sizeof(s));
		memcpy(s, pBegin, pEnd-pBegin);
		int val = atoi(s);

		pResult[index] = val;
		--index;	
		if (index < 0)
		{
			break;
		}

		pBegin = p+1;
		pEnd = p+1;

		++p;
	}

	return result;
}

string int2ip(unsigned int ip)
{
	unsigned char val[4];
	char *p = (char *)&ip;
	for (int i=3; i>=0; --i)
	{
		unsigned char v = p[i];
		val[3-i] = v;
	}

	char ip_string[32];
	memset((char *)ip_string, 0x00, sizeof(ip_string));

	for (int i=0; i<4; ++i)
	{
		if (i == 0)
		{
			sprintf_s(ip_string, "%s%u", ip_string, val[i]);	
		}
		else
		{
			sprintf_s(ip_string, "%s.%u", ip_string, val[i]);	
		}
	}

	return string(ip_string);
}

/*
struct Section
{
	unsigned int start;
	unsigned int end;
};
list<Section> ipSections;
class CMPER  
{  
public:  
	bool operator()(const Student st1,const Student  st2) const;  
};  

void addIpSection(const char *start, const char *end)
{
	ipSections.push_back(make_pair(ip2int(start), ip2int(end)));
}
void test_ip_section()
{
	addIpSection("192.168.0.1", "192.168.0.255");

	ipSections.sort(ipSections.begin(), ipSections.end(), );



	unsigned int i1 = ip2int("192.168.0.1");
	auto s1 = int2ip(i1);

	unsigned int i2 = ip2int("192.168.2.1");
	auto s2 = int2ip(i2);

	printf("i1=%u, i2=%u\n", i1, i2);
	printf("s1=%s, s2=%s\n", s1.c_str(), s2.c_str());

}

*/
void test_map()
{
	map<int, int> m;
	m.insert(make_pair(5, 3));
	m.insert(make_pair(4, 99));
	m.insert(make_pair(3, 12));
	m.insert(make_pair(1, 1));
	m.insert(make_pair(6, 83));
	m.insert(make_pair(2, 910));

	for (auto it : m)
	{
		printf("%d = %d\n", it.first, it.second);
	}
}

void test_float()
{
	float f = 0.1f;
	float sum = 0.0f;
	for( int i=0; i<4000000; i++)
	{
		sum += f;
	}

	printf("%f\n", sum);
}

/*
void test_fixed_private(double a, double b)
{
	auto &c = Fixed(a);
	auto &d = Fixed(b);
	auto &e = Fixed();

	printf("原始数据：\n");
	Fixed::_print(c);
	Fixed::_print(d);
	printf("\n");

	printf("\n加法：");
	Fixed::_copy(c, e);
	Fixed::_add(e, d, e);
	Fixed::_print(e);

	printf("\n减法：");
	Fixed::_copy(c, e);
	Fixed::_sub(e, d, e);
	Fixed::_print(e);

	printf("\n乘法：");
	Fixed::_copy(c, e);
	Fixed::_mul(e, d, e);
	Fixed::_print(e);

	printf("\n除法：");
	Fixed::_copy(c, e);
	Fixed::_div(e, d, e);
	Fixed::_print(e);

	printf("\n开方：");
	Fixed::_copy(c, e);
	Fixed::_sqrt(e, e);
	Fixed::_print(e);

	printf("\n\n\n");
}
*/

void test_fixed(double a, double b)
{
	Fixed c = a;
	Fixed d = b;
	Fixed e = 0;

	printf("原始数据：\n");
	FixedPrint(c);
	FixedPrint(d);
	printf("\n");

	printf("\n加法：");
	e = c;
	e = e + d;
	FixedPrint(e);

	printf("\n减法：");
	e = c;
	e -= d;
	FixedPrint(e);

	printf("\n乘法：");
	e = c;
	e = d * e;
	FixedPrint(e);

	printf("\n除法：");
	e = c;
	e /= d;
	FixedPrint(e);

	printf("\n开方：");
	e = c;
	e = FixedSqrt(e);
	FixedPrint(e);

	printf("\n\n\n");
}

map<long long, long long> m_savedMap;

long long test_add(long long n)
{
	auto it = m_savedMap.find(n);
	if (it != m_savedMap.end())
	{
		return it->second;
	}

	if (n>=2)
	{
		long long n1 = test_add(n-1);
		long long n2 = test_add(n-2);
		long long result = n1+n2;
		if (result < n1 || result < n2)
		{
			int x = 0;
		}
		m_savedMap[n] = result;
		return result;
	}
	else
	{
		return 1;
	}
}

void test_hannuota(int n, int x, int y, int z)
{
	if (n == 1)
	{
		//printf("%d -> %d\n", x, z);
	}
	else
	{
		test_hannuota(n-1, x, z, y);
		//printf("%d -> %d\n", x, z);
		test_hannuota(n-1, y, x, z);
	}
}

void test_fixed_vec2()
{
	FixedVec2 v;
	v.print();
	printf(" = (%lf, %lf)\n", (double)v.x, (double)v.y);

	FixedVec2 v2;
	v2.x = 5;
	v2.y = 6.6;
	v2.print();
	printf(" = (%lf, %lf)\n", (double)v2.x, (double)v2.y);

	auto d = v.distance(v2);
	FixedPrint(d);
	printf(" = %lf\n", (double)d);

	auto d2 = v.distanceSquared(v2);
	FixedPrint(d2);
	printf(" = %lf\n", (double)d2);

	auto v3 = v2.getNormalized();
	v3.print();
	printf(" = (%lf, %lf)\n", (double)v3.x, (double)v3.y);

	auto dx = v3.lengthSquared();
	FixedPrint(dx);
	printf(" = %lf\n", (double)dx);

	auto l = v2.length();
	FixedPrint(l);
	printf(" = %lf\n", (double)l);

}

int main(int argc, char* argv[])
{
	test_fixed_vec2();

	//test_fixed(12, 1.6);
	//test_fixed(1.024*1.024, -12.8);
	//test_fixed(1024*1024, 512);

	//test_ip_section();

	//long long result = test_add(59);
	//printf("result=%I64u\n", result);

	//test_hannuota(60, 'x', 'y', 'z');

	getchar();
	return 0;
}

