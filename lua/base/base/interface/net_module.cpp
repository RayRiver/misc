#include "ScriptEngine.h"
#include "NetImp.h"

void net_connect(const char *hostname, int port)
{
	GetNetImp()->connect(hostname, (unsigned short)port);
}

void net_on_connected(LUA_FUNCTION fn)
{

}

void net_disconnect()
{
	GetNetImp()->disconnect();
}