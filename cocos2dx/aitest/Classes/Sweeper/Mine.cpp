#include "Mine.h"

USING_NS_CC;

bool Mine::init()
{
	if (!Node::init())
	{
		return false;
	}

	// 创建渲染节点;
	auto drawnode = DrawNode::create();
	this->addChild(drawnode);

	// 绘制实体;
	drawnode->drawDot(Vec2(0,0), 5.0f, Color4F(1.0, 1.0f, 1.0f, 0.2f));

	return true;
}

