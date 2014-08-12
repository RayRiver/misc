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
	});
	auto menu = Menu::create(item, nullptr);
	menu->setPosition(DISPLAY->right()-100, DISPLAY->top()-20);
	this->addChild(menu);


	this->scheduleUpdate();

	// ��ʼʱ��;
	this->startGeneration();

	return true;
}

void SweeperLiveScene::startGeneration()
{
	// �����Ѵ��ڵ�sweeper�͵���;
	for (auto sweeper : m_sweepers)
	{
		auto view = sweeper->getView();
		this->removeChild(view);
		delete sweeper;
	}
	m_sweepers.clear();
	for (auto mine : m_mines)
	{
		auto view = mine->getView();
		this->removeChild(view);
		delete mine;
	}
	m_mines.clear();

	// ��ʾ��ǰʱ��;
	int nGeneration = GeneticAlgorithm::instance()->getGeneration();
	char szGeneration[32];
	sprintf(szGeneration, "Generation: %d", nGeneration);
	m_labelGeneration->setString(szGeneration);

	// ��������;
	for (int i=0; i<CONSTANTS.MineNumber; ++i)
	{
		auto mineView = MineView::create();
		auto mine = MineObject::create(mineView);
		this->addChild(mineView);
		m_mines.insert(mine);

		// �������λ��;
		mine->setFixedPosition(this->randomFixedPosition());
	}

	// ����sweeper;
	for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
	{
		auto sweeperView = SweeperView::create();
		auto sweeper = SweeperObject::create(sweeperView);

		sweeper->setFixedSize(FixedSize(20, 20));

		this->addChild(sweeperView);
		m_sweepers.push_back(sweeper);

		// �������λ��;
		sweeper->setFixedPosition(this->randomFixedPosition());

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
		m_generationCurrentTicks = 0;

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

