#include "InputManager.h"

#include <string>
#include <set>

#include "VisibleRect.h"

using namespace std;
USING_NS_CC;

#define JOYSTICK_LEVEL_LIGHT 33.0f
#define JOYSTICK_LEVEL_HEAVY 45.0f

InputManager::InputManager()
	: m_pJoystick(nullptr)
	, m_pJoystickBg(nullptr)
	, m_joystickTouch(nullptr)	
	, m_joystickDirection(Vec2::ZERO)
	, m_joystickValue(0.0f)
	, m_joystickPrevState(JoystickState::None)
	, m_joystickState(JoystickState::None)
{

}

InputManager::~InputManager()
{

}

bool InputManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto texture_joystick_bg = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
	auto texture_joystick = Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");

	m_pJoystick = Sprite::createWithTexture(texture_joystick);
	m_pJoystickBg = Sprite::createWithTexture(texture_joystick_bg);
	this->addChild(m_pJoystick);
	this->addChild(m_pJoystickBg);
	this->_hideJoystick();



	auto listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = [=](const std::vector<Touch *> &touches, Event *unused_event) {
		std::set<Touch *> tempTouches;

		for (auto touch : touches)
		{
			Point p = touch->getLocation();
			if (p.x <= VisibleRect::getVisibleRect().size.width / 2)
			{
				if (!m_joystickTouch)
				{
					m_joystickTouch = touch;
				}
			}
			else
			{
				tempTouches.insert(touch);
			}
		}

		if (m_joystickTouch)
		{
			this->_showJoystick(m_joystickTouch->getLocation());
		}
		for (const auto touch : tempTouches)
		{
			for (auto &it : m_buttonMap)
			{
				auto &info = it.second;
				Size size = info.button->getContentSize();
				Point pos = info.button->getPosition();
				Rect rect = Rect(pos.x-size.width/2, pos.y-size.height/2, size.width, size.height);
				if (rect.containsPoint(touch->getLocation()))
				{
					this->_pressButton(&info);
					m_buttonTouches.insert(TOUCH_PAIR(touch, info.id));
					break;
				}
			}

		}
	};

	listener->onTouchesMoved = [=](const std::vector<Touch *> &touches, Event *unused_event) {
		for (auto touch : touches)
		{
			if (m_joystickTouch == touch)
			{
				Point start = touch->getStartLocation();
				Point dest = touch->getLocation();
				float distance = start.getDistance(dest);
				Point direction = dest - start;
				direction.normalize();
				this->_updateJoystick(direction, distance);
			}
			else 
			{
				TOUCHES::iterator it = m_buttonTouches.find(touch);
				if (it != m_buttonTouches.end())
				{
					auto id = it->second;
					auto &info = m_buttonMap[id];
					Size size = info.button->getContentSize();
					Point pos = info.button->getPosition();
					Rect rect = Rect(pos.x-size.width/2, pos.y-size.height/2, size.width, size.height);
					if (!rect.containsPoint(touch->getLocation()))
					{
						this->_releaseButton(&info);
						m_buttonTouches.erase(it);
					}

				}
			}
		}
	};

	listener->onTouchesEnded = [=](const std::vector<Touch *> &touches, Event *unused_event) {
		for (auto touch : touches)
		{
			if (m_joystickTouch == touch)
			{
				m_joystickTouch = nullptr;
				this->_hideJoystick();
			}
			else 
			{
				TOUCHES::iterator it = m_buttonTouches.find(touch);
				if (it != m_buttonTouches.end())
				{
					auto id = it->second;
					auto &info = m_buttonMap[id];

					this->_releaseButton(&info);
					m_buttonTouches.erase(it);
				}
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


void InputManager::addButton( int id, const cocos2d::Vec2 &pos )
{
	auto texture_button_normal = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
	auto sprite = Sprite::createWithTexture(texture_button_normal);
	sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	sprite->setPosition(pos);
	this->addChild(sprite);

	ButtonInfo info;
	info.id = id;
	info.button = sprite;
	info.pressed = false;
	info.pressedTrigger = false;
	info.releaseTrigger = false;
	m_buttonMap[id] = info;
}

bool InputManager::buttonPressedTrigger( int id )
{
	auto info = this->_findButton(id);
	bool bTrigger = false;
	if (info)
	{
		bTrigger = info->pressedTrigger;
		info->pressedTrigger = false;
	}
	return bTrigger;
}

bool InputManager::buttonReleaseTrigger( int id )
{
	auto info = this->_findButton(id);
	bool bTrigger = false;
	if (info)
	{
		bTrigger = info->releaseTrigger;
		info->releaseTrigger = false;
	}
	return bTrigger;
}

bool InputManager::isButtonPressed( int id )
{
	auto info = this->_findButton(id);
	if (info)
	{
		return info->pressed;
	}
	else
	{
		return false;
	}
}

void InputManager::_showJoystick(Point pos)
{
	m_pJoystick->setPosition(pos);
	m_pJoystickBg->setPosition(pos);
	m_pJoystick->setVisible(true);
	m_pJoystickBg->setVisible(true);
}

void InputManager::_hideJoystick()
{
	m_pJoystick->setPosition(m_pJoystickBg->getPosition());
	m_pJoystick->setVisible(false);
	m_pJoystickBg->setVisible(false);


	m_joystickDirection = Vec2::ZERO;
	m_joystickValue = 0.0f;
	m_joystickPrevState = m_joystickState;
	m_joystickState = JoystickState::None;
}

void InputManager::_updateJoystick(Vec2 direction, float distance)
{
	m_joystickDirection = direction;
	m_joystickPrevState = m_joystickState;

	if (distance <= JOYSTICK_LEVEL_LIGHT)
	{
		m_joystickValue = distance;
		m_joystickState = JoystickState::Light;
	}
	else if (distance >= JOYSTICK_LEVEL_HEAVY) 
	{
		m_joystickValue = JOYSTICK_LEVEL_HEAVY;
		m_joystickState = JoystickState::Heavy;
	}
	else 
	{
		m_joystickValue = distance;
		m_joystickState = JoystickState::Heavy;
	}

	Point start = m_pJoystickBg->getPosition();
	m_pJoystick->setPosition(start + (direction * m_joystickValue));
}

void InputManager::_simulateUpdateJoystick(Vec2 direction)
{
	this->_updateJoystick(direction, JOYSTICK_LEVEL_HEAVY);
}

InputManager::ButtonInfo * InputManager::_findButton( int id )
{
	BUTTON_MAP::iterator it = m_buttonMap.find(id);	
	if (it == m_buttonMap.end())
	{
		return nullptr;
	}
	return &(it->second);
}

void InputManager::_pressButton( ButtonInfo *info )
{
	info->pressed = true;
	info->pressedTrigger = true;
	auto texture_button_pressed = Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");
	info->button->setTexture(texture_button_pressed);
}

void InputManager::_releaseButton( ButtonInfo *info )
{
	info->pressed = false;
	info->releaseTrigger = true;
	auto texture_button_normal = Director::getInstance()->getTextureCache()->addImage("CloseNormal.png");
	info->button->setTexture(texture_button_normal);
}
