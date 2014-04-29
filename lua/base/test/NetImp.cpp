#include "NetImp.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "NetEngine.h"
#include "VarList.h"
#include "Packet.h"
#include "Log.h"
#include "ScriptEngine.h"
#include "BitStream.h"

NetSocket *GetNetImp()
{	
	static NetImp obj;

	size_t index = 0;
	if (!NetEngine::instance()->find(&obj, index)) 
	{
		NetEngine::instance()->add(&obj);
	}

	BitStream::setDefaultByteOrder(BitStream::LITTLE_ENDIAN);

	return (NetSocket *)&obj;
}

void NetImp::onConnected()
{
	printf("onConnected\n");
	if (ScriptEngine::instance()->getEventHandler("onNetConnected") != INVALID_LUA_FUNCTION)
	{
		VarList args, result;
		ScriptEngine::instance()->callEvent("onNetConnected", args, result);
	}
}

void NetImp::onDisconnect()
{
	printf("onDisconnect\n");
	if (ScriptEngine::instance()->getEventHandler("onNetDisconnect") != INVALID_LUA_FUNCTION)
	{
		VarList args, result;
		ScriptEngine::instance()->callEvent("onNetDisconnect", args, result);
	}
}

int NetImp::onReadLength(unsigned char *buffer, size_t bytes, size_t &offset)
{
	size_t length_size = sizeof(int);
	if (bytes > length_size)
	{
		// read length
		BitStream bs(buffer, bytes);
		int len = bs.readInt32();

		// is whole package
		if (bytes >= length_size + len)
		{
			offset = length_size; 
			return len;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

void NetImp::onRead(BitStream &packet_stream)
{
	Log("do_read:");
	LogHex((char *)packet_stream.buffer(), packet_stream.size());

	VarList args, result;

	// read header
	packet_stream.readInt32();
	packet_stream.readInt32();
	packet_stream.readInt32();
	packet_stream.readInt32();
	packet_stream.readInt32();
	packet_stream.readInt32();
	packet_stream.readInt32();
	packet_stream.readInt32();
	packet_stream.readInt32();

	int id = packet_stream.readInt32();	
	args.add(id);
	while (!packet_stream.isEnd())
	{
		int type = (int)packet_stream.readInt8();
		switch (type)
		{
		case Var::BOOL:
			args.add(packet_stream.readInt8() ? true : false);
			break;
		case Var::BYTE:
			args.add(packet_stream.readInt8());
			break;
		case Var::SHORT:
			args.add(packet_stream.readInt16());
			break;
		case Var::INT:
			args.add(packet_stream.readInt32());
			break;
		case Var::INT64:
			args.add(packet_stream.readInt64());
			break;
		case Var::FLOAT:
			args.add(packet_stream.readFloat());
			break;
		case Var::NUMBER:
			args.add(packet_stream.readDouble());
			break;
		case Var::STRING:
			{
				int length = packet_stream.readInt32();
				assert(length > 0);
				uint8_t *buffer = (uint8_t *)malloc(length);
				assert(buffer);
				packet_stream.readData(buffer, length);
				args.add((const char *)buffer);
			}
			break;
		default:
			assert(false);
			break;
		}
	}

	if (ScriptEngine::instance()->getEventHandler("onNetReceive") != INVALID_LUA_FUNCTION)
	{
		ScriptEngine::instance()->callEvent("onNetReceive", args, result);
	}

}

void NetImp::writePacket( Packet &packet )
{
	VarList &args = ((Packet &)packet).getVarList();

	BitStream bs;

	// write header
	bs.writeInt32(0x100);
	bs.writeInt32(0);
	bs.writeInt32(2);
	bs.writeInt32(0);
	bs.writeInt32(0);
	bs.writeInt32(5);
	bs.writeInt32(6);
	bs.writeInt32(7);
	bs.writeInt32(8);

	// packet to bitstream
	int id = args.get(0).toInt();
	bs.writeInt32(id);
	for (int i=1; i<args.count(); ++i)
	{
		int type = args.get(i).getType();
		switch (type)
		{
		case Var::BOOL:
			bs.writeInt8(args.get(i).toBool() ? 1 : 0);
			break;
		case Var::BYTE:
			bs.writeInt8(args.get(i).toInt());
			break;
		case Var::SHORT:
			bs.writeInt16(args.get(i).toInt());
			break;
		case Var::INT:
			bs.writeInt32(args.get(i).toInt());
			break;
		case Var::INT64:
			bs.writeInt64(args.get(i).toInt64());
			break;
		case Var::FLOAT:
			bs.writeFloat(args.get(i).toFloat());
			break;
		case Var::NUMBER:
			bs.writeDouble(args.get(i).toNumber());
			break;
		case Var::STRING:
			{
				const char *s = args.get(i).toString();
				bs.writeData((uint8_t *)s, strlen(s));
			}
			break;
		default:
			assert(false);
			break;
		}	
	}

	// write length
	BitStream bs_length;
	bs_length.writeInt32(bs.size());
	this->write(bs_length.buffer(), bs_length.size());

	// write data
	this->write(bs.buffer(), bs.size());

	Log("do_write:");
	LogHex((char *)bs.buffer()-4, bs.size()+4);
}
