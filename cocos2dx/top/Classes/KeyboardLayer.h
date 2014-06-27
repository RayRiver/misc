#ifndef KeyboardLayer_h__
#define KeyboardLayer_h__

#include <vector>
#include <set>
#include <map>

#include "cocos2d.h"

class InputManager;
class KeyboardLayer : public cocos2d::Layer
{
public:
	typedef std::function<void ()> Callback;

public:
	KeyboardLayer();
	virtual ~KeyboardLayer();

	static KeyboardLayer *create(InputManager *m_inputManager); 

	virtual bool init(InputManager *m_inputManager);
	virtual void update(float dt);

	void registerInputBeganHandler(int action);
	void registerInputEndedHandler(int action);

private:
	void addKeyAction(cocos2d::EventKeyboard::KeyCode key, int action);
	
private:
	typedef cocos2d::EventKeyboard::KeyCode KEYCODE;
	typedef std::set<KEYCODE> KEYS;
	typedef std::map<cocos2d::Ref *, Callback> OBJECT_EVENT_MAP;

	// action -> action info
	struct ActionInfo
	{
		KEYS keys;
		Callback beganCallback;
		Callback endedCallback;
		bool active;
	};
	typedef std::map<int, ActionInfo> ACTION_MAP;




	// key -> key info
	struct KeyInfo
	{
		int action;
	};
	typedef std::map<cocos2d::EventKeyboard::KeyCode, KeyInfo> KEY_MAP;

	ACTION_MAP m_actionMap;
	KEY_MAP m_keyMap;

	InputManager *m_inputManager;
};

#endif // KeyboardLayer_h__
