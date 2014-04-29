#ifndef LuaHelper_h__
#define LuaHelper_h__

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


typedef int LUA_FUNCTION;
#define INVALID_LUA_FUNCTION 0

class LuaHelper
{
public:
	static void printStack(lua_State *L, const char *info = "???");

	static void init(lua_State *L);
	static int LuaHelper::addRefFunction(lua_State* L, int lo, int def);
	static void LuaHelper::getRefFunction(lua_State* L, int refid);
	static void LuaHelper::removeRefFunction(lua_State* L, int refid);

private:
	static int s_function_ref_id;
};

#endif // LuaHelper_h__
