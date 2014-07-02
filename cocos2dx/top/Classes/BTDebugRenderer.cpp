#include "BTDebugRenderer.h"

#include "BTDebugNode.h"
#include "VisibleRect.h"

USING_NS_CC;

BTDebugRenderer *BTDebugRenderer::s_instance = nullptr;

BTDebugRenderer * BTDebugRenderer::create( BTNode *root )
{
	if (s_instance)
	{
		return s_instance;	
	}

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
	s_instance = ret;
	return s_instance;
}

BTDebugRenderer * BTDebugRenderer::getInstance()
{
	if (s_instance)
	{
		return s_instance;	
	}
	else
	{
		return nullptr;
	}
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

	m_dynamicDrawNode = DrawNode::create();
	this->addChild(m_dynamicDrawNode);

	// 创建所有的节点和线
	NodeInfo nodeInfo;
	nodeInfo.btNode = m_btroot;
	m_nodeMap[m_btroot] = nodeInfo;

	NodeList nodes;
	nodes.push_back(m_btroot);
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
		BTDebugNode *debugNode = BTDebugNode::create(node, m_nodeMap[node].prevDebugNode);
		m_nodeMap[node].debugNode = debugNode;

		const Size &size = debugNode->getContentSize();
		if (max_width < size.width)
		{
			max_width = size.width;
		}
		max_height += size.height;

		// 子节点加入下一层节点
		for (const auto &child : node->getChildrenList())	
		{
			NodeInfo nodeInfo;
			nodeInfo.btNode = child;
			nodeInfo.prevDebugNode = debugNode;
			m_nodeMap[child] = nodeInfo;

			nextNodes.push_back(child);
		}
	}
	max_width += 2*interval_x;
	max_height += (nodes.size()+1)*interval_y;

	float origin_y = VisibleRect::center().y + max_height/2;
	for (auto &node : nodes)	
	{
		const auto &debugNode = m_nodeMap[node].debugNode;
		const auto &prevDebugNode = m_nodeMap[node].prevDebugNode;

		// 设置节点位置
		const Size &size = debugNode->getContentSize();
		debugNode->setPosition(origin_x + interval_x + size.width/2, origin_y - interval_y - size.height/2);
		this->addChild(debugNode);

		// 
		debugNode->sendEvent(BTNodeEvent::exit);

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

void BTDebugRenderer::renderNode( BTNode *node, BTNodeEvent event )
{
	if (!node)
	{
		return;
	}

	auto it = m_nodeMap.find(node);
	if (it == m_nodeMap.end())
	{
		return;
	}
	NodeInfo *info = &(it->second);

	info->debugNode->sendEvent(event);
}
