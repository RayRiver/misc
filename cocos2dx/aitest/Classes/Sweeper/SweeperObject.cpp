#include "SweeperObject.h"

#include "utils/helper.h"
#include "utils/Display.h"

#include "SweeperView.h"

SweeperObject * SweeperObject::create(SweeperView *view)
{
	auto obj = new SweeperObject;
	if (obj && obj->init(view))
	{

	}
	else
	{
		delete obj;
		obj = nullptr;
	}
	return obj;
}

SweeperObject::SweeperObject()
	: m_view(nullptr)
{

}

SweeperObject::~SweeperObject()
{

}

bool SweeperObject::init(SweeperView *view)
{
	m_size.x = 20;
	m_size.y = 20;

	m_rotation = 0;

	m_view = view;

	return true;
}

bool SweeperObject::update(const FixedVec2 &closestPos)
{
	FixedVec2 closestVector = closestPos - m_fixedPosition;
	closestVector.normalize();

	// 神经网络输入;
	NeuralNetInputs inputs;
	inputs.push_back(closestVector.x);	
	inputs.push_back(closestVector.y);	
	inputs.push_back(m_lookat.x);	
	inputs.push_back(m_lookat.y);	

	// 更新神经网络，获得反馈;
	NeuralNetOutputs outputs = m_brain.update(inputs);

	// 输出值赋值到左右履带;
	m_lTrack = outputs[0];
	m_rTrack = outputs[1];

	// 转动力;
	Fixed rotForce = m_lTrack - m_rTrack;

	// 转动;
	helper::clampFixed(rotForce, -0.3, 0.3);
	m_speed = m_lTrack + m_rTrack;

	// 更新角度;
	Fixed rotation = m_rotation + rotForce;
	
	// 更新视线;
	m_lookat.x = FixedSin(rotation);
	m_lookat.y = FixedCos(rotation);

	// 更新位置;
	auto delta = m_lookat * m_speed;
	FixedPoint pos = m_fixedPosition + delta;

	// 超出屏幕则让其循环;
	if (pos.x < DISPLAY->left()) pos.x = DISPLAY->right();
	if (pos.x > DISPLAY->right()) pos.x = DISPLAY->left();
	if (pos.y < DISPLAY->bottom()) pos.y = DISPLAY->top();
	if (pos.y > DISPLAY->top()) pos.y = DISPLAY->bottom();

	// 刷新位置显示;
	this->setFixedPosition(pos);

	// 刷新角度显示;
	this->setFixedRotation(rotation);

	return true;
}

bool SweeperObject::checkCollision( const FixedVec2& mine )
{
	if (mine.x >= m_fixedPosition.x-m_size.x/2 && mine.x <= m_fixedPosition.x+m_size.x/2 &&
		mine.y >= m_fixedPosition.y-m_size.y/2 && mine.y <= m_fixedPosition.y+m_size.y/2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SweeperObject::increaseFitness()
{
	// 更新基因组序列的适应值;
	auto &genome = m_brain.getGenome();
	++genome.fitness;

	// 刷新适应值显示;
	if (m_view)
	{
		m_view->updateFitness(genome.fitness);
	}
}

void SweeperObject::resetFitness()
{
	// 更新基因组序列的适应值;
	auto &genome = m_brain.getGenome();
	genome.fitness = 0;

	// 刷新适应值显示;
	if (m_view)
	{
		m_view->updateFitness(genome.fitness);
	}
}

void SweeperObject::setFixedPosition( const FixedPoint &p )
{
	m_fixedPosition = p; 

	// 刷新位置显示;
	if (m_view)
	{
		m_view->updatePosition(m_fixedPosition);
	}
}

void SweeperObject::setFixedSize( const FixedSize &size )
{
	m_size = size;

	// 刷新大小显示;
	if (m_view)
	{
		m_view->updateSize(m_size);
	}
}

void SweeperObject::setFixedRotation( const Fixed &rotation )
{
	m_rotation = rotation;

	// 刷新角度显示;
	if (m_view)
	{
		m_view->updateRotation(m_rotation);
	}
}
