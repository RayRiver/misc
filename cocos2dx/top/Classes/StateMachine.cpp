#include "StateMachine.h"

#include <assert.h>

using namespace std;
USING_NS_CC;

#define _FSMDEBUG

const char *StateMachine::NAME = "StateMachine";

StateMachine::StateMachine()
	: m_currentState(STATE_NONE)
	, m_beforeEventCallback(nullptr)
	, m_afterEventCallback(nullptr)
	, m_leaveStateCallback(nullptr)
	, m_enterStateCallback(nullptr)
	, m_changeStateCallback(nullptr)
{
	this->setName(StateMachine::NAME);
}

StateMachine::~StateMachine()
{

}

void StateMachine::setupState(const char *eventName, int fromState, int toState)
{
	EventMap::iterator itEvent = m_eventMap.find(eventName);
	if (itEvent == m_eventMap.end())
	{
		EventInfo eventInfo;
		eventInfo.beforeEvent = nullptr;
		eventInfo.afterEvent = nullptr;
		m_eventMap[eventName] = eventInfo;
	}

	m_eventMap[eventName].stateMap[fromState] = toState;
}

bool StateMachine::doEvent( const char *eventName )
{
	EventMap::iterator itEvent = m_eventMap.find(eventName);
	if (itEvent == m_eventMap.end())
	{
		return false;
	}
	EventInfo *eventInfo = &(itEvent->second);

	// parse from state and to state
	int fromState = m_currentState;
	int toState = fromState;
	StateMap::iterator itStateMap = eventInfo->stateMap.find(fromState);
	if (itStateMap != eventInfo->stateMap.end())
	{
		toState = eventInfo->stateMap[fromState];
	}
	else
	{
		itStateMap = eventInfo->stateMap.find(StateMachine::STATE_ALL); 
		if (itStateMap != eventInfo->stateMap.end())
		{
			toState = eventInfo->stateMap[StateMachine::STATE_ALL];
		}	
	}

#if defined(_FSMDEBUG)
	log("doEvent: %s, %d -> %d", eventName, fromState, toState);
#endif

	// on before event
	if (eventInfo->beforeEvent) 
	{ 
#if defined(_FSMDEBUG)
		log("doEvent: before this event");
#endif
		eventInfo->beforeEvent(eventName, fromState, toState); 
	}
	if (m_beforeEventCallback) 
	{ 
#if defined(_FSMDEBUG)
		log("doEvent: before any event");
#endif
		m_beforeEventCallback(eventName, fromState, toState); 
	}

	// the same state
	if (fromState == toState)
	{
		// on after event
		if (eventInfo->afterEvent) 
		{ 
#if defined(_FSMDEBUG)
			log("doEvent: after this event");
#endif
			eventInfo->afterEvent(eventName, fromState, toState); 
		}
		if (m_afterEventCallback) 
		{ 
#if defined(_FSMDEBUG)
			log("doEvent: after any event");
#endif
			m_afterEventCallback(eventName, fromState, toState); 
		}
		return true;
	}

	Callback enterStateCallback = nullptr;
	Callback leaveStateCallback = nullptr;

	// on leave state
	this->getStateListener(fromState, enterStateCallback, leaveStateCallback);
	bool ret = true;
	if (leaveStateCallback)
	{
#if defined(_FSMDEBUG)
		log("doEvent: leave this state");
#endif
		ret &= leaveStateCallback(eventName, fromState, toState);
	}
	if (m_leaveStateCallback)
	{
#if defined(_FSMDEBUG)
		log("doEvent: leave any state");
#endif
		ret &= m_leaveStateCallback(eventName, fromState, toState);
	}
	if (!ret) return false;

	// on enter state
	this->getStateListener(toState, enterStateCallback, leaveStateCallback);
	if (enterStateCallback)
	{
#if defined(_FSMDEBUG)
		log("doEvent: enter this state");
#endif
		enterStateCallback(eventName, fromState, toState);
	}
	if (m_enterStateCallback)
	{
#if defined(_FSMDEBUG)
		log("doEvent: enter any state");
#endif
		m_enterStateCallback(eventName, fromState, toState);
	}

	m_currentState = toState;

	// on change state
	if (m_changeStateCallback)
	{
#if defined(_FSMDEBUG)
		log("doEvent: change state");
#endif
		m_changeStateCallback(eventName, fromState, toState);
	}

	// on after event
	if (eventInfo->afterEvent) 
	{ 
#if defined(_FSMDEBUG)
		log("doEvent: after this event");
#endif
		eventInfo->afterEvent(eventName, fromState, toState); 
	}
	if (m_afterEventCallback) 
	{ 
#if defined(_FSMDEBUG)
		log("doEvent: after any event");
#endif
		m_afterEventCallback(eventName, fromState, toState); 
	}

	return true;
}

void StateMachine::registerBeforeEventCallback( const char *eventName, const Callback &callback )
{
	EventInfo *pEventInfo = nullptr;
	EventMap::iterator itEvent = m_eventMap.find(eventName);
	if (itEvent == m_eventMap.end())
	{
		EventInfo eventInfo;
		eventInfo.beforeEvent = nullptr;
		eventInfo.afterEvent = nullptr;
		m_eventMap.insert(pair<std::string, EventInfo>(eventName, eventInfo));
		pEventInfo = &(m_eventMap[eventName]);
	}
	else
	{
		pEventInfo = &(itEvent->second);
	}

	pEventInfo->beforeEvent = callback;
}

void StateMachine::registerAfterEventCallback( const char *eventName, const Callback &callback )
{
	EventInfo *pEventInfo = nullptr;
	EventMap::iterator itEvent = m_eventMap.find(eventName);
	if (itEvent == m_eventMap.end())
	{
		EventInfo eventInfo;
		eventInfo.beforeEvent = nullptr;
		eventInfo.afterEvent = nullptr;
		m_eventMap.insert(pair<std::string, EventInfo>(eventName, eventInfo));
		pEventInfo = &(m_eventMap[eventName]);
	}
	else
	{
		pEventInfo = &(itEvent->second);
	}

	pEventInfo->afterEvent = callback;;
}

void StateMachine::registerEnterStateCallback( int state, const Callback &callback )
{
	StateListenerInfo *pStateListenerInfo = nullptr;
	StateListenerMap::iterator itStateListener = m_stateListenerMap.find(state);
	if (itStateListener == m_stateListenerMap.end())
	{
		StateListenerInfo stateListenerInfo;
		stateListenerInfo.enterState = nullptr;
		stateListenerInfo.leaveState = nullptr;
		m_stateListenerMap.insert(pair<int, StateListenerInfo>(state, stateListenerInfo));
		pStateListenerInfo = &(m_stateListenerMap[state]);
	}
	else
	{
		pStateListenerInfo = &(itStateListener->second);
	}

	pStateListenerInfo->enterState = callback;
}

void StateMachine::registerLeaveStateCallback( int state, const Callback &callback )
{
	StateListenerInfo *pStateListenerInfo = nullptr;
	StateListenerMap::iterator itStateListener = m_stateListenerMap.find(state);
	if (itStateListener == m_stateListenerMap.end())
	{
		StateListenerInfo stateListenerInfo;
		stateListenerInfo.enterState = nullptr;
		stateListenerInfo.leaveState = nullptr;
		m_stateListenerMap.insert(pair<int, StateListenerInfo>(state, stateListenerInfo));
		pStateListenerInfo = &(m_stateListenerMap[state]);
	}
	else
	{
		pStateListenerInfo = &(itStateListener->second);
	}

	pStateListenerInfo->leaveState = callback;
}

void StateMachine::registerBeforeEventCallback( const Callback &callback )
{
	m_beforeEventCallback = callback;
}

void StateMachine::registerAfterEventCallback( const Callback &callback )
{
	m_afterEventCallback = callback;
}

void StateMachine::registerEnterStateCallback( const Callback &callback )
{
	m_enterStateCallback = callback;
}

void StateMachine::registerLeaveStateCallback( const Callback &callback )
{
	m_leaveStateCallback = callback;
}

void StateMachine::registerChangeStateCallback( const Callback &callback )
{
	m_changeStateCallback = callback;
}

void StateMachine::getStateListener(int state, StateMachine::Callback &enterStateCallback, StateMachine::Callback &leaveStateCallback)
{
	StateListenerMap::iterator itStateListener = m_stateListenerMap.find(state);
	if (itStateListener != m_stateListenerMap.end())
	{
		StateListenerInfo *pStateListenerInfo = &(itStateListener->second);
		enterStateCallback = pStateListenerInfo->enterState;
		leaveStateCallback = pStateListenerInfo->leaveState;
	}
	else
	{
		enterStateCallback = nullptr;
		leaveStateCallback = nullptr;
	}
}

