#ifndef PathGenome_h__
#define PathGenome_h__

#include <vector>

struct PathGenome
{
	std::vector<int> bits;	// Ⱦɫ��;
	double fitness;			// ��Ӧ�Է���;

	PathGenome();
	PathGenome(const int bits_count);
	void dump();
};

#endif // PathGenome_h__
