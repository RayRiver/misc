#ifndef InputManager_h__
#define InputManager_h__

#include <map>

#include "cocos2d.h"

class InputManager : public cocos2d::Layer
{
public:
	enum class JoystickState
	{
		None,
		Light,
		Heavy,
	};
	enum Action
	{
		// for keyboard only
		Up = -4,
		Down = -3,
		Left = -2,
		Right = -1,
		Esc = 0,

		// actions
		Action1 = 1,
		Action2,
		Action3,
	};

public:
	InputManager();
	virtual ~InputManager();

	virtual bool init();

	CREATE_FUNC(InputManager);

	inline cocos2d::Vec2 &getJoystickDirection() { return m_joystickDirection; }
	inline float getJoystickValue() { return m_joystickValue; }
	inline JoystickState getJoystickState() { return m_joystickState; }
	inline JoystickState getJoystickPrevState() { return m_joystickPrevState; }

	void addButton(int id, const cocos2d::Vec2 &pos);
	bool buttonPressedTrigger(int id);
	bool buttonReleaseTrigger(int id);
	bool isButtonPressed(int id);

private:
	cocos2d::Touch *m_joystickTouch;
	typedef std::map<cocos2d::Touch *, int> TOUCHES;
	typedef std::pair<cocos2d::Touch *, int> TOUCH_PAIR;
	TOUCHES m_buttonTouches;

	cocos2d::Sprite *m_pJoystick;
	cocos2d::Sprite *m_pJoystickBg;



	cocos2d::Vec2 m_joystickDirection;
	float m_joystickValue;
	JoystickState m_joystickState;
	JoystickState m_joystickPrevState;

	struct ButtonInfo
	{
		int id;
		cocos2d::Sprite *button;
		bool pressed;
		bool pressedTrigger;
		bool releaseTrigger;
	};
	typedef std::map<int, ButtonInfo> BUTTON_MAP;
	BUTTON_MAP m_buttonMap;

private:
	void _showJoystick(cocos2d::Point pos);
	void _hideJoystick();
	void _updateJoystick(cocos2d::Vec2 direction, float distance);
	void _simulateUpdateJoystick(cocos2d::Vec2 direction);

	InputManager::ButtonInfo *_findButton(int id);
	void _pressButton(InputManager::ButtonInfo *info);
	void _releaseButton(InputManager::ButtonInfo *info);


public:
	friend class KeyboardLayer;
};

#endif // InputManager_h__
