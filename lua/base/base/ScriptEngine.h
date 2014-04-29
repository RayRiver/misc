#ifndef ScriptState_h__
#define ScriptState_h__

#include <string>
#include <map>
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


#include "LuaHelper.h"

class VarList;
class ScriptEngine
{
private:
	ScriptEngine();
public:
	static ScriptEngine *instance();
	virtual ~ScriptEngine();

	bool start(lua_State *L = nullptr);
	void stop();

	inline lua_State *state() { return m_luaState; }

	void registerEvent(const char *name, int lua_function_index);
	void unregisterEvent(const char *name);
	void callEvent(const char *name, const VarList &args, VarList &result);

	LUA_FUNCTION getEventHandler(const char *name);

private:
	lua_State *m_luaState;
	typedef std::map<std::string, LUA_FUNCTION> FUNCTION_MAP;
	typedef std::pair<std::string, LUA_FUNCTION> FUNCTION_MAP_PAIR;
	FUNCTION_MAP m_functionMap;
};

#endif // ScriptState_h__
