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

	// 创建渲染节点;
	m_drawnode = DrawNode::create();	
	this->addChild(m_drawnode);

	// 绘制实体;
	Vec2 verts[] = 
	{ 
		Vec2((float)-m_size.x/2, (float)-m_size.y/2), 
		Vec2((float) m_size.x/2, (float)-m_size.y/2), 
		Vec2((float) m_size.x/2, (float) m_size.y/2), 
		Vec2((float)-m_size.x/2, (float) m_size.y/2) 
	};
	m_drawnode->drawPolygon(verts, 4, Color4F(0.0f, 1.0f, 0.0f, 0.5f), 1.0f, Color4F(0.0f, 1.0f, 0.0f, 0.5f));

	// 创建适应值显示标签;
	m_label = Label::createWithSystemFont("", "Arial", 12);
	m_label->setPosition(0, 20);
	this->addChild(m_label);

	return true;
}

bool Sweeper::update(const FixedVec2 &closestPos)
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
	m_rotation -= rotForce;
	
	// 更新视线;
	m_lookat.x = -FixedSin(m_rotation);
	m_lookat.y = FixedCos(m_rotation);

	// 更新位置;
	auto delta = m_lookat * m_speed;
	m_fixedPosition += delta;

	// 超出屏幕则让其循环;
	if (m_fixedPosition.x < DISPLAY->left()) m_fixedPosition.x = DISPLAY->right();
	if (m_fixedPosition.x > DISPLAY->right()) m_fixedPosition.x = DISPLAY->left();
	if (m_fixedPosition.y < DISPLAY->bottom()) m_fixedPosition.y = DISPLAY->top();
	if (m_fixedPosition.y > DISPLAY->top()) m_fixedPosition.y = DISPLAY->bottom();

	// 更新node位置和角度;
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
	// 更新基因组序列的适应值;
	auto &genome = m_brain.getGenome();
	++genome.fitness;

	// 刷新适应值;
	char s[32];
	sprintf(s, "%d", (int)genome.fitness);
	m_label->setString(s);
}

void Sweeper::resetFitness()
{
	m_label->setString("");
}
