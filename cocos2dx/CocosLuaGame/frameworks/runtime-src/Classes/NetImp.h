#ifndef NetImp_h__
#define NetImp_h__

#include "NetSocket.h"

class BitStream;
class LuaValueList;
class NetImp : public NetSocket
{
public:
	virtual void onConnected();
	virtual void onDisconnect();
	virtual int onReadLength(unsigned char *buffer, size_t size, size_t &offset);
	virtual void onRead(BitStream &stream);

	virtual void writePacket(unsigned int id, const LuaValueList &args);

};

#define EVENT_USEREXT_CUSTOM_NETWORK (ScriptHandlerMgr::HandlerType)((int)ScriptHandlerMgr::HandlerType::EVENT_CUSTOM_BEGAN+1) 

#endif // NetImp_h__
