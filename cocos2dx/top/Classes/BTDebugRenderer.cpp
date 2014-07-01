#include "BTDebugRenderer.h"

#include "BTDebugNode.h"
#include "VisibleRect.h"

USING_NS_CC;

BTDebugRenderer * BTDebugRenderer::create( BTNode *root )
{
	auto ret = new BTDebugRenderer();
	if (ret && ret->init(root))
	{
		ret->autorelease();
	}
	else
	{
		delete ret;
		ret = nullptr;
	}
	return ret;
}

BTDebugRenderer::BTDebugRenderer()
	: m_btroot(nullptr)
{

}

BTDebugRenderer::~BTDebugRenderer()
{

}

bool BTDebugRenderer::init(BTNode *root)
{
	if (!Layer::init())
	{
		return false;
	}

	m_btroot = root;

	m_drawNode = DrawNode::create();
	this->addChild(m_drawNode);

	// 创建所有的节点和线
	NodeInfo nodeInfo;
	nodeInfo.btNode = m_btroot;
	NodeList nodes;
	nodes.push_back(nodeInfo);
	this->initNodes(nodes, 0);

	return true;
}

void BTDebugRenderer::initNodes( NodeList &nodes, float origin_x )
{
	const float interval_x = 20.0f;
	const float interval_y = 10.0f;

	NodeList nextNodes;
	float max_width = 0.0f;
	float max_height = 0.0f;
	for (auto &node : nodes)	
	{
		node.debugNode = BTDebugNode::create(node.btNode);

		const Size &size = node.debugNode->getContentSize();
		if (max_width < size.width)
		{
			max_width = size.width;
		}
		max_height += size.height;

		// 子节点加入下一层节点
		for (const auto &child : node.btNode->getChildrenList())	
		{
			NodeInfo nodeInfo;
			nodeInfo.btNode = child;
			nodeInfo.prevDebugNode = node.debugNode;
			nextNodes.push_back(nodeInfo);
		}
	}
	max_width += 2*interval_x;
	max_height += (nodes.size()+1)*interval_y;

	float origin_y = VisibleRect::center().y + max_height/2;
	for (auto &nodeInfo : nodes)	
	{
		const auto &btNode = nodeInfo.btNode;
		const auto &debugNode = nodeInfo.debugNode;
		const auto &prevDebugNode = nodeInfo.prevDebugNode;

		// 设置节点位置
		const Size &size = debugNode->getContentSize();
		debugNode->setPosition(origin_x + interval_x + size.width/2, origin_y - interval_y - size.height/2);
		this->addChild(debugNode);

		// 渲染节点背景
		float x = debugNode->getPositionX();
		float y = debugNode->getPositionY();
		float w = debugNode->getContentSize().width;
		float h = debugNode->getContentSize().height;
		Vec2 vertexes[4] = {Vec2(x-w/2, y-h/2), Vec2(x-w/2, y+h/2), Vec2(x+w/2, y+h/2), Vec2(x+w/2, y-h/2)};
		m_drawNode->drawPolygon(vertexes, 4, Color4F(0.5, 0, 0, 0.5f), 0.5f, Color4F(1, 1, 1, 0.5f));

		// 连线
		if (prevDebugNode)
		{
			m_drawNode->drawSegment(
				Vec2(prevDebugNode->getPositionX()+prevDebugNode->getContentSize().width/2, prevDebugNode->getPositionY()),
				Vec2(debugNode->getPositionX()-debugNode->getContentSize().width/2, debugNode->getPositionY()),
				1.0f, Color4F(1, 1, 1, 0.5));
		}

		origin_y -= (interval_y+size.height);
	}

	if (nextNodes.size() > 0)
	{
		this->initNodes(nextNodes, origin_x + max_width);
	}
}

void BTDebugRenderer::render()
{
	
}
