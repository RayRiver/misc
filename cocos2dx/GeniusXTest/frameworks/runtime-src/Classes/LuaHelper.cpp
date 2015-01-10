#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"

static int show_error(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TSTRING);

	const char* msg = lua_tostring(L, 1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	::MessageBoxA(nullptr, msg, "Lua Assert Failed", MB_OK);
#endif

	return 0;
}

static const luaL_Reg helperlib[] = 
{
	"show_error", show_error,
	NULL, NULL
};

int register_all_luahelper(lua_State *L)
{
	luaL_register(L, "helper", helperlib);
	return 0;
}
