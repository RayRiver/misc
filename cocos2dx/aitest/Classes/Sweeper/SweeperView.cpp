#include "SweeperView.h"

USING_NS_CC;

#include "SweeperObject.h"

SweeperView * SweeperView::create()
{
	auto view = new SweeperView;
	if (view && view->init())
	{
		view->autorelease();
	}
	else
	{
		delete view;
		view = nullptr;
	}
	return view;
}

bool SweeperView::init()
{
	if (!Node::init())
	{
		return false;
	}

	// 创建渲染节点;
	m_drawnode = DrawNode::create();	
	this->addChild(m_drawnode);

	// 创建适应值显示标签;
	m_label = Label::createWithSystemFont("", "Arial", 12);
	m_label->setPosition(0, 20);
	this->addChild(m_label);

	return true;
}

void SweeperView::updatePosition( const FixedPoint &p )
{
	this->setPosition((float)p.x, (float)p.y);
}

void SweeperView::updateSize( const FixedSize &size )
{
	// 重新绘制实体;
	Vec2 verts[] = 
	{ 
		Vec2((float)-size.x/2, (float)-size.y/2), 
		Vec2((float) size.x/2, (float)-size.y/2), 
		Vec2((float) size.x/2, (float) size.y/2), 
		Vec2((float)-size.x/2, (float) size.y/2) 
	};
	m_drawnode->clear();
	m_drawnode->drawPolygon(verts, 4, Color4F(0.0f, 1.0f, 0.0f, 0.5f), 1.0f, Color4F(0.0f, 1.0f, 0.0f, 0.5f));
}

void SweeperView::updateFitness( const Fixed &n )
{
	if (FixedEquals(n, FixedZero))
	{
		m_label->setString("");
	}
	else
	{
		char s[32];
		sprintf(s, "%d", (int)n);
		m_label->setString(s);
	}
}

void SweeperView::updateRotation( const Fixed &rotation )
{
	float r = (float)(rotation * 180 / M_PI);
	this->setRotation(r);
}
