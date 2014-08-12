#include "MineView.h"

USING_NS_CC;

bool MineView::init()
{
	if (!Node::init())
	{
		return false;
	}

	// ������Ⱦ�ڵ�;
	auto drawnode = DrawNode::create();
	this->addChild(drawnode);

	// ����ʵ��;
	drawnode->drawDot(Vec2(0,0), 5.0f, Color4F(1.0, 1.0f, 1.0f, 0.5f));

	return true;
}

void MineView::updatePosition( const FixedPoint &p )
{
	this->setPosition((float)p.x, (float)p.y);
}
