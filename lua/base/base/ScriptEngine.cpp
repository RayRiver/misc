#include "ScriptEngine.h"

#include <assert.h>
#include "lua.hpp"
#include "tolua_fix.h"

#include "VarList.h"

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

		extern void toluafix_open(lua_State* L);
		toluafix_open(m_luaState);

		extern int luaopen_toluaInterface (lua_State* tolua_S);
		luaopen_toluaInterface(m_luaState);

		extern int luaopen_ScriptInterface(lua_State *L);
		luaopen_ScriptInterface(m_luaState);

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

void ScriptEngine::callEvent( const char *name, const VarList &args, VarList &result )
{
	FUNCTION_MAP::iterator it = m_functionMap.find(name);
	if (it != m_functionMap.end())
	{
		LUA_FUNCTION nHandler = it->second;

		toluafix_get_function_by_refid(m_luaState, nHandler);
		if (lua_isfunction(m_luaState, -1))
		{
			for (size_t i=0; i<args.count(); ++i)
			{
				int type = args.get(i).getType();
				switch (type)
				{
				case Var::BOOL:
					lua_pushboolean(m_luaState, args.get(i).toBool() ? 1 : 0);
					break;
				case Var::INT:
				case Var::INT64:
				case Var::FLOAT:
				case Var::NUMBER:
					lua_pushnumber(m_luaState, args.get(i).toNumber());
					break;
				case Var::STRING:
					lua_pushstring(m_luaState, args.get(i).toString());
					break;
				default:
					break;
				}
			}
			int error = lua_pcall(m_luaState, args.count(), 1, NULL);
			if (error)
			{
				printf("[LUA ERROR] %s\n", lua_tostring(m_luaState, - 1));
				lua_pop(m_luaState, 1); // remove error message from stack
			}
			else
			{
				// get return value
				if (lua_isnumber(m_luaState, -1))
				{
					int ret = lua_tointeger(m_luaState, -1);
					result.add(ret);
				}
				else if (lua_isboolean(m_luaState, -1))
				{
					int ret = lua_toboolean(m_luaState, -1);
					result.add(ret);
				}
				else if (lua_isstring(m_luaState, -1))
				{
					const char *ret = lua_tostring(m_luaState, -1);
					result.add(ret);
				}

				// remove return value from stack
				lua_pop(m_luaState, 1);  
			}
		}

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

LUA_FUNCTION ScriptEngine::getHandler( const char *name )
{
	FUNCTION_MAP::iterator it = m_functionMap.find(name);
	if (it != m_functionMap.end())
	{
		return it->second;
	}
	return 0;
}

