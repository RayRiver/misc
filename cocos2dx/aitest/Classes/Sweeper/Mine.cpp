#include "Mine.h"

USING_NS_CC;

bool Mine::init()
{
	if (!Node::init())
	{
		return false;
	}

	// ������Ⱦ�ڵ�;
	auto drawnode = DrawNode::create();
	this->addChild(drawnode);

	// ����ʵ��;
	drawnode->drawDot(Vec2(0,0), 5.0f, Color4F(1.0, 1.0f, 1.0f, 0.2f));

	return true;
}

