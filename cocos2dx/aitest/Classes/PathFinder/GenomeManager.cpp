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
	// 创建起始群体;
	this->createStartPopulation();
}

GenomeManager::~GenomeManager()
{

}

void GenomeManager::epoch()
{
	// 更新所有个体的适应性分数;
	this->updateFitness();

	// 创建子群体;
	vector<PathGenome> vChildren;

	while (vChildren.size() < m_nPopSize)
	{
		// 赌轮法选择2个父辈;
		PathGenome &parent1 = this->selectGenome();
		PathGenome &parent2 = this->selectGenome();

		// 杂交;
		PathGenome child1, child2;
		this->crossover(parent1, parent2, child1, child2);

		// 突变;
		this->mutate(child1);
		this->mutate(child2);

		// 加入子群体;
		vChildren.push_back(child1);
		vChildren.push_back(child2);
	}

	// 进入新时代;
	++m_nGeneration;
	m_genomes = vChildren;
}

void GenomeManager::createStartPopulation()
{
	// 初始化群体;
	m_genomes.clear();
	for (int i=0; i<m_nPopSize; ++i)
	{
		m_genomes.push_back(PathGenome(m_nChromoLength));
	}

	// 初始化变量;
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

		// 解码基因;
		vector<int> path;
		this->decode(genome.bits, path);

		// 获取适应性分数;
		auto &tempMemory = MapManager::instance()->getCurrentMap().testRoute(path, genome.fitness);

		// 更新总适应性分数;
		m_totalFitness += genome.fitness;

		// 存储最优适应性的方案;
		if (genome.fitness > m_bestFitness)
		{
			m_bestFitness = genome.fitness;
			m_nFittestIndex = i;
			MapManager::instance()->setMemoryMap(tempMemory);

			// 是否已经找到出口;
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
	// 未杂交或父母的基因相同;
	if (helper::randFloat() > m_crossOverRate || parent1.bits == parent2.bits)
	{
		child1 = parent1;
		child2 = parent2;
		return;
	}

	// 决定杂交bit起始位置;
	int pos = helper::randInt(0, m_nChromoLength-1);

	// 交换bits;
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

		// 基因序列转化成方向代码;
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

