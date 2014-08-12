#include "SweeperController.h"

#include "utils/Display.h"
#include "utils/helper.h"

#include "SweeperObject.h"
#include "SweeperView.h"
#include "MineObject.h"
#include "MineView.h"
#include "SweeperConstants.h"

USING_NS_CC;

SweeperController * SweeperController::s_instance = nullptr;

SweeperController * SweeperController::instance()
{
	if (!s_instance)
	{
		s_instance = new SweeperController;
		s_instance->init();
	}
	return s_instance;
}

void SweeperController::destroy()
{
	if (s_instance)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

SweeperController::SweeperController()
	: m_generationCurrentTicks(0)
{

}

SweeperController::~SweeperController()
{

}

bool SweeperController::init()
{
	if (!BaseScene::init())
	{
		return false;
	}

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

	// 创建时代显示标签;
	m_labelGeneration = Label::createWithSystemFont("Generation: 0", "Arial", 20);
	m_labelGeneration->setAnchorPoint(Vec2(0, 1));
	m_labelGeneration->setPosition(DISPLAY->left(), DISPLAY->top());
	this->addChild(m_labelGeneration);


	this->scheduleUpdate();

	this->start();

	return true;
}

void SweeperController::clear()
{

}

void SweeperController::start()
{
	// 初始化遗传算法;
	m_algorithm.init(CONSTANTS.CrossoverRate, CONSTANTS.MutateRate, CONSTANTS.SweeperNumber, CONSTANTS.InputNumber);

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
		const auto &genes = m_algorithm.getGenome(i);
		sweeper->setGenome(genes);
	}
}

void SweeperController::update( float dt )
{
	// 满足条件，进入新时代;
	if (m_generationCurrentTicks >= CONSTANTS.TicksPerGeneration)
	{
		m_generationCurrentTicks = 0;

		// 进入新时代;
		m_algorithm.epoch();

		// 更新时代显示;
		char s[32];
		sprintf(s, "Generation: %d", m_algorithm.getGeneration());
		m_labelGeneration->setString(s);

		// 创建子代sweeper;
		for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
		{
			auto sweeper = m_sweepers[i];

			// 设置随机位置;
			sweeper->setFixedPosition(this->randomFixedPosition());

			sweeper->resetFitness();

			// 设置基因;
			const auto &genes = m_algorithm.getGenome(i);
			sweeper->setGenome(genes);
		}

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

void SweeperController::nextGeneration( float dt )
{

}

FixedPoint SweeperController::randomFixedPosition()
{
	FixedPoint p;
	p.x = DISPLAY->left() + helper::randFixed() * DISPLAY->width();
	p.y = DISPLAY->bottom() + helper::randFixed() * DISPLAY->height();
	return p;
}

