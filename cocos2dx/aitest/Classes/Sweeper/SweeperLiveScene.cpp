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

	// 创建时代显示标签;
	m_labelGeneration = Label::createWithSystemFont("Generation: 0", "Arial", 20);
	m_labelGeneration->setAnchorPoint(Vec2(0, 1));
	m_labelGeneration->setPosition(DISPLAY->left(), DISPLAY->top());
	this->addChild(m_labelGeneration);

	// 创建切换按钮;
	auto label = Label::createWithSystemFont("Switch Statistics", "Arial", 20);
	auto item = MenuItemLabel::create(label, [=](Ref *) {
		auto scene = SweeperStatisticsScene::create();
		Director::getInstance()->replaceScene(scene);
	});
	auto menu = Menu::create(item, nullptr);
	menu->setPosition(DISPLAY->right()-100, DISPLAY->top()-20);
	this->addChild(menu);


	this->scheduleUpdate();

	// 开始时代;
	this->startGeneration();

	return true;
}

void SweeperLiveScene::startGeneration()
{
	// 销毁已存在的sweeper和地雷;
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

	// 显示当前时代;
	int nGeneration = GeneticAlgorithm::instance()->getGeneration();
	char szGeneration[32];
	sprintf(szGeneration, "Generation: %d", nGeneration);
	m_labelGeneration->setString(szGeneration);

	// 创建地雷;
	for (int i=0; i<CONSTANTS.MineNumber; ++i)
	{
		auto mineView = MineView::create();
		auto mine = MineObject::create(mineView);
		this->addChild(mineView);
		m_mines.insert(mine);

		// 设置随机位置;
		mine->setFixedPosition(this->randomFixedPosition());
	}

	// 创建sweeper;
	for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
	{
		auto sweeperView = SweeperView::create();
		auto sweeper = SweeperObject::create(sweeperView);

		sweeper->setFixedSize(FixedSize(20, 20));

		this->addChild(sweeperView);
		m_sweepers.push_back(sweeper);

		// 设置随机位置;
		sweeper->setFixedPosition(this->randomFixedPosition());

		// 设置基因;
		const auto &genes = GeneticAlgorithm::instance()->getGenome(i);
		sweeper->setGenome(genes);
	}
}

void SweeperLiveScene::update( float dt )
{
	// 满足条件，进入新时代;
	if (m_generationCurrentTicks >= CONSTANTS.TicksPerGeneration)
	{
		m_generationCurrentTicks = 0;

		// 进入新时代;
		GeneticAlgorithm::instance()->epoch();

		this->startGeneration();

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

		// 更新神经网络和位置;
		bool ret = sweeper->update(closestPos);
		if (!ret)
		{
			MessageBox("update sweeper error!", "error");
			this->unscheduleAllSelectors();
			return;
		}

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

FixedPoint SweeperLiveScene::randomFixedPosition()
{
	FixedPoint p;
	p.x = DISPLAY->left() + helper::randFixed() * DISPLAY->width();
	p.y = DISPLAY->bottom() + helper::randFixed() * DISPLAY->height();
	return p;
}

