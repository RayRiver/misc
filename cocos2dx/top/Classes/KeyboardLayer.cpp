#include "KeyboardLayer.h"

#include "InputManager.h"

USING_NS_CC;

KeyboardLayer * KeyboardLayer::create( InputManager *inputManager )
{
	auto pRet = new KeyboardLayer();
	if (pRet && pRet->init(inputManager)) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL;
	} 
}

KeyboardLayer::KeyboardLayer()
	: m_inputManager(nullptr)
{

}

KeyboardLayer::~KeyboardLayer()
{

}

bool KeyboardLayer::init( InputManager *inputManager )
{
	if (!Layer::init())
	{
		return false;
	}

	m_inputManager = inputManager;

	this->addKeyAction(EventKeyboard::KeyCode::KEY_W, InputManager::Action::Up);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_CAPITAL_W, InputManager::Action::Up);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_S, InputManager::Action::Down);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_CAPITAL_S, InputManager::Action::Down);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_A, InputManager::Action::Left);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_CAPITAL_A, InputManager::Action::Left);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_D, InputManager::Action::Right);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_CAPITAL_D, InputManager::Action::Right);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_J, InputManager::Action::Action1);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_CAPITAL_J, InputManager::Action::Action1);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_K, InputManager::Action::Action2);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_CAPITAL_K, InputManager::Action::Action2);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_L, InputManager::Action::Action3);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_CAPITAL_L, InputManager::Action::Action3);
	this->addKeyAction(EventKeyboard::KeyCode::KEY_ESCAPE, InputManager::Action::Esc);

	this->registerInputBeganHandler(InputManager::Action::Action1);
	this->registerInputEndedHandler(InputManager::Action::Action1);
	this->registerInputBeganHandler(InputManager::Action::Action2);
	this->registerInputEndedHandler(InputManager::Action::Action2);
	this->registerInputBeganHandler(InputManager::Action::Action3);
	this->registerInputEndedHandler(InputManager::Action::Action3);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event *event) {
		KEY_MAP::iterator it = m_keyMap.find(keycode);
		if (it != m_keyMap.end())
		{
			KeyInfo *keyInfo = &(it->second);
			ACTION_MAP::iterator it = m_actionMap.find(keyInfo->action);
			if (it != m_actionMap.end())
			{
				ActionInfo *actionInfo = &(it->second);
				actionInfo->active = true;	
				if (actionInfo->beganCallback)
				{
					actionInfo->beganCallback();
				}
			}
		}
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event *event) {
		KEY_MAP::iterator it = m_keyMap.find(keycode);
		if (it != m_keyMap.end())
		{
			KeyInfo *keyInfo = &(it->second);
			ACTION_MAP::iterator it = m_actionMap.find(keyInfo->action);
			if (it != m_actionMap.end())
			{
				ActionInfo *actionInfo = &(it->second);
				actionInfo->active = false;	
				if (actionInfo->endedCallback)
				{
					actionInfo->endedCallback();
				}
			}
		}
	};
	
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	this->scheduleUpdate();

	return true;
}

void KeyboardLayer::update( float dt )
{
	Vec2 direction = Vec2::ZERO;
	if (m_actionMap[InputManager::Action::Left].active)
	{
		direction.x = -1;	
	}
	else if (m_actionMap[InputManager::Action::Right].active)
	{
		direction.x = 1;
	}
	if (m_actionMap[InputManager::Action::Up].active)
	{
		direction.y = 1;	
	}
	else if (m_actionMap[InputManager::Action::Down].active)
	{
		direction.y = -1;
	}

	if (direction != Vec2::ZERO)
	{
		direction.normalize();
		m_inputManager->_showJoystick(Point(100, 100));
		m_inputManager->_simulateUpdateJoystick(direction);
	}
	else
	{
		//m_inputManager->_hideJoystick();
	}

}

void KeyboardLayer::addKeyAction( cocos2d::EventKeyboard::KeyCode key, int action )
{
	// update key map
	KeyInfo keyInfo;
	keyInfo.action = action;
	m_keyMap[key] = keyInfo;

	// update action map
	KEYS *keys = nullptr;
	ACTION_MAP::iterator it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		keys = &(it->second).keys;
	}
	else
	{
		ActionInfo actionInfo;
		actionInfo.active = false;
		m_actionMap[action] = actionInfo;	
		keys = &(m_actionMap[action].keys);
	}
	keys->insert(key);
}

void KeyboardLayer::registerInputBeganHandler( int action )
{
	ACTION_MAP::iterator it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		ActionInfo *actionInfo = &(it->second);
		actionInfo->beganCallback = [=]() {
			InputManager::ButtonInfo *info = m_inputManager->_findButton(action);
			if (info)
			{
				m_inputManager->_pressButton(info);
			}	
		};
	}
}

void KeyboardLayer::registerInputEndedHandler( int action )
{
	ACTION_MAP::iterator it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		ActionInfo *actionInfo = &(it->second);
		actionInfo->endedCallback = [=]() {
			InputManager::ButtonInfo *info = m_inputManager->_findButton(action);
			if (info)
			{
				m_inputManager->_releaseButton(info);
			}	
		};
	}
}


