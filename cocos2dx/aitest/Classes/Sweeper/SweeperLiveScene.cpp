#include "SweeperLiveScene.h"

#include "utils/Display.h"
#include "utils/helper.h"

#include "SweeperObject.h"
#include "SweeperView.h"
#include "MineObject.h"
#include "MineView.h"
#include "SweeperConstants.h"

#include "GeneticAlgorithm.h"

#include "SweeperStatisticsScene.h"

USING_NS_CC;

SweeperLiveScene::SweeperLiveScene()
	: m_generationCurrentTicks(0)
{

}

SweeperLiveScene::~SweeperLiveScene()
{
	for (auto sweeper : m_sweepers)
	{
		delete sweeper;
	}
	m_sweepers.clear();
	for (auto mine : m_mines)
	{
		delete mine;
	}
	m_mines.clear();
}

bool SweeperLiveScene::init()
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
	auto label = Label::createWithSystemFont("Switch Statistics", "Arial", 20);
	auto item = MenuItemLabel::create(label, [=](Ref *) {
		auto scene = SweeperStatisticsScene::create();
		Director::getInstance()->replaceScene(scene);
		return;
	});
	auto menu = Menu::create(item, nullptr);
	menu->setPosition(DISPLAY->right()-100, DISPLAY->top()-20);
	this->addChild(menu);

	// ��������;
	for (int i=0; i<CONSTANTS.MineNumber; ++i)
	{
		MineView *mineView = nullptr;
		mineView = MineView::create();
		this->addChild(mineView);
		auto mine = MineObject::create(mineView);
		m_mines.insert(mine);

		// �������λ��;
		mine->setFixedPosition(this->randomFixedPosition());
	}

	// ����sweeper;
	for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
	{
		SweeperView *sweeperView = nullptr;
		sweeperView = SweeperView::create();
		this->addChild(sweeperView);
		auto sweeper = SweeperObject::create(sweeperView);
		sweeper->setFixedSize(FixedSize(20, 20));
		m_sweepers.push_back(sweeper);

		// �������λ��;
		sweeper->setFixedPosition(this->randomFixedPosition());

		// ���û���;
		const auto &genes = GeneticAlgorithm::instance()->getGenome(i);
		sweeper->setGenome(genes);
	}

	// ��ʼ��ʱ��;
	this->startGeneration();

	// ע��ص�;
	this->scheduleUpdate();

	return true;
}

void SweeperLiveScene::startGeneration()
{
	// ��ʾ��ǰʱ��;
	int nGeneration = GeneticAlgorithm::instance()->getGeneration();
	char szGeneration[32];
	sprintf(szGeneration, "Generation: %d", nGeneration);
	m_labelGeneration->setString(szGeneration);

	// ��������;
	m_generationCurrentTicks = 0;

	// ��Ӧֵ���㣬������ƻ���;
	for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
	{
		auto sweeper = m_sweepers[i];

		// �������λ��;
		sweeper->setFixedPosition(this->randomFixedPosition());

		// ��Ӧֵ����;
		sweeper->resetFitness();

		// ���û���;
		const auto &genes = GeneticAlgorithm::instance()->getGenome(i);
		sweeper->setGenome(genes);
	}
}

void SweeperLiveScene::update( float dt )
{
	// ����������������ʱ��;
	if (m_generationCurrentTicks >= CONSTANTS.TicksPerGeneration)
	{
		// ������ʱ��;
		GeneticAlgorithm::instance()->epoch();

		this->startGeneration();

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

		// �����������λ��;
		bool ret = sweeper->update(closestPos);
		if (!ret)
		{
			MessageBox("update sweeper error!", "error");
			this->unscheduleAllSelectors();
			return;
		}

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

FixedPoint SweeperLiveScene::randomFixedPosition()
{
	FixedPoint p;
	p.x = DISPLAY->left() + helper::randFixed() * DISPLAY->width();
	p.y = DISPLAY->bottom() + helper::randFixed() * DISPLAY->height();
	return p;
}


