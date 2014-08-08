#ifndef GeneticAlgorithm_h__
#define GeneticAlgorithm_h__

#include <vector>

#include "utils/Fixed.h"

typedef std::vector<Fixed> GeneSequence;

// 基因组;
struct Genome
{
	GeneSequence genes;							// 基因列表;
	Fixed fitness;								// 适应值;
	Genome();
	Genome(int nGeneNum);
	Genome(const GeneSequence &_genes, Fixed _fitness);
};

// 遗传算法;
class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	// 初始化算法;
	void init(const Fixed &crossoverRate, const Fixed &mutateRate, int nPopSize, int nGeneNum);

	// 获取基因;
	inline const Genome &getGenome(int index) { return m_population[index]; }

	// 开始新时代;
	void epoch();

	// 获取当前时代;
	inline int getGeneration() { return m_nGeneration; }

private:
	// 创建初始群体;
	void createStartPopulation();

	// 杂交;
	void crossover(const GeneSequence &parent1, const GeneSequence &parent2, GeneSequence &child1, GeneSequence &child2);

	// 变异;
	void mutate(GeneSequence &chromo);

	// 选择;
	Genome &select();

	// 适应值算法;
	void updateFitness();

private:
	std::vector<Genome> m_population;			// 群体列表;

	// 可调整参数;
	Fixed m_crossoverRate;						// 杂交率;
	Fixed m_mutateRate;							// 变异率;
	int m_nPopSize;								// 群体数量;
	int m_nChromoLength;						// 个体的基因数量;

	// 内部维护参数;
	int m_nGeneration;							// 时代计数;
	Fixed m_totalFitness;						// 群体总适应值;
	Fixed m_bestFitness;						// 最优个体适应值;
	Fixed m_worstFitness;						// 最差个体适应值;
	int m_fittestIndex;							// 最优个体索引;


};

#endif // GeneticAlgorithm_h__
