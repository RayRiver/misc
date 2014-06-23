#include "EntityComponent.h"

#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "LuaValueList.h"
#include "EventDef.h"
#include "LuaScriptHandlerMgr.h"

USING_NS_CC;

EntityComponent* EntityComponent::create( void )
{
	EntityComponent * ret = new EntityComponent();
	if (ret != nullptr && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

EntityComponent::EntityComponent()
{

}

EntityComponent::~EntityComponent()
{
	ScriptHandlerMgr::getInstance()->removeObjectAllHandlers((void *)this);
}

void EntityComponent::onEnter()
{
	Component::onEnter();

#if CC_ENABLE_SCRIPT_BINDING
	if (_scriptType == kScriptTypeLua)
	{
		int nHandler = cocos2d::ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, EVENT_USEREXT_CUSTOM_COMPONENT_ONENTER);
		if (0 != nHandler) 
		{
			cocos2d::LuaStack *stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
			int ret = stack->executeFunctionByHandler(nHandler, 0);
			stack->clean();
		}
	}
#endif // CC_ENABLE_SCRIPT_BINDING
}

void EntityComponent::onExit()
{
	Component::onExit();

#if CC_ENABLE_SCRIPT_BINDING
	if (_scriptType == kScriptTypeLua)
	{
		int nHandler = cocos2d::ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, EVENT_USEREXT_CUSTOM_COMPONENT_ONEXIT);
		if (0 != nHandler) 
		{
			cocos2d::LuaStack *stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
			int ret = stack->executeFunctionByHandler(nHandler, 0);
			stack->clean();
		}
	}
#endif // CC_ENABLE_SCRIPT_BINDING
}

void EntityComponent::update( float dt )
{
	Component::update(dt);

#if CC_ENABLE_SCRIPT_BINDING
	if (_scriptType == kScriptTypeLua)
	{
		int nHandler = cocos2d::ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, EVENT_USEREXT_CUSTOM_COMPONENT_ONFRAME);
		if (0 != nHandler) 
		{
			cocos2d::LuaStack *stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
			stack->pushFloat(dt);
			int ret = stack->executeFunctionByHandler(nHandler, 1);
			stack->clean();
		}
	}
#endif // CC_ENABLE_SCRIPT_BINDING
}

void EntityComponent::registerHandler( const char *event_name, LUA_FUNCTION handler )
{
	if (strcmp(event_name, "enter") == 0)
	{
		ScriptHandlerMgr::getInstance()->addObjectHandler((void *)this, handler, EVENT_USEREXT_CUSTOM_COMPONENT_ONENTER);
	}
	else if (strcmp(event_name, "exit") == 0)
	{
		ScriptHandlerMgr::getInstance()->addObjectHandler((void *)this, handler, EVENT_USEREXT_CUSTOM_COMPONENT_ONEXIT);
	}
	else if (strcmp(event_name, "frame") == 0)
	{
		ScriptHandlerMgr::getInstance()->addObjectHandler((void *)this, handler, EVENT_USEREXT_CUSTOM_COMPONENT_ONFRAME);
	}
	else
	{
		CCASSERT(false, "");
	}
}

void EntityComponent::unregisterHandler(const char *event_name)
{
	if (strcmp(event_name, "enter") == 0)
	{
		ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)this, EVENT_USEREXT_CUSTOM_COMPONENT_ONENTER);
	}
	else if (strcmp(event_name, "exit") == 0)
	{
		ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)this, EVENT_USEREXT_CUSTOM_COMPONENT_ONEXIT);
	}
	else if (strcmp(event_name, "frame") == 0)
	{
		ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)this, EVENT_USEREXT_CUSTOM_COMPONENT_ONFRAME);
	}
	else
	{
		CCASSERT(false, "");
	}
}

void EntityComponent::unregisterAllHandlers()
{
	ScriptHandlerMgr::getInstance()->removeObjectAllHandlers((void *)this);
}

