#ifndef NetImp_h__
#define NetImp_h__

#include "NetSocket.h"

class BitStream;
class VarList;
class NetImp : public NetSocket
{
public:
	void writePack(const VarList &args);

	virtual void onConnected();
	virtual void onDisconnect();
	virtual void onRead(BitStream &stream);
};

extern NetImp *GetNetImp();


#endif // NetImp_h__
