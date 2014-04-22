#ifndef NetImp_h__
#define NetImp_h__

#include "NetSocket.h"

class BitStream;
class NetImp : public NetSocket
{
public:
	virtual void onConnected();
	virtual void onDisconnect();
	virtual void onRead(BitStream &stream);
};

extern NetImp *GetNetImp();


#endif // NetImp_h__
