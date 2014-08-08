#include "GeneticAlgorithm.h"

#include "utils/helper.h"

using namespace std;

Genome::Genome()
	: fitness(0.0)
{

}

Genome::Genome( const GeneSequence &_genes, Fixed _fitness )
	: genes(_genes)
	, fitness(_fitness)
{
	
}

Genome::Genome( int nGeneNum )
	: fitness(0)
{
	// �������Ⱦɫ��;
	for (int i=0; i<nGeneNum; ++i) 
	{
		genes.push_back(helper::randClamped());
	}
}

GeneticAlgorithm::GeneticAlgorithm()
{
	this->init(0.0, 0.0, 1, 1);
}

GeneticAlgorithm::~GeneticAlgorithm()
{

}

void GeneticAlgorithm::init( const Fixed &crossoverRate, const Fixed &mutateRate, int nPopSize, int nGeneNum )
{
	m_crossoverRate = crossoverRate;
	m_mutateRate = mutateRate;
	m_nPopSize = nPopSize;
	m_nChromoLength = nGeneNum;

	m_nGeneration = 0;
	m_totalFitness = 0;
	m_bestFitness = 0;
	m_worstFitness = 999999;
	m_fittestIndex = 0;

	m_population.clear();
	this->createStartPopulation();
}

void GeneticAlgorithm::createStartPopulation()
{
	// ��ʼ��Ⱥ��;
	m_population.clear();
	for (int i=0; i<m_nPopSize; ++i)
	{
		m_population.push_back(Genome(m_nChromoLength));
	}
}

void GeneticAlgorithm::epoch()
{
	// ������Ӧֵ;
	this->updateFitness();

	// �����Ӵ�Ⱥ��;
	vector<Genome> vChildren;

	// TODO: ѡ��Ӣ�����Ӵ�;


	// ѭ�������Ӵ�����;
	while (vChildren.size() < m_nPopSize) 
	{
		// ѡ�񸸴�;
		GeneSequence &parent1 = this->select().genes;
		GeneSequence &parent2 = this->select().genes;

		// �����Ӵ�;
		GeneSequence child1;
		GeneSequence child2;

		// �ӽ�;
		this->crossover(parent1, parent2, child1, child2);

		// ����;
		this->mutate(child1);
		this->mutate(child2);

		// �����Ӵ�Ⱥ��;
		vChildren.push_back(Genome(child1, 0));
		vChildren.push_back(Genome(child2, 0));
	}

	// ������ʱ��;
	m_population = vChildren;
	++m_nGeneration;

}

void GeneticAlgorithm::crossover( const GeneSequence &parent1, const GeneSequence &parent2, GeneSequence &child1, GeneSequence &child2 )
{
	// δ�ﵽ�ӽ��ʻ�ĸ��ͬ;
	if (helper::randFixed() < m_crossoverRate || parent1 == parent2)
	{
		child1 = parent1;
		child2 = parent2;
		return;
	}

	// �����ӽ���;
	int pos = helper::randFixedInt(0, m_nChromoLength-1);

	// �ӽ�;
	for (int i=0; i<pos; ++i)
	{
		child1.push_back(parent1[i]);
		child2.push_back(parent2[i]);
	}
	for (int i=pos; i<parent1.size(); ++i)
	{
		child1.push_back(parent2[i]);
		child2.push_back(parent1[i]);
	}

}

void GeneticAlgorithm::mutate( GeneSequence &chromo )
{
	for (int i=0; i<chromo.size(); ++i)
	{
		if (helper::randFixed() < m_mutateRate)
		{
			chromo[i] += (helper::randFixedClamped() * 0.3);
		}
	}
}

Genome & GeneticAlgorithm::select()
{
	Fixed slice = helper::randFixed() * m_totalFitness;

	Fixed total = 0.0;
	for (int i=0; i<m_nPopSize; ++i)
	{
		total += m_population[i].fitness;
		if (total >= slice)
		{
			return m_population[i];
		}
	}

	return m_population[0];
}

void GeneticAlgorithm::updateFitness()
{
	m_totalFitness = 0.0;
	Fixed highest = 0;
	Fixed lowest = 9999999;

	for (int i=0; i<m_nPopSize; ++i)
	{
		auto &genome = m_population[i];

		// ��������ֵ������;
		if (genome.fitness > highest)
		{
			highest = genome.fitness;
			m_fittestIndex = i;
			m_bestFitness = highest;
		}

		// �������ֵ;
		if (genome.fitness < lowest)
		{
			lowest = genome.fitness;
			m_worstFitness = lowest;
		}

		m_totalFitness += genome.fitness;
	}
}


