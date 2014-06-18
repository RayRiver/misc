#ifndef ScriptFunctions_h__
#define ScriptFunctions_h__

#include "cocos2d.h"
#include "CCLuaValue.h"

USING_NS_CC;

class LuaValueList;

void network_start();
void network_stop();
void network_connect(const char *hostname, unsigned short port);
void network_disconnect();
void network_send(unsigned int id, const LuaValueList &args);
void network_registerHandler(LUA_FUNCTION handler);
void network_unregisterHandler();

#endif // ScriptFunctions_h__
