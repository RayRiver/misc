// base.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>

#include "lua.hpp"

#include "Sys.h"
#include "BitStream.h"
#include "Var.h"
#include "VarList.h"
#include "ThreadObj.h"
#include "ThreadManager.h"
#include "StreamBuffer.h"
#include "NetEngine.h"
#include "NetSocket.h"
#include "ScriptEngine.h"

void test_socket()
{
	NetEngine::instance()->start();

	class TestSocket : public NetSocket
	{
	public:
		void onConnected()
		{
			printf("onConnected\n");
			this->write((unsigned char *)"12345678", 11);
		}
		void onDisconnect()
		{
			printf("onDisconnect\n");
		}
		void onRead(BitStream &stream)
		{
			printf("onRead %u\n", stream.size());
		}
	};

	NetSocket *sock = new TestSocket();
	NetEngine::instance()->add(sock);
	sock->connect("127.0.0.1", 60000);

	while (1)
	{
		NetEngine::instance()->update();
		Sleep(100);
	}

	NetEngine::instance()->stop();
}

void test_thread()
{
	class TestThreadObj : public ThreadObj
	{
	public:
		void run()
		{
			printf("test thread obj run.\n");
			while (isRunning())
			{
				Sleep(1000);
				printf("thread loop...\n");
			}
		}
		void finish()
		{
			printf("test thread obj finish.\n");
		}
	};

	ThreadManager::instance()->start(new TestThreadObj(), "testthread");

	Sleep(5000);
	ThreadManager::instance()->stop("testthread");
}

void test_varlist()
{
	VarList args;	
	args.add(1);
	args.add("ddddd");
	args.add(true);
	printf("args count: %d\n", args.count());
	printf("args 0: %d\n", args.get(0).toInt());
	printf("args 1: %s\n", args.get(1).toString());
	printf("args 2: %s\n", args.get(2).toBool() ? "true" : "false");
}

void test_tolua()
{
	{
		NetEngine::instance()->start();
	}

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	extern int luaopen_toluaInterface (lua_State* tolua_S);
	luaopen_toluaInterface(L);

	//extern int luaopen_ScriptInterface(lua_State *L);
	//luaopen_ScriptInterface(L);

	int e = luaL_dofile(L, "script/main.lua");
	if ( e ) {
		printf("%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	// main loop
	while (true)
	{
		NetEngine::instance()->update();
		Sys::sleep(100);
	}

	lua_close(L);

	{
		NetEngine::instance()->stop();
	}

}

void test_bitstream()
{
	BitStream bs;
	bs.writeInt8(123);
	bs.writeInt16(122);
	bs.writeInt32(121);
	bs.writeInt64(120);
	bs.writeFloat(1.0f);
	bs.writeDouble(2.0);
	bs.writeData((uint8_t *)"1234\x00", 5);
	bs.writeFloat(3.0f);

	printf("readInt8:  %d\n", bs.readInt8());
	printf("readInt16: %d\n", bs.readInt16());
	printf("readInt32: %d\n", bs.readInt32());
	printf("readInt64: %I64d\n", bs.readInt64());
	printf("readFloat: %f\n", bs.readFloat());
	printf("readDouble: %lf\n", bs.readDouble());
	char buffer[32];
	memset(buffer, 0x00, sizeof(buffer));
	printf("readData: %s\n", bs.readData((uint8_t *)buffer, 5));
	printf("readFloat: %f\n", bs.readFloat());
}

void script_main()
{
	NetEngine::instance()->start();
	ScriptEngine::instance()->start();

	// main loop
	while (true)
	{
		NetEngine::instance()->update();
		Sys::sleep(100);
	}

	ScriptEngine::instance()->stop();
	NetEngine::instance()->stop();
}

int main(int argc, char* argv[])
{
	script_main();
	system("pause");
	return 0;
}

