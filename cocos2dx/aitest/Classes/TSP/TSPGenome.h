#ifndef TSPGenome_h__
#define TSPGenome_h__

#include <vector>

struct TSPGenome
{
	std::vector<int> bits;	// 染色体;
	double fitness;			// 适应性分数;

	TSPGenome();
	TSPGenome(const int limit);
	void dump();

	bool operator<(const TSPGenome &other)
	{
		return (this->fitness < other.fitness);
	}
};

#endif // TSPGenome_h__
