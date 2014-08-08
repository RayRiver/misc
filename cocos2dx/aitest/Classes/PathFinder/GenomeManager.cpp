#include "GenomeManager.h"

#include "utils/helper.h"
#include "PathMap.h"
#include "MapManager.h"

using namespace std;

GenomeManager::GenomeManager(double crossover_rate, double muatate_rate, int pop_size, int bits_count, int gene_length)
	: m_nGeneration(0)
	, m_crossOverRate(crossover_rate)
	, m_mutateRate(muatate_rate)
	, m_nPopSize(pop_size)
	, m_nChromoLength(bits_count)
	, m_nGeneLength(gene_length)
	, m_nFittestIndex(0)
	, m_bestFitness(0.0)
	, m_totalFitness(0.0)
	, m_hasSolution(false)
{
	// ������ʼȺ��;
	this->createStartPopulation();
}

GenomeManager::~GenomeManager()
{

}

void GenomeManager::epoch()
{
	// �������и������Ӧ�Է���;
	this->updateFitness();

	// ������Ⱥ��;
	vector<PathGenome> vChildren;

	while (vChildren.size() < m_nPopSize)
	{
		// ���ַ�ѡ��2������;
		PathGenome &parent1 = this->selectGenome();
		PathGenome &parent2 = this->selectGenome();

		// �ӽ�;
		PathGenome child1, child2;
		this->crossover(parent1, parent2, child1, child2);

		// ͻ��;
		this->mutate(child1);
		this->mutate(child2);

		// ������Ⱥ��;
		vChildren.push_back(child1);
		vChildren.push_back(child2);
	}

	// ������ʱ��;
	++m_nGeneration;
	m_genomes = vChildren;
}

void GenomeManager::createStartPopulation()
{
	// ��ʼ��Ⱥ��;
	m_genomes.clear();
	for (int i=0; i<m_nPopSize; ++i)
	{
		m_genomes.push_back(PathGenome(m_nChromoLength));
	}

	// ��ʼ������;
	m_totalFitness = 0.0;
	m_nGeneration = 0;

}

void GenomeManager::updateFitness()
{
	m_hasSolution = false;

	m_nFittestIndex = 0;
	m_bestFitness = 0.0;
	m_totalFitness = 0.0;

	for (int i=0; i<m_nPopSize; ++i)
	{
		auto &genome = m_genomes[i];

		// �������;
		vector<int> path;
		this->decode(genome.bits, path);

		// ��ȡ��Ӧ�Է���;
		auto &tempMemory = MapManager::instance()->getCurrentMap().testRoute(path, genome.fitness);

		// ��������Ӧ�Է���;
		m_totalFitness += genome.fitness;

		// �洢������Ӧ�Եķ���;
		if (genome.fitness > m_bestFitness)
		{
			m_bestFitness = genome.fitness;
			m_nFittestIndex = i;
			MapManager::instance()->setMemoryMap(tempMemory);

			// �Ƿ��Ѿ��ҵ�����;
			if (genome.fitness == 1)
			{
				m_hasSolution = true;
			}
		}
	}
}

PathGenome & GenomeManager::selectGenome()
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

void GenomeManager::crossover( const PathGenome &parent1, const PathGenome &parent2, PathGenome &child1, PathGenome &child2 )
{
	// δ�ӽ���ĸ�Ļ�����ͬ;
	if (helper::randFloat() > m_crossOverRate || parent1.bits == parent2.bits)
	{
		child1 = parent1;
		child2 = parent2;
		return;
	}

	// �����ӽ�bit��ʼλ��;
	int pos = helper::randInt(0, m_nChromoLength-1);

	// ����bits;
	for (int i=0; i<pos; ++i)
	{
		child1.bits.push_back(parent1.bits[i]);
		child2.bits.push_back(parent2.bits[i]);
	}
	for (int i=pos; i<parent1.bits.size(); ++i)
	{
		child1.bits.push_back(parent2.bits[i]);
		child2.bits.push_back(parent1.bits[i]);
	}

}

void GenomeManager::mutate( PathGenome &child )
{
	for (int i=0; i<child.bits.size(); ++i)
	{
		if (helper::randFloat() < m_mutateRate)
		{
			child.bits[i] = !child.bits[i];
		}
	}
}

void GenomeManager::decode( const std::vector<int> &bits, std::vector<int> &path )
{
	for (int i=0; i<bits.size(); i+=m_nGeneLength)
	{
		vector<int> gene;
		for (int bit=0; bit<m_nGeneLength; ++bit)
		{
			gene.push_back(bits[i+bit]);
		}

		// ��������ת���ɷ������;
		int val = 0;
		int multiplier = 1;
		for (int bit=gene.size(); bit>0; --bit)
		{
			val += gene[bit-1] * multiplier;	
			multiplier *= 2;
		}

		path.push_back(val);
	}
}

