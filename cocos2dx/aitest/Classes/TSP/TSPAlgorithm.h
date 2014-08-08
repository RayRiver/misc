#ifndef TSPAlgorithm_h__
#define TSPAlgorithm_h__

#include <vector>

#include "TSPGenome.h"

class TSPAlgorithm
{
public:
	TSPAlgorithm();
	~TSPAlgorithm();

	// 初始化;
	void init(double crossoverRate, double mutateRate, int nPopSize, int nChromoLength, int nBestToAdd);

	// 开始新时代;
	void epoch();

	// 获取当前时代;
	inline int getGeneration() { return m_nGeneration; }

	// 是否找到了解决方案;
	inline bool hasSolution() { return m_hasSolution; }

	// 获取当前时代适应值最高的路径;
	inline const TSPGenome &getFittestGenome() { return m_genomes[m_nFittestIndex]; }

private:
	// 创建开始群体;
	void createStartPopulation();

	// 杂交（部分匹配杂交）;
	void crossover(const TSPGenome &parent1, const TSPGenome &parent2, TSPGenome &child1, TSPGenome &child2);

	// 变异（交换变异）;
	void mutate(TSPGenome &chromo);

	// 适应性计算;
	void updateFitness();

	// 选择个体（赌轮法）;
	TSPGenome &selectGenome();

private:
	bool m_hasSolution;							// 是否已经找到解决方案;

	int m_nGeneration;							// 时代;

	std::vector<TSPGenome> m_genomes;			// 基因组;
	int m_nPopSize;								// 群体数量;
	int m_nChromoLength;						// 基因长度;

	double m_crossoverRate;						// 杂交率;
	double m_mutateRate;						// 变异率;

	double m_shortestRoute;						// 当前时代的最短路径;
	double m_longestRoute;						// 当前时代的最长路径;

	double m_totalFitness;						// 适应值总分（赌轮选择用）;
	int m_nFittestIndex;						// 适应值最高个体的索引;

	int m_nBestToAdd;							// 上一代精英个体（适应值最高）复制到子代的个数;

};

#endif // TSPAlgorithm_h__
