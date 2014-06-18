#include "ScriptFunctions.h"

#include "cocos2d.h"
#include "LuaScriptHandlerMgr.h"

#include "NetManager.h"
#include "NetSocket.h"
#include "NetImp.h"
#include "LuaValueList.h"

USING_NS_CC;

void network_start()
{
	if (!NetManager::instance()->isStarted())
	{
		NetManager::instance()->start();
	}
}

void network_stop()
{
	NetManager::instance()->stop();
}

void network_connect(const char *hostname, unsigned short port)
{
	GetNetImp()->connect(hostname, port);	
}

void network_disconnect()
{
	GetNetImp()->disconnect();
}

void network_send(unsigned int id, const LuaValueList &args)
{
	GetNetImp()->writePacket(id, args);
}

void network_registerHandler(LUA_FUNCTION handler)
{
	ScriptHandlerMgr::getInstance()->addObjectHandler(GetNetImp(), handler, EVENT_USEREXT_CUSTOM_NETWORK);
}

void network_unregisterHandler()
{
	ScriptHandlerMgr::getInstance()->removeObjectAllHandlers(GetNetImp());
}
