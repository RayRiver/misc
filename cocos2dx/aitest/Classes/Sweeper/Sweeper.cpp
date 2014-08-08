#include "Sweeper.h"

#include "utils/helper.h"
#include "utils/Display.h"

USING_NS_CC;

bool Sweeper::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	m_size.x = 20;
	m_size.y = 20;

	m_rotation = 0;

	// ������Ⱦ�ڵ�;
	m_drawnode = DrawNode::create();	
	this->addChild(m_drawnode);

	// ����ʵ��;
	Vec2 verts[] = 
	{ 
		Vec2((float)-m_size.x/2, (float)-m_size.y/2), 
		Vec2((float) m_size.x/2, (float)-m_size.y/2), 
		Vec2((float) m_size.x/2, (float) m_size.y/2), 
		Vec2((float)-m_size.x/2, (float) m_size.y/2) 
	};
	m_drawnode->drawPolygon(verts, 4, Color4F(0.0f, 1.0f, 0.0f, 0.5f), 1.0f, Color4F(0.0f, 1.0f, 0.0f, 0.5f));

	// ������Ӧֵ��ʾ��ǩ;
	m_label = Label::createWithSystemFont("", "Arial", 12);
	m_label->setPosition(0, 20);
	this->addChild(m_label);

	return true;
}

bool Sweeper::update(const FixedVec2 &closestPos)
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
	m_rotation -= rotForce;
	
	// ��������;
	m_lookat.x = -FixedSin(m_rotation);
	m_lookat.y = FixedCos(m_rotation);

	// ����λ��;
	auto delta = m_lookat * m_speed;
	m_fixedPosition += delta;

	// ������Ļ������ѭ��;
	if (m_fixedPosition.x < DISPLAY->left()) m_fixedPosition.x = DISPLAY->right();
	if (m_fixedPosition.x > DISPLAY->right()) m_fixedPosition.x = DISPLAY->left();
	if (m_fixedPosition.y < DISPLAY->bottom()) m_fixedPosition.y = DISPLAY->top();
	if (m_fixedPosition.y > DISPLAY->top()) m_fixedPosition.y = DISPLAY->bottom();

	// ����nodeλ�úͽǶ�;
	this->setPosition((float)m_fixedPosition.x, (float)m_fixedPosition.y);
	m_drawnode->setRotation( (float)(m_rotation * 180 / M_PI) );

	return true;
}

bool Sweeper::checkCollision( const FixedVec2& mine )
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

void Sweeper::increaseFitness()
{
	// ���»��������е���Ӧֵ;
	auto &genome = m_brain.getGenome();
	++genome.fitness;

	// ˢ����Ӧֵ;
	char s[32];
	sprintf(s, "%d", (int)genome.fitness);
	m_label->setString(s);
}

void Sweeper::resetFitness()
{
	m_label->setString("");
}
