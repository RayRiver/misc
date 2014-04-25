#include "NetImp.h"

#include "lua.hpp"
#include "NetEngine.h"
#include "VarList.h"
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

void NetImp::onRead(BitStream &bs)
{
	printf("onRead %u\n", bs.size());
	if (ScriptEngine::instance()->getEventHandler("onNetReceive") != INVALID_LUA_FUNCTION)
	{
		VarList args, result;

		int id = bs.readInt32();	
		args.add(id);
		while (!bs.isEnd())
		{
			int type = (int)bs.readInt8();
			switch (type)
			{
			case Var::BOOL:
				args.add(bs.readInt8() ? true : false);
				break;
			case Var::INT:
				args.add(bs.readInt32());
				break;
			case Var::INT64:
				args.add(bs.readInt64());
				break;
			case Var::FLOAT:
				args.add(bs.readFloat());
				break;
			case Var::NUMBER:
				args.add(bs.readDouble());
				break;
			case Var::STRING:
				{
					int length = bs.readInt32();
					assert(length > 0);
					uint8_t *buffer = (uint8_t *)malloc(length);
					assert(buffer);
					bs.readData(buffer, length);
					args.add((const char *)buffer);
				}
				break;
			default:
				assert(false);
				break;
			}
		}
		
		ScriptEngine::instance()->callEvent("onNetReceive", args, result);
	}
}

void NetImp::writePack( const VarList &args )
{
	assert(args.count() >= 1);

	BitStream bs;
	int id = args.get(0).toInt();
	bs.writeInt32(id);
	for (size_t i=1; i<args.count(); ++i)
	{
		int type = args.get(i).getType();
		switch (type)
		{
		case Var::BOOL:
			bs.writeInt8(args.get(i).toBool() ? 1 : 0);
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

	this->write(bs.buffer(), bs.size());
}
