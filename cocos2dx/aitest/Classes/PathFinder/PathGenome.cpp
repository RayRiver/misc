#include "PathGenome.h"

#include <math.h>
#include <string>

#include "cocos2d.h"
USING_NS_CC;

#include "utils/helper.h"

PathGenome::PathGenome()
	: fitness(0) 
{

}

PathGenome::PathGenome(const int bits_count) 
	: fitness(0) 
{
	// 创造随机染色体;
	for (int i=0; i<bits_count; ++i) 
	{
		bits.push_back(helper::randInt(0,1));
	}
}

void PathGenome::dump()
{
	std::string s;
	for (auto bit : bits)
	{
		char c = '0' + bit;
		s.push_back(c);	
	}
	log("%s", s.c_str());
}

