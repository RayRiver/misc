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

	// ����������;
	NeuralNetInputs inputs;
	inputs.push_back(closestVector.x);	
	inputs.push_back(closestVector.y);	
	inputs.push_back(m_lookat.x);	
	inputs.push_back(m_lookat.y);	

	// ���������磬��÷���;
	NeuralNetOutputs outputs = m_brain.update(inputs);

	// ���ֵ��ֵ�������Ĵ�;
	m_lTrack = outputs[0];
	m_rTrack = outputs[1];

	// ת����;
	Fixed rotForce = m_lTrack - m_rTrack;

	// ת��;
	helper::clampFixed(rotForce, -0.3, 0.3);
	m_speed = m_lTrack + m_rTrack;

	// ���½Ƕ�;
	Fixed rotation = m_rotation + rotForce;
	
	// ��������;
	m_lookat.x = FixedSin(rotation);
	m_lookat.y = FixedCos(rotation);

	// ����λ��;
	auto delta = m_lookat * m_speed;
	FixedPoint pos = m_fixedPosition + delta;

	// ������Ļ������ѭ��;
	if (pos.x < DISPLAY->left()) pos.x = DISPLAY->right();
	if (pos.x > DISPLAY->right()) pos.x = DISPLAY->left();
	if (pos.y < DISPLAY->bottom()) pos.y = DISPLAY->top();
	if (pos.y > DISPLAY->top()) pos.y = DISPLAY->bottom();

	// ˢ��λ����ʾ;
	this->setFixedPosition(pos);

	// ˢ�½Ƕ���ʾ;
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
	// ���»��������е���Ӧֵ;
	auto &genome = m_brain.getGenome();
	++genome.fitness;

	// ˢ����Ӧֵ��ʾ;
	if (m_view)
	{
		m_view->updateFitness(genome.fitness);
	}
}

void SweeperObject::resetFitness()
{
	// ���»��������е���Ӧֵ;
	auto &genome = m_brain.getGenome();
	genome.fitness = 0;

	// ˢ����Ӧֵ��ʾ;
	if (m_view)
	{
		m_view->updateFitness(genome.fitness);
	}
}

void SweeperObject::setFixedPosition( const FixedPoint &p )
{
	m_fixedPosition = p; 

	// ˢ��λ����ʾ;
	if (m_view)
	{
		m_view->updatePosition(m_fixedPosition);
	}
}

void SweeperObject::setFixedSize( const FixedSize &size )
{
	m_size = size;

	// ˢ�´�С��ʾ;
	if (m_view)
	{
		m_view->updateSize(m_size);
	}
}

void SweeperObject::setFixedRotation( const Fixed &rotation )
{
	m_rotation = rotation;

	// ˢ�½Ƕ���ʾ;
	if (m_view)
	{
		m_view->updateRotation(m_rotation);
	}
}
