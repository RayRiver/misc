#include "TSPAlgorithm.h"

#include "utils/helper.h"
#include "TSPMap.h"

using namespace std;

TSPAlgorithm::TSPAlgorithm()
{
	this->init(0.0, 0.0, 1, 3, 0);
}

TSPAlgorithm::~TSPAlgorithm()
{

}

void TSPAlgorithm::init( double crossoverRate, double mutateRate, int nPopSize, int nChromoLength, int nBestToAdd )
{
	m_hasSolution = false;
	m_nGeneration = 0;
	m_shortestRoute = 999999999;
	m_totalFitness = 0;
	m_nFittestIndex = 0;

	m_crossoverRate = crossoverRate; 
	m_mutateRate = mutateRate;
	m_nPopSize = nPopSize;
	m_nChromoLength = nChromoLength;
	m_nBestToAdd = nBestToAdd;

	this->createStartPopulation();
}

void TSPAlgorithm::createStartPopulation()
{
	m_genomes.clear();

	for (int i=0; i<m_nPopSize; ++i)
	{
		m_genomes.push_back(TSPGenome(m_nChromoLength));
	}
}

void TSPAlgorithm::epoch()
{
	// ���ñ���;
	m_shortestRoute = 999999999;
	m_longestRoute = 0;
	m_totalFitness = 0;
	m_hasSolution = false;

	// ����Ⱥ����Ӧֵ;
	this->updateFitness();

	// ����ҵ�����õ�·����ֹͣ;
	if (m_shortestRoute <= TSPMap::instance()->bestPossibleRoute())
	{
		m_hasSolution = true;
		return;
	}

	// �����Ӵ�Ⱥ��;
	vector<TSPGenome> vChildren;

	// ���Ƚ���һ���ľ�Ӣ������뵽�Ӵ�Ⱥ�壨������2��������;
	for (int i=0; i<m_nBestToAdd/2*2; ++i)
	{
		vChildren.push_back(m_genomes[m_nFittestIndex]);
	}

	// �����Ӵ���������;
	while (vChildren.size() < m_nPopSize)
	{
		// ѡȡ����;
		auto &parent1 = this->selectGenome();
		auto &parent2 = this->selectGenome();

		// �����Ӵ�;
		TSPGenome child1, child2;

		// �ӽ�;
		this->crossover(parent1, parent2, child1, child2);

		// ����;
		this->mutate(child1);
		this->mutate(child2);

		// ��������Ⱥ;
		vChildren.push_back(child1);
		vChildren.push_back(child2);
	}

	// ��ʼ��ʱ��;
	m_genomes = vChildren;
	++m_nGeneration;

}

void TSPAlgorithm::crossover( const TSPGenome &parent1, const TSPGenome &parent2, TSPGenome &child1, TSPGenome &child2 )
{
	// ���Ƹ���;
	child1.bits = parent1.bits;
	child2.bits = parent2.bits;

	// δ�ﵽ�ӽ��ʻ򸸱���ͬ;
	if (helper::randFloat() > m_crossoverRate || child1.bits == child2.bits)
	{
		return;
	}

	// ѡ���ӽ���ʼ��ͽ�����;
	int begIndex = helper::randInt(0, parent1.bits.size()-2);
	int endIndex = helper::randInt(begIndex+1, parent1.bits.size()-1);

	// ���ν���ƥ��Ļ����;
	for (int pos=begIndex; pos<=endIndex; ++pos)
	{
		int gene1 = parent1.bits[pos];
		int gene2 = parent2.bits[pos];

		if (gene1 == gene2) continue;

		std::vector<int>::iterator it1, it2;
		int tmp = 0;

		// ��child1��Ѱ�ҳ�������;
		for (auto it=child1.bits.begin(); it!=child1.bits.end(); ++it)
		{
			auto gene = *it;
			if (gene == gene1)
			{
				it1 = it;
			}
			else if (gene == gene2)
			{
				it2 = it;
			}
		}
		tmp = *it1;
		*it1 = *it2;
		*it2 = tmp;
		
		// ��child2��Ѱ�ҳ�������;
		for (auto it=child2.bits.begin(); it!=child2.bits.end(); ++it)
		{
			auto gene = *it;
			if (gene == gene1)
			{
				it1 = it;
			}
			else if (gene == gene2)
			{
				it2 = it;
			}
		}
		tmp = *it1;
		*it1 = *it2;
		*it2 = tmp;
	}
}

void TSPAlgorithm::mutate( TSPGenome &chromo )
{
	// �Ƿ�ﵽ������;
	if (helper::randFloat() > m_mutateRate)
	{
		return;
	}

	// ѡ���һ������;
	int pos1 = helper::randInt(0, chromo.bits.size()-1);
	int pos2 = pos1;
	while (pos1 == pos2)
	{
		pos2 = helper::randInt(0, chromo.bits.size()-1);
	}

	// ����;
	int tmp = chromo.bits[pos1];
	chromo.bits[pos1] = chromo.bits[pos2];
	chromo.bits[pos2] = tmp;
}

void TSPAlgorithm::updateFitness()
{
	// ������·��;
	for (int i=0; i<m_nPopSize; ++i)
	{
		// ����ø����·������;
		double total = TSPMap::instance()->getTotalLength(m_genomes[i].bits);
		m_genomes[i].fitness = total;

		// ���µ�ǰʱ�����·������;
		if (total < m_shortestRoute)
		{
			m_shortestRoute = total;
			m_nFittestIndex = i;
		}

		// ���µ�ǰʱ���·������;
		if (total > m_longestRoute)
		{
			m_longestRoute = total;
		}
	}

	// ������Ӧ�Է���;
	m_totalFitness = 0;
	for (int i=0; i<m_nPopSize; ++i)
	{
		m_genomes[i].fitness = m_longestRoute - m_genomes[i].fitness;

		// ������Ӧֵ�ܷ�;
		m_totalFitness += m_genomes[i].fitness;
	}

}

TSPGenome & TSPAlgorithm::selectGenome()
{
	double fSlice = helper::randFloat() * m_totalFitness;

	double current = 0.0;
	int selectedIndex = 0;
	for (int i=0; i<m_nPopSize; ++i)
	{
		current += m_genomes[i].fitness;
		if (current > fSlice)
		{
			selectedIndex = i;
			break;
		}
	}

	return m_genomes[selectedIndex];
}

