#include "TSPGenome.h"

#include <math.h>
#include <string>

#include "cocos2d.h"
USING_NS_CC;

#include <vector>
#include <set>

#include "utils/helper.h"

using namespace std;

TSPGenome::TSPGenome()
	: fitness(0) 
{

}

TSPGenome::TSPGenome(const int limit) 
	: fitness(0) 
{
	vector<int> path;
	set<int> pathset;

	// 创造随机路径;
	for (int i=0; i<limit; ++i) 
	{
		int val = helper::randInt(0, limit-1);

		while (true)
		{
			auto it = pathset.find(val);
			if (it != pathset.end())
			{
				val = helper::randInt(0, limit-1);
			}
			else
			{
				break;
			}
		}

		path.push_back(val);
		pathset.insert(val);
	}

	bits = path;
}

void TSPGenome::dump()
{
	std::string s;
	for (auto bit : bits)
	{
		char c = '0' + bit;
		s.push_back(c);	
	}
	log("%s", s.c_str());
}

