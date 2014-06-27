#ifndef StateMachine_h__
#define StateMachine_h__

#include <string>
#include <map>

#include "cocos2d.h"

class StateMachine : public cocos2d::Component
{
public:
	static const char *NAME;

	enum 
	{ 
		STATE_ALL = -1,
		STATE_NONE = 0,
	};	

	typedef std::function<bool (const char *, int, int)> Callback;

public:
	StateMachine();
	virtual ~StateMachine();

	CREATE_FUNC(StateMachine);

	void setupState(const char *eventName, int fromState, int toState);
	bool doEvent(const char *eventName);
	inline int getState() { return m_currentState; }
	inline bool isState(int state) { return m_currentState == state; }

	void registerBeforeEventCallback(const char *eventName, const Callback &callback);
	void registerAfterEventCallback(const char *eventName, const Callback &callback);
	void registerEnterStateCallback(int state, const Callback &callback);
	void registerLeaveStateCallback(int state, const Callback &callback);

	void registerBeforeEventCallback(const Callback &callback);
	void registerAfterEventCallback(const Callback &callback);
	void registerEnterStateCallback(const Callback &callback);
	void registerLeaveStateCallback(const Callback &callback);

	void registerChangeStateCallback(const Callback &callback);

private:
	void getStateListener(int state, StateMachine::Callback &enterStateCallback, StateMachine::Callback &leaveStateCallback);

private:
	typedef std::map<int, int> StateMap;

	struct EventInfo
	{
		StateMap stateMap;
		Callback beforeEvent;
		Callback afterEvent;
	};
	typedef std::map<std::string, EventInfo> EventMap;


	struct StateListenerInfo
	{
		Callback enterState;
		Callback leaveState;
	};
	typedef std::map<int, StateListenerInfo> StateListenerMap;
	

	EventMap m_eventMap;
	StateListenerMap m_stateListenerMap;

	int m_currentState;

	Callback m_beforeEventCallback;
	Callback m_afterEventCallback;
	Callback m_enterStateCallback;
	Callback m_leaveStateCallback;
	Callback m_changeStateCallback;

};

#endif // StateMachine_h__
