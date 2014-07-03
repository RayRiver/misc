#include "BTECanvasLayer.h"

#include "VisibleRect.h"

#include "BTEResponder.h"
#include "BTENode.h"

USING_NS_CC;

bool BTECanvasLayer::init()
{
	if (!BTELayer::init())
	{
		return false;
	}

	m_bDaggingLayer = false;

	auto colorLayer = LayerColor::create(Color4B(230, 230, 230, 255));
	this->addChild(colorLayer);

	m_drawNode = DrawNode::create();
	//Vec2 verts[] = { Vec2(300, 300), Vec2(300, 400), Vec2(400, 400), Vec2(400, 300) };
	//m_drawNode->drawPolygon(verts, 4, Color4F(1, 1, 1, 1), 2, Color4F(1, 0, 0, 1));
	m_drawNode->drawSegment(VisibleRect::top(), VisibleRect::bottom(), 1.0f, Color4F(250.0/255, 100.0/255, 100.0/255, 200.0/255));
	this->addChild(m_drawNode);



	//m_canvas = BTECanvas::create();
	//m_canvas->setPosition(VisibleRect::getVisibleRect().size.width * 2/3, VisibleRect::center().y);
	//this->addChild(m_canvas);


	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = [=](const std::vector<Touch*> &touches, Event *event) {
		auto touch = touches[0];
		if (touch->getLocation().x > VisibleRect::getVisibleRect().size.width/3)
		{
		}
	};
	listener->onTouchesMoved = [=](const std::vector<Touch*> &touches, Event *event) {
		auto touch = touches[0];
		if (this->isDragging())
		{
			const Vec2 &point = touch->getLocation();
			const Vec2 &lastPoint = touch->getPreviousLocation();
			this->doDrag(point - lastPoint);
		}
	}; 
	listener->onTouchesEnded = [=](const std::vector<Touch*> &touches, Event *event) {
		if (this->isDragging())
		{
			this->stopDrag();
		}
	}; 
	listener->onTouchesCancelled = [=](const std::vector<Touch*> &touches, Event *event) {
		if (this->isDragging())
		{
			this->stopDrag();
		}
	}; 

	return true;
}

void BTECanvasLayer::addNode( BTENode *node )
{
	node->setPosition(node->getPosition()-this->getPosition());
	this->addChild(node);
	this->registerResponder(node);
}

void BTECanvasLayer::startDrag()
{
	m_bDaggingLayer = true;
}

void BTECanvasLayer::stopDrag()
{
	m_bDaggingLayer = false;
}

void BTECanvasLayer::doDrag( const Vec2 &move )
{
	//this->setPosition(this->getPosition() + move);
	for (auto &responder : m_responders)
	{
		responder->setPosition(responder->getPosition() + move);
	}
	m_drawNode->setPosition(m_drawNode->getPosition() + move);
}

bool BTECanvasLayer::isDragging()
{
	return m_bDaggingLayer;
}

