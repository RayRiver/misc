#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"

bool g_ignoreAssert;

static int show_error(lua_State* L)
{
	if (g_ignoreAssert)
	{
		return 0;
	}

	luaL_checktype(L, 1, LUA_TSTRING);

	const char* msg = lua_tostring(L, 1);

	std::string s = msg;
	s += "\n";
	s += "Press 'Abort' to end the programe.\n";
	s += "Press 'Retry' to ignore this assert.\n";
	s += "Press 'Ignore' to ignore all asserts in the future.\n";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	int ret = ::MessageBoxA(nullptr, s.c_str(), "Lua Assert Failed", MB_ABORTRETRYIGNORE);
	if (ret == IDABORT)
	{
		cocos2d::Director::getInstance()->end();
	}
	else if (ret == IDRETRY)
	{
		
	}
	else if (ret == IDIGNORE)
	{
		g_ignoreAssert = true;
	}
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
	g_ignoreAssert = false;

	luaL_register(L, "helper", helperlib);
	return 0;
}
