#include "BTDebugNode.h"

#include <vector>

#include "Utils.h"
#include "BTNode.h"
#include "BTDebugRenderer.h"

USING_NS_CC;
using namespace std;

BTDebugNode * BTDebugNode::create( BTNode *btnode )
{
	auto ret = new BTDebugNode();
	if (ret && ret->init(btnode))
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

bool BTDebugNode::init( BTNode *btnode )
{
	if (!Node::init())
	{
		return false;
	}

	m_btnode = btnode;

	const int width = 100;
	const int height = 60;
	const char *fontName = "SimSun.ttf";
	const int fontSize = 12;
	const float fontBorder = 3.0f;

	vector<Node *> vChildren;

	// ��ʾǰ������
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
		//Vec2 vertexes[4] = {Vec2(-size.width/2, -size.height/2), Vec2(-size.width/2, size.height/2), Vec2(size.width/2, size.height/2), Vec2(size.width/2, -size.height/2)};
		//draw->drawPolygon(vertexes, 4, Color4F(0, 0, 0.5, 0.5f), 0.5f, Color4F(1, 1, 1, 0.5f));
		node->setContentSize(size);

		node->addChild(text);

		vChildren.push_back(node);
	}

	// ��ʾ�ڵ���Ϣ
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
		//Vec2 vertexes[4] = {Vec2(-size.width/2, -size.height/2), Vec2(-size.width/2, size.height/2), Vec2(size.width/2, size.height/2), Vec2(size.width/2, -size.height/2)};
		//draw->drawPolygon(vertexes, 4, Color4F(0, 0, 0.5, 0.5f), 0.5f, Color4F(1, 1, 1, 0.5f));
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


	auto node = Node::create();
	//float x = this->getPositionX();
	//float y = this->getPositionY();
	//Vec2 vertexes[4] = {Vec2(x-max_width/2, y-max_height/2), Vec2(x-max_width/2, y+max_height/2), Vec2(x+max_width/2, y+max_height/2), Vec2(x+max_width/2, y-max_height/2)};
	//m_manager->getDrawNode()->drawPolygon(vertexes, 4, Color4F(0.5, 0, 0, 0.5f), 0.5f, Color4F(1, 1, 1, 0.5f));
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

	//auto text = Label::createWithSystemFont(Utils::gettext("test"), fontName, fontSize);
	//drawNode->addChild(text);

	return true;
}

