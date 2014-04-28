#include "LuaHelper.h"

#define LUAHELPER_REFID_FUNCTION_MAPPING "LuaHelper_refid_function_mapping"

void LuaHelper::printStack( lua_State *L, const char *info )
{
	printf("=====>> %s <<=====\n", info);

	int count = lua_gettop(L);
	for (int i=count; i>0; --i)
	{
		if (i == count)
			printf("-> %02d: ", i);
		else
			printf("   %02d: ", i);
		int type = lua_type(L, i);
		switch (type)
		{
		case LUA_TNIL:
			printf("nil");
			break;
		case LUA_TBOOLEAN:
			printf("%s", lua_toboolean(L, i) ? "true" : "false");
			break;
		case LUA_TLIGHTUSERDATA:
			printf("light userdata <0x%x>", lua_topointer(L, i));
			break;
		case LUA_TNUMBER:
			printf("%lf", lua_tonumber(L, i));
			break;
		case LUA_TSTRING:
			printf("%s", lua_tostring(L, i));
			break;
		case LUA_TTABLE:
			printf("table <0x%x>", lua_topointer(L, i));
			break;
		case LUA_TFUNCTION:
			printf("function <0x%x>", lua_topointer(L, i));
			break;
		case LUA_TUSERDATA:
			printf("userdata <0x%x>", lua_touserdata(L, i));
			break;
		case LUA_TTHREAD:
			printf("thread <0x%x>", lua_tothread(L, i));
			break;
		default:
			break;
		}
		printf("\n");
	}

	printf("==============================\n\n");
}

int LuaHelper::s_function_ref_id = 0;

void LuaHelper::init(lua_State *L)
{
	lua_pushstring(L, LUAHELPER_REFID_FUNCTION_MAPPING);
	lua_newtable(L);
	lua_rawset(L, LUA_REGISTRYINDEX);
}

LUA_FUNCTION LuaHelper::addRefFunction(lua_State* L, int lo, int def)
{
	// function at lo
	if (!lua_isfunction(L, lo)) return 0;

	LUA_FUNCTION function_ref_id = (int)(lua_topointer(L,lo));
	lua_pushstring(L, LUAHELPER_REFID_FUNCTION_MAPPING);
	lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: fun ... refid_fun */
	lua_pushinteger(L, function_ref_id);						/* stack: fun ... refid_fun refid */
	lua_pushvalue(L, lo);                                       /* stack: fun ... refid_fun refid fun */

	lua_rawset(L, -3);											/* refid_fun[refid] = fun, stack: fun ... refid_ptr */
	lua_pop(L, 1);                                              /* stack: fun ... */

	return function_ref_id;
}

void LuaHelper::getRefFunction(lua_State* L, int refid)
{
	lua_pushstring(L, LUAHELPER_REFID_FUNCTION_MAPPING);
	lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: ... refid_fun */
	lua_pushinteger(L, refid);                                  /* stack: ... refid_fun refid */
	lua_rawget(L, -2);                                          /* stack: ... refid_fun fun */
	lua_remove(L, -2);                                          /* stack: ... fun */
}

void LuaHelper::removeRefFunction(lua_State* L, int refid)
{
	lua_pushstring(L, LUAHELPER_REFID_FUNCTION_MAPPING);
	lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: ... refid_fun */
	lua_pushinteger(L, refid);                                  /* stack: ... refid_fun refid */
	lua_pushnil(L);                                             /* stack: ... refid_fun refid nil */
	lua_rawset(L, -3);											/* refid_fun[refid] = fun, stack: ... refid_ptr */
	lua_pop(L, 1);                                              /* stack: ... */
}
