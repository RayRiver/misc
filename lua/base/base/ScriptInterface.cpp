#include "lua.hpp"
#include "Sys.h"
#include "NetImp.h"
#include "VarList.h"
#include "ScriptEngine.h"
#include "tolua_fix.h"

static int sys_sleep(lua_State *L)
{
	::luaL_checktype(L, 1, LUA_TNUMBER);
	int msec = (int)lua_tointeger(L, 1);
	Sys::sleep(msec);
	return 0;
}

static const luaL_Reg syslib[] =
{
	"sleep", sys_sleep,
	NULL, NULL
};

static int net_connect(lua_State *L)
{
	::luaL_checktype(L, 1, LUA_TSTRING);
	::luaL_checktype(L, 2, LUA_TNUMBER);
	const char *hostname = lua_tostring(L, 1);
	unsigned short port = (unsigned short)lua_tointeger(L, 2);
	GetNetImp()->connect(hostname, port);
	return 0;
}

static int net_disconnect(lua_State *L)
{
	GetNetImp()->disconnect();
	return 0;
}

static const luaL_Reg netlib[] =
{
	"connect", net_connect,
	"disconnect", net_disconnect,
	NULL, NULL
};

static int event_register(lua_State *L)
{
	::luaL_checktype(L, 1, LUA_TSTRING);
	::luaL_checktype(L, 2, LUA_TFUNCTION);

	const char *name = lua_tostring(L, 1);

	// add function ref
	LUA_FUNCTION nHandler = toluafix_ref_function(L, 2, 0);
	//LUA_FUNCTION nHandler = (LUA_FUNCTION)lua_topointer(L, 2);

	ScriptEngine::instance()->registerEvent(name, nHandler);
	return 0;
}

static int event_unregister(lua_State *L)
{
	::luaL_checktype(L, 1, LUA_TSTRING);
	const char *name = lua_tostring(L, 1);
	ScriptEngine::instance()->unregisterEvent(name);

	// remove function ref
	toluafix_get_function_by_refid(L, ScriptEngine::instance()->getHandler(name));
	LUA_FUNCTION nHandler = lua_tointeger(L, 1);
	toluafix_remove_function_by_refid(L, nHandler);
	lua_pop(L, 1);

	return 0;
}

static int event_call(lua_State *L)
{
	::luaL_checktype(L, 1, LUA_TSTRING);
	const char *name = lua_tostring(L, 1);

	// parse arguements
	VarList args, result;
	int count = lua_gettop(L) - 1;
	for (int i=2; i<=count+1; ++i)
	{
		if (lua_isboolean(L, i))
		{
			bool val = lua_toboolean(L, i) ? true : false;
			args.add(val);
		}
		else if (lua_isnumber(L, i))
		{
			args.add(lua_tonumber(L, i));
		}
		else if (lua_isstring(L, i))
		{
			args.add(lua_tostring(L, i));
		}
		else if (lua_isnil(L, i))
		{
			assert(false);
		}
		else
		{
			assert(false);
		}
	}

	// call lua function
	ScriptEngine::instance()->callEvent(name, args, result);

	// parse return values
	int result_count = result.count();
	for (int i=0; i<result_count; ++i)
	{
		switch (result.get(i).getType())
		{
		case Var::BOOL:
			lua_pushboolean(L, result.get(i).toBool() ? 1 : 0);
			break;
		case Var::INT:
		case Var::INT64:
		case Var::FLOAT:
		case Var::NUMBER:
			lua_pushnumber(L, result.get(i).toNumber());
			break;
		case Var::STRING:
			lua_pushstring(L, result.get(i).toString());
			break;
		default:
			assert(false);
			break;
		}
	}

	return result_count;
}

static const luaL_Reg eventlib[] =
{
	"register", event_register,
	"unregister", event_unregister,
	"call", event_call,
	NULL, NULL
};

int luaopen_ScriptInterface(lua_State *L)
{
	::luaL_register(L, "sys", syslib);
	::luaL_register(L, "net", netlib);
	::luaL_register(L, "event", eventlib);
	return 1;
}