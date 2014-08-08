#ifndef GenomeManager_h__
#define GenomeManager_h__

#include <vector>

#include "PathGenome.h"

class GenomeManager
{
public:
	GenomeManager(double crossover_rate, double muatate_rate, int pop_size, int bits_count, int gene_length);
	~GenomeManager();

	void epoch();						// ��ʼ��ʱ��;
	inline bool hasSolution() { return m_hasSolution; }
	inline int getGeneration() { return m_nGeneration; }

private:
	void createStartPopulation();		// ������ʼȺ��;
	void updateFitness();				// ����Ⱥ���ڸ��������Ӧ�Է���;
	PathGenome &selectGenome();				// ���ַ�ѡ�����;
	void crossover(const PathGenome &parent1, const PathGenome &parent2, PathGenome &child1, PathGenome &child2);	// �ӽ�;
	void mutate(PathGenome &child);			// ͻ��;
	void decode(const std::vector<int> &bits, std::vector<int> &path);

private:
	std::vector<PathGenome> m_genomes;	// ������Ⱥ��;

	int m_nGeneration;					// ʱ������;

	int m_nPopSize;						// Ⱥ�����;
	int m_nChromoLength;				// ÿ��Ⱦɫ���ж���bits;
	int m_nGeneLength;					// ÿ�������ж���bits;
	double m_crossOverRate;				// �ӽ���;
	double m_mutateRate;				// ������;

	int m_nFittestIndex;				// ������Ӧ�Ի����������;
	double m_bestFitness;				// ������Ӧ��ֵ;
	double m_totalFitness;				// ��Ӧ���ܷ�;

	bool m_hasSolution;					// �Ƿ��Ѿ��ҵ��������;


};

#endif // GenomeManager_h__
