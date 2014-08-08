#ifndef GenomeManager_h__
#define GenomeManager_h__

#include <vector>

#include "PathGenome.h"

class GenomeManager
{
public:
	GenomeManager(double crossover_rate, double muatate_rate, int pop_size, int bits_count, int gene_length);
	~GenomeManager();

	void epoch();						// 开始新时代;
	inline bool hasSolution() { return m_hasSolution; }
	inline int getGeneration() { return m_nGeneration; }

private:
	void createStartPopulation();		// 创建初始群体;
	void updateFitness();				// 更新群体内各个体的适应性分数;
	PathGenome &selectGenome();				// 赌轮法选择个体;
	void crossover(const PathGenome &parent1, const PathGenome &parent2, PathGenome &child1, PathGenome &child2);	// 杂交;
	void mutate(PathGenome &child);			// 突变;
	void decode(const std::vector<int> &bits, std::vector<int> &path);

private:
	std::vector<PathGenome> m_genomes;	// 基因组群体;

	int m_nGeneration;					// 时代计数;

	int m_nPopSize;						// 群体个数;
	int m_nChromoLength;				// 每个染色体有多少bits;
	int m_nGeneLength;					// 每个基因有多少bits;
	double m_crossOverRate;				// 杂交率;
	double m_mutateRate;				// 变异率;

	int m_nFittestIndex;				// 最优适应性基因组的索引;
	double m_bestFitness;				// 最优适应性值;
	double m_totalFitness;				// 适应性总分;

	bool m_hasSolution;					// 是否已经找到解决方案;


};

#endif // GenomeManager_h__
