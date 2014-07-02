#include "BTDebugNode.h"

#include <vector>

#include "Utils.h"
#include "BTNode.h"
#include "BTDebugRenderer.h"

USING_NS_CC;
using namespace std;

BTDebugNode * BTDebugNode::create( BTNode *btnode, BTDebugNode *prevDebugNode )
{
	auto ret = new BTDebugNode();
	if (ret && ret->init(btnode, prevDebugNode))
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

bool BTDebugNode::init( BTNode *btnode, BTDebugNode *prevDebugNode )
{
	if (!Node::init())
	{
		return false;
	}

	m_btnode = btnode;
	m_prev = prevDebugNode;

	m_drawNode = DrawNode::create();
	this->addChild(m_drawNode);

	const char *fontName = "SimSun.ttf";
	const int fontSize = 12;
	const float fontBorder = 3.0f;

	vector<Node *> vChildren;

	// 显示前提条件
	if (btnode->getPrecondition())
	{
		const char *desc = btnode->getPreconditionDesc();
		if (desc[0] == 0)
		{
			desc = Utils::gettext("string_btprecondition_default_desc");
		}

		auto text = Label::createWithSystemFont(desc, fontName, fontSize);
		Size size = text->getContentSize();
		size.width += 2*fontBorder;
		size.height += 2*fontBorder;

		auto node = Node::create();
		node->setContentSize(size);

		node->addChild(text);

		vChildren.push_back(node);
	}

	// 显示节点信息
	{
		const char *desc = btnode->getName();
		if (desc[0] == 0)
		{
			desc = Utils::gettext("string_btnode_default_desc");
		} 

		auto text = Label::createWithSystemFont(desc, fontName, fontSize);
		Size size = text->getContentSize();
		size.width += 2*fontBorder;
		size.height += 2*fontBorder;

		auto node = Node::create();
		node->setContentSize(size);

		node->addChild(text);

		vChildren.push_back(node);
	}

	float max_width = 0.0f;
	float max_height = 0.0f;
	for (const auto &child : vChildren)
	{
		const Size &size = child->getContentSize();
		if (max_width < size.width)
		{
			max_width = size.width;
		}
		max_height += size.height;
	}
	const float interval = 10.0f;
	max_width += 2*interval;
	max_height += (vChildren.size()+1)*interval;


	Vec2 vertexes[4] = {Vec2(-max_width/2, -max_height/2), Vec2(-max_width/2, +max_height/2), Vec2(+max_width/2, +max_height/2), Vec2(+max_width/2, -max_height/2)};
	m_drawNode->drawPolygon(vertexes, 4, Color4F(0.5, 0, 0, 0.5f), 0.5f, Color4F(1, 1, 1, 0.5f));

	auto node = Node::create();
	node->setContentSize(Size(max_width, max_height));

	float origin_y = -max_height/2;
	for (size_t i=0; i<vChildren.size(); ++i)
	{
		Size size = vChildren[i]->getContentSize();
		vChildren[i]->setPosition(0, origin_y+interval+size.height/2);	
		node->addChild(vChildren[i]);
		origin_y += (interval+size.height);
	}

	this->setContentSize(node->getContentSize());
	this->addChild(node);

	return true;
}

void BTDebugNode::sendEvent( BTNodeEvent event )
{
	drawNode(event, true);
}

void BTDebugNode::drawNode( BTNodeEvent event, bool isActionNode )
{
	auto debugNode = this;
	auto prevDebugNode = this->m_prev;

	const Size &size = debugNode->getContentSize();
	auto w = size.width;
	auto h = size.height;
	Vec2 rectVerts[4] = {Vec2(-w/2, -h/2), Vec2(-w/2, +h/2), Vec2(+w/2, +h/2), Vec2(+w/2, -h/2)};	
	Vec2 segmentV1;
	Vec2 segmentV2;
	if (prevDebugNode)
	{
		segmentV1 = Vec2(prevDebugNode->getPositionX()-debugNode->getPositionX()+prevDebugNode->getContentSize().width/2, prevDebugNode->getPositionY()-debugNode->getPositionY());
		segmentV2 = Vec2(-debugNode->getContentSize().width/2, 0);
	}
	Color4F rect_fillcolor_enter;
	Color4F rect_fillcolor_exit;
	float rect_border_width;
	if (isActionNode)
	{
		rect_fillcolor_enter = Color4F(0.0f, 0.8f, 0.0f, 0.5f);
		rect_fillcolor_exit = Color4F(0.8f, 0.0f, 0.0f, 0.5f);
		rect_border_width = 1.0f;
	}
	else
	{
		rect_fillcolor_enter = Color4F(0.0f, 0.5f, 0.0f, 0.5f);
		rect_fillcolor_exit = Color4F(0.5f, 0.0f, 0.0f, 0.5f);
		rect_border_width = 0.5f;
	}

	if (event == BTNodeEvent::enter)
	{
		m_drawNode->clear();
		m_drawNode->drawPolygon(rectVerts, 4, rect_fillcolor_enter, rect_border_width, Color4F(1, 1, 1, 0.5f));
		if (prevDebugNode)
		{
			m_drawNode->drawSegment(segmentV1, segmentV2, 1.5f, Color4F(1, 1, 1, 0.8));
		}
	}
	else if (event == BTNodeEvent::exit)
	{
		m_drawNode->clear();
		m_drawNode->drawPolygon(rectVerts, 4, rect_fillcolor_exit, rect_border_width, Color4F(1, 1, 1, 0.5f));
		if (prevDebugNode)
		{
			m_drawNode->drawSegment(segmentV1, segmentV2, 0.5f, Color4F(1, 1, 1, 0.5));
		}
	}

	if (prevDebugNode)
	{
		prevDebugNode->drawNode(event, false);
	}
}

