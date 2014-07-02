#include "BTELayer.h"

#include "BTEResponder.h"

USING_NS_CC;

bool BTELayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_activeResponder = nullptr;

	return true;
}

bool BTELayer::touchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
	if (!m_activeResponder)
	{
		auto activeResponder = getActiveResponder(touch->getLocation());
		if (activeResponder)
		{
			m_activeResponder = activeResponder;
			activeResponder->onActivate();
			return true;
		}
	}
	else
	{
		CCASSERT(false, "");
	}
	return false;
}

void BTELayer::touchMoved( cocos2d::Touch *touch, cocos2d::Event *event )
{
	if (m_activeResponder)
	{
		m_activeResponder->onAction(touch->getPreviousLocation(), touch->getLocation());
	}
	else
	{
		CCASSERT(false, "");
	}
}

void BTELayer::touchEnded( cocos2d::Touch *touch, cocos2d::Event *event )
{
	if (m_activeResponder)
	{
		m_activeResponder->onInactivate();
		m_activeResponder = nullptr;
	}
	else
	{
		CCASSERT(false, "");
	}
}

void BTELayer::touchCancelled( cocos2d::Touch *touch, cocos2d::Event *event )
{
	if (m_activeResponder)
	{
		m_activeResponder->onInactivate();
		m_activeResponder = nullptr;
	}
	else
	{
		CCASSERT(false, "");
	};
}

void BTELayer::registerResponder( BTEResponder *responder )
{
	m_responders.push_back(responder);
}

BTEResponder * BTELayer::getActiveResponder( const cocos2d::Vec2 &point )
{
	for (ResponderList::reverse_iterator it=m_responders.rbegin(); it!=m_responders.rend(); ++it)
	//for (const auto &responder : m_responders)
	{
		const auto &responder = *it;

		if (!responder)
		{
			CCASSERT(false, "");
			continue;
		}

		const Vec2 &pos = responder->getPosition();
		const Size &size = responder->getContentSize();
		const Rect &rect = Rect(pos.x-size.width/2, pos.y-size.height/2, size.width, size.height);
		if (rect.containsPoint(point))
		{
			return responder;
		}
	}
	return nullptr;
}

