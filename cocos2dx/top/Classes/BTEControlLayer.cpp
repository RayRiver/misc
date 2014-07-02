#include "BTEControlLayer.h"

#include "VisibleRect.h"

#include "BehaviorTreeEditor.h"
#include "BTENode.h"
#include "BTEResponder.h"
#include "BTEWidget.h"

USING_NS_CC;

bool BTEControlLayer::init()
{
	if (!BTELayer::init())
	{
		return false;
	}

	m_draggingNode = nullptr;

	// background
	auto drawNode = DrawNode::create();
	Vec2 verts[] = { 
		VisibleRect::leftTop(), 
		VisibleRect::leftBottom(), 
		Vec2(VisibleRect::left().x+VisibleRect::getVisibleRect().size.width/3, VisibleRect::bottom().y), 
		Vec2(VisibleRect::left().x+VisibleRect::getVisibleRect().size.width/3, VisibleRect::top().y)
	};
	drawNode->drawPolygon(verts, 4, Color4F(0.8f, 0.8f, 0.8f, 1.0f), 1.0f, Color4F(0.4f, 0.4f, 0.4f, 1.0f));
	this->addChild(drawNode);

	// responder
	auto button = BTEWidget::create("textures/button_n.png");
	button->setPosition(50, 100);
	this->addChild(button);
	this->registerResponder(button);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = [=](const std::vector<Touch*> &touches, Event *event) {
		auto touch = touches[0];
		const Vec2 &pos = button->getPosition();
		const Size &size = button->getContentSize();
		const Rect &rect = Rect(pos.x-size.width/2, pos.y-size.height/2, size.width, size.height);
		const Vec2 &point = touch->getLocation();
		if (rect.containsPoint(point))
		{
			auto node = BTENode::create("textures/button_n.png");
			node->setPosition(button->getPosition());
			BehaviorTreeEditor::getInstance()->getCanvasLayer()->addChild(node);
			m_draggingNode = node;
		}
	};
	listener->onTouchesMoved = [=](const std::vector<Touch*> &touches, Event *event) {
		if (m_draggingNode)
		{
			auto touch = touches[0];
			Vec2 pos = touch->getLocation();

			const Size &size = m_draggingNode->getContentSize();
			if (pos.x < VisibleRect::left().x + size.width/2)
			{
				pos.x = VisibleRect::left().x + size.width/2;	
			}
			else if (pos.x > VisibleRect::right().x - size.width/2)
			{
				pos.x = VisibleRect::right().x - size.width/2;
			}
			if (pos.y < VisibleRect::bottom().y + size.height/2)
			{
				pos.y = VisibleRect::bottom().y + size.height/2;	
			}
			else if (pos.y > VisibleRect::top().y - size.height/2)
			{
				pos.y = VisibleRect::top().y - size.height/2;
			}

			m_draggingNode->setPosition(pos);	
		}
	}; 
	listener->onTouchesEnded = [=](const std::vector<Touch*> &touches, Event *event) {
		auto touch = touches[0];
		if (m_draggingNode)
		{
			const Vec2 &point = touch->getLocation();
			const Size &size = m_draggingNode->getContentSize();
			if (point.x - size.width/2 > VisibleRect::getVisibleRect().size.width/3 &&
				point.x + size.width/2 < VisibleRect::right().x &&
				point.y - size.height/2 > VisibleRect::bottom().y &&
				point.y + size.height/2 < VisibleRect::top().y)
			{
				m_draggingNode->setPosition(touch->getLocation());	
				m_draggingNode = nullptr;
			}
			else
			{
				this->removeChild(m_draggingNode);
				m_draggingNode = nullptr;
			}
		}
	}; 
	listener->onTouchesCancelled = [=](const std::vector<Touch*> &touches, Event *event) {
		if (m_draggingNode)
		{
			this->removeChild(m_draggingNode);
			m_draggingNode = nullptr;
		}
	}; 
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

