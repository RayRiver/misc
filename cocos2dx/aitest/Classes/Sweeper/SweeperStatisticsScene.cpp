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

	// ����ʱ����ʾ��ǩ;
	m_labelGeneration = Label::createWithSystemFont("Generation: 0", "Arial", 20);
	m_labelGeneration->setAnchorPoint(Vec2(0, 1));
	m_labelGeneration->setPosition(DISPLAY->left(), DISPLAY->top());
	this->addChild(m_labelGeneration);

	// �����л���ť;
	auto label = Label::createWithSystemFont("Switch Live", "Arial", 20);
	auto item = MenuItemLabel::create(label, [=](Ref *) {
		auto scene = SweeperLiveScene::create();
		Director::getInstance()->replaceScene(scene);
	});
	auto menu = Menu::create(item, nullptr);
	menu->setPosition(DISPLAY->right()-100, DISPLAY->top()-20);
	this->addChild(menu);

	// ��������;
	for (int i=0; i<CONSTANTS.MineNumber; ++i)
	{
		auto mine = MineObject::create(nullptr);
		m_mines.insert(mine);

		// �������λ��;
		mine->setFixedPosition(this->randomFixedPosition());
	}

	// ����sweeper;
	for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
	{
		auto sweeper = SweeperObject::create(nullptr);
		sweeper->setFixedSize(FixedSize(20, 20));
		m_sweepers.push_back(sweeper);

		// �������λ��;
		sweeper->setFixedPosition(this->randomFixedPosition());

		// ���û���;
		const auto &genes = GeneticAlgorithm::instance()->getGenome(i);
		sweeper->setGenome(genes);
	}

	// ����ͳ��������Ⱦ��;
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


	// ��ʼʱ��;
	this->startGeneration();

	// ����ͳ��ͼ;
	this->drawStatistics();

	// ע����»ص�;
	this->scheduleUpdate();

	return true;
}

void SweeperStatisticsScene::startGeneration()
{
	// ��ʾ��ǰʱ��;
	int nGeneration = GeneticAlgorithm::instance()->getGeneration();
	char szGeneration[32];
	sprintf(szGeneration, "Generation: %d", nGeneration);
	m_labelGeneration->setString(szGeneration);

	// ��������;
	m_generationCurrentTicks = 0;

	// ��Ӧֵ���㣬�������û���;
	for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
	{
		auto sweeper = m_sweepers[i];

		// ��Ӧֵ����;
		sweeper->resetFitness();

		// ���û���;
		const auto &genes = GeneticAlgorithm::instance()->getGenome(i);
		sweeper->setGenome(genes);
	}
}

void SweeperStatisticsScene::drawStatistics()
{
	Vec2 origin(100, 100);
	Size size(750, 400);

	// ����ͳ��ͼ����;
	m_coordinateRenderer->clear();
	m_coordinateRenderer->drawSegment(origin, Vec2(origin.x+size.width, origin.y), 1.0f, Color4F(1.0f, 1.0f, 1.0f, 0.9f));
	m_coordinateRenderer->drawSegment(origin, Vec2(origin.x, origin.y+size.height), 1.0f, Color4F(1.0f, 1.0f, 1.0f, 0.9f));

	// ������Ӧֵ����;
	m_bestFitnessRenderer->clear();
	m_averageFitnessRenderer->clear();
	m_worstFitnessRenderer->clear();

	// ��ȡͳ������;
	auto &dataList = GeneticAlgorithm::instance()->getStatisticsData();
	int count = dataList.size();

	// ��ȡ������Ӧֵ�����ֵ�����ڻ������굥λ;
	Fixed max = 0;
	for (const auto &data : dataList)
	{
		if (data.bestFitness > max)
		{
			max = data.bestFitness;
		}
	}

	// ƽ�����;
	Fixed unitWidth = size.width / count;
	Fixed unitHeight = size.height / max;

	// �����߶�;
	auto bestStart = FixedPoint(origin.x, origin.y);
	auto averageStart = FixedPoint(origin.x, origin.y);
	auto worstStart = FixedPoint(origin.x, origin.y);
	for (const auto &data : dataList)
	{
		// �������ֵ�߶�;
		{
			Fixed x = worstStart.x + unitWidth;
			Fixed y = origin.y + unitHeight * data.worstFitness;
			FixedPoint worstEnd(x, y);
			m_averageFitnessRenderer->drawSegment(Vec2(worstStart.x, worstStart.y), Vec2(worstEnd.x, worstEnd.y), 1.0f, Color4F(1.0f, 0.0f, 0.0f, 0.9f));
			worstStart = worstEnd;
		}

		// ����ƽ��ֵ�߶�;
		{
			Fixed x = averageStart.x + unitWidth;
			Fixed y = origin.y + unitHeight * data.averageFitness;
			FixedPoint averageEnd(x, y);
			m_averageFitnessRenderer->drawSegment(Vec2(averageStart.x, averageStart.y), Vec2(averageEnd.x, averageEnd.y), 1.0f, Color4F(0.0f, 0.0f, 1.0f, 0.9f));
			averageStart = averageEnd;
		}

		// ��������ֵ�߶�;
		{
			Fixed x = bestStart.x + unitWidth;
			Fixed y = origin.y + unitHeight * data.bestFitness;
			FixedPoint bestEnd(x, y);
			m_bestFitnessRenderer->drawSegment(Vec2(bestStart.x, bestStart.y), Vec2(bestEnd.x, bestEnd.y), 1.0f, Color4F(0.0f, 1.0f, 0.0f, 0.9f));
			bestStart = bestEnd;
		}
	}

	// ��ʾ��ǰʱ������Ӧֵ;
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
		// ����������������ʱ��;
		if (m_generationCurrentTicks >= CONSTANTS.TicksPerGeneration)
		{
			// ������ʱ��;
			GeneticAlgorithm::instance()->epoch();

			this->startGeneration();

			// ����ͳ��ͼ;
			this->drawStatistics();

			PROFILE_PRINT_ALL();

			return;
		}
		++m_generationCurrentTicks;



		// ��ǰʱ�����´���;
		for (auto sweeper : m_sweepers)
		{
			// ��ȡ�������;
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

			// �Ҳ�������;
			if (!pClosestMine)
			{
				// TODO: ����ô����;
				return;
			}
			const auto &closestPos = pClosestMine->getFixedPosition();

			PROFILE_BEGIN("update nn");
			// �����������λ��;
			bool ret = sweeper->update(closestPos);
			if (!ret)
			{
				MessageBox("update sweeper error!", "error");
				this->unscheduleAllSelectors();
				return;
			}
			PROFILE_END("update nn");

			// �����ײ;
			bool bCollision = sweeper->checkCollision(closestPos);
			if (bCollision)
			{
				// ������Ӧֵ;
				sweeper->increaseFitness();

				// ���ٵ��ף����������ط�����һ���µĵ���;
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
