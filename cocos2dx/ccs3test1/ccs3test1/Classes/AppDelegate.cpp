#include "AppDelegate.h"

#include "Config.h"
#include "HelloWorldScene.h"
#include "Box2dTest.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();

    director->setOpenGLView(eglView);

	eglView->setDesignResolutionSize(854, 480, ResolutionPolicy::NO_BORDER);
	
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	//extern int raknet_test();
	//raknet_test();

	LOAD_CONFIG("global");	
	//int x = 0;
	//READ_CONFIG("global", "test", x);	
	//log("xxx: %d", x);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}




#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"
#include "RakSleep.h"
#include "BitStream.h"
#include "GetTime.h"

using namespace std;
using namespace RakNet;

const int SOCKET_PORT = 30050;

//#define log(fmt, ...) printf(fmt"\n", __VA_ARGS__) 

enum ENUM_USER_PACKET_DEFINE
{
	_USER_PACKET_DEFINE_START = ID_USER_PACKET_ENUM,

	ID_UP_TEST_PACKET,
};

bool g_bServerReady = false;
bool g_bRakNetTestOK = false;

void server_task()
{
	auto server = RakNet::RakPeerInterface::GetInstance();

	RakNet::SocketDescriptor sd;
	sd.port = SOCKET_PORT;

	auto ret = server->Startup(1024, &sd, 1);
	if (ret != RakNet::RAKNET_STARTED)
	{
		log(">>>> server startup failed");
		return;
	}
	log(">>>>> server startup on port %d", SOCKET_PORT);
	server->SetMaximumIncomingConnections(2);
	g_bServerReady = true;

	while (true)
	{
		auto packet = server->Receive();
		if (packet)
		{
			switch (packet->data[0])
			{
			default:
				break;
			}
			log(">>>>> receive packet %d", packet->data[0]);
			g_bRakNetTestOK = true;
			break;
		}

		RakSleep(1000);	
	}
}

void client_task()
{
	RakNet::RakPeerInterface *client = RakNet::RakPeerInterface::GetInstance();

	RakNet::SocketDescriptor sd;
	sd.port = 0;

	client->Startup(1, &sd, 1);
	auto ret = client->Connect("127.0.0.1", SOCKET_PORT, NULL, 0, 0);
	if (ret != RakNet::CONNECTION_ATTEMPT_STARTED)
	{
		log("connect failed");
		return;
	}
	log("connect ok");

	unsigned char useTimeStamp = ID_TIMESTAMP;
	RakNet::Time timeStamp = RakNet::GetTime();
	unsigned char typeId = ID_UP_TEST_PACKET;
	BitStream bs;
	bs.Write(useTimeStamp);
	bs.Write(timeStamp);
	bs.Write(typeId);

	client->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);

}

int raknet_test()
{
	thread t(server_task);
	while (!g_bServerReady)
	{
		RakSleep(1000);
	}
	client_task();
	t.join();

	return 0;
}
