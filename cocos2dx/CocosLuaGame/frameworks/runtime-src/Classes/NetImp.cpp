#include "NetImp.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "NetManager.h"
#include "Log.h"
#include "BitStream.h"

#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "LuaValueList.h"
#include "EventDef.h"
#include "LuaScriptHandlerMgr.h"

USING_NS_CC;

enum VarType
{
	VAR_UNDEFINED,
	VAR_BOOL,
	VAR_INT,
	VAR_FLOAT,
	VAR_STRING,
	VAR_RESERVED_DONT_USE_1, // wide string
	VAR_RESERVED_DONT_USE_2, // object
	VAR_RESERVED_DONT_USE_3, // pointer
	VAR_RESERVED_DONT_USE_4, // userdata

	VAR_INT64,
	VAR_NUMBER,

	VAR_BYTE,
	VAR_SHORT,
};


static int handleUserExtEvent(int handler, cocos2d::ScriptHandlerMgr::HandlerType handlerType, cocos2d::LuaValueArray &args)
{
	cocos2d::LuaStack *stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
	stack->pushInt((int)handlerType);
	stack->pushLuaValueArray(args);
	int ret = stack->executeFunctionByHandler(handler, 2);
	stack->clean();
	return ret;
}

static void sendCustomEvent(void *object, cocos2d::ScriptHandlerMgr::HandlerType handlerType, cocos2d::LuaValueArray &args)
{
#if CC_ENABLE_SCRIPT_BINDING
	int nHandler = cocos2d::ScriptHandlerMgr::getInstance()->getObjectHandler((void*)object, handlerType);
	if (0 != nHandler) 
	{
		handleUserExtEvent(nHandler, handlerType, args);
	}
#endif // #if CC_ENABLE_SCRIPT_BINDING
}

NetSocket *GetNetImp()
{	
	static NetImp obj;

	size_t index = 0;
	if (!NetManager::instance()->find(&obj, index)) 
	{
		NetManager::instance()->add(&obj);
	}

	BitStream::setDefaultByteOrder(BitStream::LITTLE_ENDIAN);

	return (NetSocket *)&obj;
}

void NetImp::onConnected()
{
	LuaValueArray args;
	args.push_back(LuaValue::stringValue("onConnected"));
	sendCustomEvent((void *)this, EVENT_USEREXT_CUSTOM_NETWORK, args);
}

void NetImp::onDisconnect()
{
	LuaValueArray args;
	args.push_back(LuaValue::stringValue("onDisconnect"));
	sendCustomEvent((void *)this, EVENT_USEREXT_CUSTOM_NETWORK, args);
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

	LuaValueArray args;
	args.push_back(LuaValue::stringValue("onReceive"));

	int id = packet_stream.readInt32();	
	args.push_back(LuaValue::intValue(id));
	while (!packet_stream.isEnd())
	{
		int type = (int)packet_stream.readInt8();
		switch (type)
		{
		case VAR_BOOL:
			args.push_back(LuaValue::booleanValue(packet_stream.readInt8() ? true : false));
			break;
		case VAR_BYTE:
			args.push_back(LuaValue::intValue(packet_stream.readInt8()));
			break;
		case VAR_SHORT:
			args.push_back(LuaValue::intValue(packet_stream.readInt16()));
			break;
		case VAR_INT:
			args.push_back(LuaValue::intValue(packet_stream.readInt32()));
			break;
		case VAR_INT64:
			args.push_back(LuaValue::intValue(packet_stream.readInt64()));
			break;
		case VAR_FLOAT:
			args.push_back(LuaValue::floatValue(packet_stream.readFloat()));
			break;
		case VAR_NUMBER:
			args.push_back(LuaValue::floatValue(packet_stream.readDouble()));
			break;
		case VAR_STRING:
			{
				int length = packet_stream.readInt16();
				assert(length >= 0);
				if (length == 0)
				{
					args.push_back(LuaValue::stringValue(""));
				}
				else
				{
					uint8_t *buffer = (uint8_t *)malloc(length+1);
					assert(buffer);
					packet_stream.readData(buffer, length);
					buffer[length] = 0;
					args.push_back(LuaValue::stringValue((const char *)buffer));
					free(buffer);
				}
			}
			break;
		default:
			assert(false);
			break;
		}
	}

	sendCustomEvent((void *)this, EVENT_USEREXT_CUSTOM_NETWORK, args);

}

void NetImp::writePacket( unsigned int id, const LuaValueList &args )
{
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
	bs.writeInt32(id);
	for (int i=0; i<args.size(); ++i)
	{
		int type = args.getValue(i).getType();
		switch (type)
		{
		case LuaValueTypeInt:
			bs.writeInt8(VAR_INT);
			bs.writeInt32(args.getValue(i).intValue());
			break;
		case LuaValueTypeFloat:
			bs.writeInt8(VAR_FLOAT);
			bs.writeFloat(args.getValue(i).floatValue());
			break;
		case LuaValueTypeBoolean:
			bs.writeInt8(VAR_BYTE);
			bs.writeInt8(args.getValue(i).booleanValue() ? 1 : 0);
			break;
		case LuaValueTypeString:
			{
				std::string s = args.getValue(i).stringValue();
				bs.writeInt8(VAR_STRING);
				bs.writeInt16(s.length());
				bs.writeData((uint8_t *)s.c_str(), s.length());
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
	LogHex((char *)bs_length.buffer(), bs_length.size());
	LogHex((char *)bs.buffer(), bs.size());
}
