#include "ScriptEngine.h"

// sys
void sys_sleep(int msec);

// net
void net_connect(const char *name, int port);
void net_on_connected(LUA_FUNCTION fn);
void net_disconnect();

// event
void event_register(const char *name, LUA_FUNCTION fn);
void event_unregister(const char *name);
void event_call(const char *name);
