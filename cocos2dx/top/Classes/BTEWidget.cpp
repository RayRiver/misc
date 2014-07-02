#include "BTEWidget.h"

#include "BehaviorTreeEditor.h"
#include "BTENode.h"

USING_NS_CC;

BTEWidget * BTEWidget::create( const std::string& filename )
{
	BTEWidget *ret = new BTEWidget();
	if (ret && ret->initWithFile(filename))
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

bool BTEWidget::initWithFile( const std::string& filename )
{
	if (!BTEResponder::initWithFile(filename))
	{
		return false;
	}

	m_forkNode = nullptr;

	return true;
}

void BTEWidget::onActivate()
{
	m_forkNode = BTENode::create("textures/button_n.png");
	m_forkNode->setPosition(this->getPosition());
	//BehaviorTreeEditor::getInstance()->getCanvasLayer()->addChild(m_forkNode);
	//BehaviorTreeEditor::getInstance()->getCanvasLayer()->registerResponder(m_forkNode);
	BehaviorTreeEditor::getInstance()->getCanvasLayer()->addNode(m_forkNode);
}

void BTEWidget::onInactivate()
{
	m_forkNode = nullptr;
}

void BTEWidget::onAction( const Vec2 &last, const Vec2 &current )
{
	m_forkNode->setPosition(m_forkNode->getPosition() + current - last);
}

