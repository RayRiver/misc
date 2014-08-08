#ifndef PathGenome_h__
#define PathGenome_h__

#include <vector>

struct PathGenome
{
	std::vector<int> bits;	// 染色体;
	double fitness;			// 适应性分数;

	PathGenome();
	PathGenome(const int bits_count);
	void dump();
};

#endif // PathGenome_h__
