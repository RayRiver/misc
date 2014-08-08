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
	// 重置变量;
	m_shortestRoute = 999999999;
	m_longestRoute = 0;
	m_totalFitness = 0;
	m_hasSolution = false;

	// 更新群体适应值;
	this->updateFitness();

	// 如果找到了最好的路径则停止;
	if (m_shortestRoute <= TSPMap::instance()->bestPossibleRoute())
	{
		m_hasSolution = true;
		return;
	}

	// 创建子代群体;
	vector<TSPGenome> vChildren;

	// 首先将上一代的精英个体加入到子代群体（必须是2个倍数）;
	for (int i=0; i<m_nBestToAdd/2*2; ++i)
	{
		vChildren.push_back(m_genomes[m_nFittestIndex]);
	}

	// 创建子代其他个体;
	while (vChildren.size() < m_nPopSize)
	{
		// 选取父代;
		auto &parent1 = this->selectGenome();
		auto &parent2 = this->selectGenome();

		// 创建子代;
		TSPGenome child1, child2;

		// 杂交;
		this->crossover(parent1, parent2, child1, child2);

		// 变异;
		this->mutate(child1);
		this->mutate(child2);

		// 加入新种群;
		vChildren.push_back(child1);
		vChildren.push_back(child2);
	}

	// 开始新时代;
	m_genomes = vChildren;
	++m_nGeneration;

}

void TSPAlgorithm::crossover( const TSPGenome &parent1, const TSPGenome &parent2, TSPGenome &child1, TSPGenome &child2 )
{
	// 复制父代;
	child1.bits = parent1.bits;
	child2.bits = parent2.bits;

	// 未达到杂交率或父辈相同;
	if (helper::randFloat() > m_crossoverRate || child1.bits == child2.bits)
	{
		return;
	}

	// 选择杂交开始点和结束点;
	int begIndex = helper::randInt(0, parent1.bits.size()-2);
	int endIndex = helper::randInt(begIndex+1, parent1.bits.size()-1);

	// 依次交换匹配的基因对;
	for (int pos=begIndex; pos<=endIndex; ++pos)
	{
		int gene1 = parent1.bits[pos];
		int gene2 = parent2.bits[pos];

		if (gene1 == gene2) continue;

		std::vector<int>::iterator it1, it2;
		int tmp = 0;

		// 从child1中寻找出来交换;
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
		
		// 从child2中寻找出来交换;
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
	// 是否达到变异率;
	if (helper::randFloat() > m_mutateRate)
	{
		return;
	}

	// 选择第一个基因;
	int pos1 = helper::randInt(0, chromo.bits.size()-1);
	int pos2 = pos1;
	while (pos1 == pos2)
	{
		pos2 = helper::randInt(0, chromo.bits.size()-1);
	}

	// 交换;
	int tmp = chromo.bits[pos1];
	chromo.bits[pos1] = chromo.bits[pos2];
	chromo.bits[pos2] = tmp;
}

void TSPAlgorithm::updateFitness()
{
	// 计算总路径;
	for (int i=0; i<m_nPopSize; ++i)
	{
		// 计算该个体的路径长度;
		double total = TSPMap::instance()->getTotalLength(m_genomes[i].bits);
		m_genomes[i].fitness = total;

		// 更新当前时代最短路径长度;
		if (total < m_shortestRoute)
		{
			m_shortestRoute = total;
			m_nFittestIndex = i;
		}

		// 更新当前时代最长路径长度;
		if (total > m_longestRoute)
		{
			m_longestRoute = total;
		}
	}

	// 计算适应性分数;
	m_totalFitness = 0;
	for (int i=0; i<m_nPopSize; ++i)
	{
		m_genomes[i].fitness = m_longestRoute - m_genomes[i].fitness;

		// 更新适应值总分;
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

