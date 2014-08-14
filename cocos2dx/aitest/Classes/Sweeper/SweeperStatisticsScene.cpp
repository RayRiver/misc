#include "SweeperStatisticsScene.h"

#include "utils/Display.h"
#include "utils/Profiler.h"

#include "SweeperConstants.h"
#include "SweeperLiveScene.h"
#include "SweeperObject.h"
#include "MineObject.h"

USING_NS_CC;

SweeperStatisticsScene::SweeperStatisticsScene()
	: m_labelGeneration(nullptr)
	, m_generationCurrentTicks(0)
	, m_coordinateRenderer(nullptr)
	, m_averageFitnessRenderer(nullptr)
	, m_bestFitnessRenderer(nullptr)
	, m_worstFitnessRenderer(nullptr)
	, m_labelBestFitness(nullptr)
	, m_labelWorstFitness(nullptr)
	, m_labelAverageFitness(nullptr)
{

}

SweeperStatisticsScene::~SweeperStatisticsScene()
{

}

bool SweeperStatisticsScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}

	// 创建时代显示标签;
	m_labelGeneration = Label::createWithSystemFont("Generation: 0", "Arial", 20);
	m_labelGeneration->setAnchorPoint(Vec2(0, 1));
	m_labelGeneration->setPosition(DISPLAY->left(), DISPLAY->top());
	this->addChild(m_labelGeneration);

	// 创建切换按钮;
	auto label = Label::createWithSystemFont("Switch Live", "Arial", 20);
	auto item = MenuItemLabel::create(label, [=](Ref *) {
		auto scene = SweeperLiveScene::create();
		Director::getInstance()->replaceScene(scene);
	});
	auto menu = Menu::create(item, nullptr);
	menu->setPosition(DISPLAY->right()-100, DISPLAY->top()-20);
	this->addChild(menu);

	// 创建地雷;
	for (int i=0; i<CONSTANTS.MineNumber; ++i)
	{
		auto mine = MineObject::create(nullptr);
		m_mines.insert(mine);

		// 设置随机位置;
		mine->setFixedPosition(this->randomFixedPosition());
	}

	// 创建sweeper;
	for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
	{
		auto sweeper = SweeperObject::create(nullptr);
		sweeper->setFixedSize(FixedSize(20, 20));
		m_sweepers.push_back(sweeper);

		// 设置随机位置;
		sweeper->setFixedPosition(this->randomFixedPosition());

		// 设置基因;
		const auto &genes = GeneticAlgorithm::instance()->getGenome(i);
		sweeper->setGenome(genes);
	}

	// 创建统计曲线渲染器;
	m_coordinateRenderer = DrawNode::create();
	this->addChild(m_coordinateRenderer);
	m_bestFitnessRenderer = DrawNode::create();
	this->addChild(m_bestFitnessRenderer);
	m_averageFitnessRenderer = DrawNode::create();
	this->addChild(m_averageFitnessRenderer);
	m_worstFitnessRenderer = DrawNode::create();
	this->addChild(m_worstFitnessRenderer);

	m_labelBestFitness = Label::createWithSystemFont("", "Arial", 18);
	m_labelBestFitness->setPosition(200, 550);
	m_labelBestFitness->setTextColor(Color4B(0, 255, 0, 255));
	this->addChild(m_labelBestFitness);

	m_labelAverageFitness = Label::createWithSystemFont("", "Arial", 18);
	m_labelAverageFitness->setPosition(400, 550);
	m_labelAverageFitness->setTextColor(Color4B(0, 0, 255, 255));
	this->addChild(m_labelAverageFitness);

	m_labelWorstFitness = Label::createWithSystemFont("", "Arial", 18);
	m_labelWorstFitness->setPosition(600, 550);
	m_labelWorstFitness->setTextColor(Color4B(255, 0, 0, 255));
	this->addChild(m_labelWorstFitness);


	// 开始时代;
	this->startGeneration();

	// 绘制统计图;
	this->drawStatistics();

	// 注册更新回调;
	this->scheduleUpdate();

	return true;
}

void SweeperStatisticsScene::startGeneration()
{
	// 显示当前时代;
	int nGeneration = GeneticAlgorithm::instance()->getGeneration();
	char szGeneration[32];
	sprintf(szGeneration, "Generation: %d", nGeneration);
	m_labelGeneration->setString(szGeneration);

	// 计数归零;
	m_generationCurrentTicks = 0;

	// 适应值归零，重新设置基因;
	for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
	{
		auto sweeper = m_sweepers[i];

		// 适应值归零;
		sweeper->resetFitness();

		// 设置基因;
		const auto &genes = GeneticAlgorithm::instance()->getGenome(i);
		sweeper->setGenome(genes);
	}
}

void SweeperStatisticsScene::drawStatistics()
{
	Vec2 origin(100, 100);
	Size size(750, 400);

	// 绘制统计图坐标;
	m_coordinateRenderer->clear();
	m_coordinateRenderer->drawSegment(origin, Vec2(origin.x+size.width, origin.y), 1.0f, Color4F(1.0f, 1.0f, 1.0f, 0.9f));
	m_coordinateRenderer->drawSegment(origin, Vec2(origin.x, origin.y+size.height), 1.0f, Color4F(1.0f, 1.0f, 1.0f, 0.9f));

	// 绘制适应值曲线;
	m_bestFitnessRenderer->clear();
	m_averageFitnessRenderer->clear();
	m_worstFitnessRenderer->clear();

	// 获取统计数据;
	auto &dataList = GeneticAlgorithm::instance()->getStatisticsData();
	int count = dataList.size();

	// 获取最优适应值的最大值，用于绘制坐标单位;
	Fixed max = 0;
	for (const auto &data : dataList)
	{
		if (data.bestFitness > max)
		{
			max = data.bestFitness;
		}
	}

	// 平均间隔;
	Fixed unitWidth = size.width / count;
	Fixed unitHeight = size.height / max;

	// 绘制线段;
	auto bestStart = FixedPoint(origin.x, origin.y);
	auto averageStart = FixedPoint(origin.x, origin.y);
	auto worstStart = FixedPoint(origin.x, origin.y);
	for (const auto &data : dataList)
	{
		// 绘制最差值线段;
		{
			Fixed x = worstStart.x + unitWidth;
			Fixed y = origin.y + unitHeight * data.worstFitness;
			FixedPoint worstEnd(x, y);
			m_averageFitnessRenderer->drawSegment(Vec2(worstStart.x, worstStart.y), Vec2(worstEnd.x, worstEnd.y), 1.0f, Color4F(1.0f, 0.0f, 0.0f, 0.9f));
			worstStart = worstEnd;
		}

		// 绘制平均值线段;
		{
			Fixed x = averageStart.x + unitWidth;
			Fixed y = origin.y + unitHeight * data.averageFitness;
			FixedPoint averageEnd(x, y);
			m_averageFitnessRenderer->drawSegment(Vec2(averageStart.x, averageStart.y), Vec2(averageEnd.x, averageEnd.y), 1.0f, Color4F(0.0f, 0.0f, 1.0f, 0.9f));
			averageStart = averageEnd;
		}

		// 绘制最优值线段;
		{
			Fixed x = bestStart.x + unitWidth;
			Fixed y = origin.y + unitHeight * data.bestFitness;
			FixedPoint bestEnd(x, y);
			m_bestFitnessRenderer->drawSegment(Vec2(bestStart.x, bestStart.y), Vec2(bestEnd.x, bestEnd.y), 1.0f, Color4F(0.0f, 1.0f, 0.0f, 0.9f));
			bestStart = bestEnd;
		}
	}

	// 显示当前时代的适应值;
	if (count > 0)
	{
		auto &data = dataList[count-1];
		if (m_labelBestFitness)
		{
			char s[32];
			sprintf(s, "best: %.02f", (float)data.bestFitness);
			m_labelBestFitness->setString(s);
		}
		if (m_labelWorstFitness)
		{
			char s[32];
			sprintf(s, "worst: %.02f", (float)data.worstFitness);
			m_labelWorstFitness->setString(s);
		}
		if (m_labelAverageFitness)
		{
			char s[32];
			sprintf(s, "average: %.02f", (float)data.averageFitness);
			m_labelAverageFitness->setString(s);
		}
	}

}

void SweeperStatisticsScene::update(float dt)
{
	int count = CONSTANTS.TicksPerGeneration+1;

	PROFILE_RESET_ALL();

	for (int i=0; i<count; ++i)
	{
		// 满足条件，进入新时代;
		if (m_generationCurrentTicks >= CONSTANTS.TicksPerGeneration)
		{
			// 进入新时代;
			GeneticAlgorithm::instance()->epoch();

			this->startGeneration();

			// 绘制统计图;
			this->drawStatistics();

			PROFILE_PRINT_ALL();

			return;
		}
		++m_generationCurrentTicks;



		// 当前时代更新处理;
		for (auto sweeper : m_sweepers)
		{
			// 获取最近地雷;
			MineObject *pClosestMine = nullptr;
			Fixed closestDistance2 = 9999*9999;
			for (auto mine : m_mines)
			{
				const auto &minePos = mine->getFixedPosition();
				const auto &fixedPosition = sweeper->getFixedPosition();

				auto len2 = minePos.distanceSquared(fixedPosition);
				if (len2 < closestDistance2)
				{
					closestDistance2 = len2;
					pClosestMine = mine;
				}
			}

			// 找不到地雷;
			if (!pClosestMine)
			{
				// TODO: 该怎么做？;
				return;
			}
			const auto &closestPos = pClosestMine->getFixedPosition();

			PROFILE_BEGIN("update nn");
			// 更新神经网络和位置;
			bool ret = sweeper->update(closestPos);
			if (!ret)
			{
				MessageBox("update sweeper error!", "error");
				this->unscheduleAllSelectors();
				return;
			}
			PROFILE_END("update nn");

			// 检查碰撞;
			bool bCollision = sweeper->checkCollision(closestPos);
			if (bCollision)
			{
				// 更新适应值;
				sweeper->increaseFitness();

				// 销毁地雷，并在其他地方产生一个新的地雷;
				pClosestMine->setFixedPosition(this->randomFixedPosition());
			}

		}
	}
}

FixedPoint SweeperStatisticsScene::randomFixedPosition()
{
	FixedPoint p;
	p.x = DISPLAY->left() + helper::randFixed() * DISPLAY->width();
	p.y = DISPLAY->bottom() + helper::randFixed() * DISPLAY->height();
	return p;
}
