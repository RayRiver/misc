#include "NetImp.h"

#include "lua.hpp"
#include "NetEngine.h"

#include "ScriptEngine.h"

NetImp *GetNetImp()
{	
	static NetImp obj;

	size_t index = 0;
	if (!NetEngine::instance()->find(&obj, index)) 
	{
		NetEngine::instance()->add(&obj);
	}

	return &obj;
}

void NetImp::onConnected()
{
	printf("onConnected\n");
}

void NetImp::onDisconnect()
{
	printf("onDisconnect\n");
}

void NetImp::onRead(BitStream &stream)
{
	printf("onRead %u\n", stream.size());
}