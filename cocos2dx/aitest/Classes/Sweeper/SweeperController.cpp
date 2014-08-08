#include "SweeperController.h"

#include "utils/Display.h"
#include "utils/helper.h"

#include "Sweeper.h"
#include "Mine.h"
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

	// ��������;
	for (int i=0; i<CONSTANTS.MineNumber; ++i)
	{
		auto mine = Mine::create();
		this->addChild(mine);
		m_mines.insert(mine);

		// �������λ��;
		mine->setFixedPosition(this->randomFixedPosition());
	}

	// ����ʱ����ʾ��ǩ;
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
	// ��ʼ���Ŵ��㷨;
	m_algorithm.init(CONSTANTS.CrossoverRate, CONSTANTS.MutateRate, CONSTANTS.SweeperNumber, CONSTANTS.InputNumber);

	// ����sweeper;
	for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
	{
		auto sweeper = Sweeper::create();
		this->addChild(sweeper);
		m_sweepers.push_back(sweeper);

		// �������λ��;
		sweeper->setFixedPosition(this->randomFixedPosition());

		// ���û���;
		const auto &genes = m_algorithm.getGenome(i);
		sweeper->setGenome(genes);
	}
}

void SweeperController::update( float dt )
{
	// ����������������ʱ��;
	if (m_generationCurrentTicks >= CONSTANTS.TicksPerGeneration)
	{
		m_generationCurrentTicks = 0;

		// ������ʱ��;
		m_algorithm.epoch();

		// ����ʱ����ʾ;
		char s[32];
		sprintf(s, "Generation: %d", m_algorithm.getGeneration());
		m_labelGeneration->setString(s);

		// �����Ӵ�sweeper;
		for (int i=0; i<CONSTANTS.SweeperNumber; ++i)
		{
			auto sweeper = m_sweepers[i];

			// �������λ��;
			sweeper->setFixedPosition(this->randomFixedPosition());

			sweeper->resetFitness();

			// ���û���;
			const auto &genes = m_algorithm.getGenome(i);
			sweeper->setGenome(genes);
		}

		return;
	}
	++m_generationCurrentTicks;

	// ��ǰʱ�����´���;
	for (auto sweeper : m_sweepers)
	{
		// ��ȡ�������;
		Mine *pClosestMine = nullptr;
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

