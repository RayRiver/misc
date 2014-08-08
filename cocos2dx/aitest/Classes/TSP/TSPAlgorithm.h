#ifndef TSPAlgorithm_h__
#define TSPAlgorithm_h__

#include <vector>

#include "TSPGenome.h"

class TSPAlgorithm
{
public:
	TSPAlgorithm();
	~TSPAlgorithm();

	// ��ʼ��;
	void init(double crossoverRate, double mutateRate, int nPopSize, int nChromoLength, int nBestToAdd);

	// ��ʼ��ʱ��;
	void epoch();

	// ��ȡ��ǰʱ��;
	inline int getGeneration() { return m_nGeneration; }

	// �Ƿ��ҵ��˽������;
	inline bool hasSolution() { return m_hasSolution; }

	// ��ȡ��ǰʱ����Ӧֵ��ߵ�·��;
	inline const TSPGenome &getFittestGenome() { return m_genomes[m_nFittestIndex]; }

private:
	// ������ʼȺ��;
	void createStartPopulation();

	// �ӽ�������ƥ���ӽ���;
	void crossover(const TSPGenome &parent1, const TSPGenome &parent2, TSPGenome &child1, TSPGenome &child2);

	// ���죨�������죩;
	void mutate(TSPGenome &chromo);

	// ��Ӧ�Լ���;
	void updateFitness();

	// ѡ����壨���ַ���;
	TSPGenome &selectGenome();

private:
	bool m_hasSolution;							// �Ƿ��Ѿ��ҵ��������;

	int m_nGeneration;							// ʱ��;

	std::vector<TSPGenome> m_genomes;			// ������;
	int m_nPopSize;								// Ⱥ������;
	int m_nChromoLength;						// ���򳤶�;

	double m_crossoverRate;						// �ӽ���;
	double m_mutateRate;						// ������;

	double m_shortestRoute;						// ��ǰʱ�������·��;
	double m_longestRoute;						// ��ǰʱ�����·��;

	double m_totalFitness;						// ��Ӧֵ�ܷ֣�����ѡ���ã�;
	int m_nFittestIndex;						// ��Ӧֵ��߸��������;

	int m_nBestToAdd;							// ��һ����Ӣ���壨��Ӧֵ��ߣ����Ƶ��Ӵ��ĸ���;

};

#endif // TSPAlgorithm_h__
