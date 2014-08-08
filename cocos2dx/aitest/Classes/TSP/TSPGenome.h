#ifndef TSPGenome_h__
#define TSPGenome_h__

#include <vector>

struct TSPGenome
{
	std::vector<int> bits;	// Ⱦɫ��;
	double fitness;			// ��Ӧ�Է���;

	TSPGenome();
	TSPGenome(const int limit);
	void dump();

	bool operator<(const TSPGenome &other)
	{
		return (this->fitness < other.fitness);
	}
};

#endif // TSPGenome_h__
