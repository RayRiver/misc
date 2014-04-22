#include "ScriptEngine.h"

#include <assert.h>
#include "lua.hpp"
#include "tolua_fix.h"

ScriptEngine * ScriptEngine::instance()
{
	static ScriptEngine obj;
	return &obj;
}

ScriptEngine::ScriptEngine()
	: m_luaState(nullptr)
{

}

ScriptEngine::~ScriptEngine()
{

}

bool ScriptEngine::start()
{
	if (!m_luaState)
	{
		m_luaState = luaL_newstate();
		if (!m_luaState)
		{
			return false;
		}
		luaL_openlibs(m_luaState);

		extern int luaopen_toluaInterface (lua_State* tolua_S);
		luaopen_toluaInterface(m_luaState);

		//extern int luaopen_ScriptInterface(lua_State *L);
		//luaopen_ScriptInterface(m_luaState);

		int e = luaL_dofile(m_luaState, "script/main.lua");
		if ( e ) {
			printf("%s\n", lua_tostring(m_luaState, -1));
			lua_pop(m_luaState, 1);
			return false;
		}

		return true;
	}
	else
	{
		assert(false);
		return true;
	}
}

void ScriptEngine::stop()
{
	lua_close(m_luaState);
	m_luaState = nullptr;
}

void ScriptEngine::registerEvent( const char *name, LUA_FUNCTION fn )
{
	m_functionMap[name] = fn;
}

void ScriptEngine::unregisterEvent( const char *name )
{
	FUNCTION_MAP::iterator it = m_functionMap.find(name);
	if (it != m_functionMap.end())
	{
		m_functionMap.erase(it);
	}
}

void ScriptEngine::callEvent( const char *name )
{
	FUNCTION_MAP::iterator it = m_functionMap.find(name);
	if (it != m_functionMap.end())
	{
		LUA_FUNCTION nHandler = it->second;
		/*
		// TODO
		int ret = 0;

		// push function by handler
		toluafix_get_function_by_refid(m_luaState, nHandler);
		if (lua_isfunction(m_luaState, -1))
		{
			if (numArgs > 0)
			{
				lua_insert(m_state, -(numArgs + 1));                     
			}
			ret = executeFunction(numArgs);	
		}
		else
		{
			printf("[LUA ERROR] function refid '%d' does not reference a Lua function\n", nHandler);
			lua_pop(m_state, 1);
		}
		lua_settop(m_luaState, 0);
		*/

	}
}

