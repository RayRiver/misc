#ifndef GeneticAlgorithm_h__
#define GeneticAlgorithm_h__

#include <vector>

#include "utils/Fixed.h"

typedef std::vector<Fixed> GeneSequence;

// ������;
struct Genome
{
	GeneSequence genes;							// �����б�;
	Fixed fitness;								// ��Ӧֵ;
	Genome();
	Genome(int nGeneNum);
	Genome(const GeneSequence &_genes, Fixed _fitness);
};

// �Ŵ��㷨;
class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	// ��ʼ���㷨;
	void init(const Fixed &crossoverRate, const Fixed &mutateRate, int nPopSize, int nGeneNum);

	// ��ȡ����;
	inline const Genome &getGenome(int index) { return m_population[index]; }

	// ��ʼ��ʱ��;
	void epoch();

	// ��ȡ��ǰʱ��;
	inline int getGeneration() { return m_nGeneration; }

private:
	// ������ʼȺ��;
	void createStartPopulation();

	// �ӽ�;
	void crossover(const GeneSequence &parent1, const GeneSequence &parent2, GeneSequence &child1, GeneSequence &child2);

	// ����;
	void mutate(GeneSequence &chromo);

	// ѡ��;
	Genome &select();

	// ��Ӧֵ�㷨;
	void updateFitness();

private:
	std::vector<Genome> m_population;			// Ⱥ���б�;

	// �ɵ�������;
	Fixed m_crossoverRate;						// �ӽ���;
	Fixed m_mutateRate;							// ������;
	int m_nPopSize;								// Ⱥ������;
	int m_nChromoLength;						// ����Ļ�������;

	// �ڲ�ά������;
	int m_nGeneration;							// ʱ������;
	Fixed m_totalFitness;						// Ⱥ������Ӧֵ;
	Fixed m_bestFitness;						// ���Ÿ�����Ӧֵ;
	Fixed m_worstFitness;						// ��������Ӧֵ;
	int m_fittestIndex;							// ���Ÿ�������;


};

#endif // GeneticAlgorithm_h__
