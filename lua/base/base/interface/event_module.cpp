#include "ScriptEngine.h"

void event_register(const char *name, LUA_FUNCTION fn)
{
	ScriptEngine::instance()->registerEvent(name, fn);
}

void event_call(const char *name)
{
	ScriptEngine::instance()->callEvent(name);
}

void event_unregister(const char *name)
{
	ScriptEngine::instance()->unregisterEvent(name);
}
