#include "BehaviorTreeEditor.h"

#include "VisibleRect.h"

#include "BTECanvasLayer.h"
#include "BTEControlLayer.h"

USING_NS_CC;

BehaviorTreeEditor *BehaviorTreeEditor::s_instance = nullptr;
BehaviorTreeEditor * BehaviorTreeEditor::getInstance()
{
	if (!s_instance)
	{
		BehaviorTreeEditor::create();
	}
	return s_instance;
}

cocos2d::Scene* BehaviorTreeEditor::create()
{
	auto scene = Scene::create();
	auto layer = new BehaviorTreeEditor;
	if (layer && layer->init())
	{
		layer->autorelease();
		BehaviorTreeEditor::s_instance = layer;
		scene->addChild(layer);
	}
	else
	{
		delete layer;
		layer = nullptr;
	}
	return scene;
}

bool BehaviorTreeEditor::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_canvasLayer = BTECanvasLayer::create();
	this->addChild(m_canvasLayer);

	m_controlLayer = BTEControlLayer::create();
	this->addChild(m_controlLayer);




	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = [=](const std::vector<Touch*> &touches, Event *event) {
		auto touch = touches[0];
		if (touch->getLocation().x < VisibleRect::getVisibleRect().size.width/3)
		{
			m_controlLayer->touchBegan(touch, event);
		}
		else
		{
			if (!m_canvasLayer->touchBegan(touch, event))
			{
				m_canvasLayer->startDrag();
			}
		}
	};
	listener->onTouchesMoved = [=](const std::vector<Touch*> &touches, Event *event) {
		auto touch = touches[0];
		if (m_controlLayer->isTouchActive())
		{
			m_controlLayer->touchMoved(touch, event);
		}
		else if (m_canvasLayer->isTouchActive())
		{
			m_canvasLayer->touchMoved(touch, event);
		}
		else if (m_canvasLayer->isDragging())
		{
			m_canvasLayer->doDrag(touch->getLocation() - touch->getPreviousLocation());
		}
	}; 
	listener->onTouchesEnded = [=](const std::vector<Touch*> &touches, Event *event) {
		auto touch = touches[0];
		if (m_controlLayer->isTouchActive())
		{
			m_controlLayer->touchEnded(touch, event);
		}
		else if (m_canvasLayer->isTouchActive())
		{
			m_canvasLayer->touchEnded(touch, event);
		}
		else if (m_canvasLayer->isDragging())
		{
			m_canvasLayer->stopDrag();
		}
	}; 
	listener->onTouchesCancelled = [=](const std::vector<Touch*> &touches, Event *event) {
		auto touch = touches[0];
		if (m_controlLayer->isTouchActive())
		{
			m_controlLayer->touchCancelled(touch, event);
		}
		else if (m_canvasLayer->isTouchActive())
		{
			m_canvasLayer->touchCancelled(touch, event);
		}
		else if (m_canvasLayer->isDragging())
		{
			m_canvasLayer->stopDrag();
		}
	}; 
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

