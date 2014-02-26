// raknettest1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

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

#define log(fmt, ...) printf(fmt"\n", __VA_ARGS__) 
#define serverlog(fmt, ...) printf(">>>>> "fmt"\n", __VA_ARGS__) 

enum ENUM_USER_PACKET_DEFINE
{
	_USER_PACKET_DEFINE_START = ID_USER_PACKET_ENUM,

	ID_USER_PACKET,
};

bool g_bServerStarted = false;

unsigned char getPacketIdentifier(Packet *p)
{
	if (p == 0)
	{
		return 0xff;
	}

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char)p->data[sizeof(MessageID) + sizeof(RakNet::Time)];
	}
	else
	{
		return (unsigned char)p->data[0];
	}
}

void server_task()
{
	auto server = RakNet::RakPeerInterface::GetInstance();

	RakNet::SocketDescriptor sd;
	sd.port = SOCKET_PORT;

	auto ret = server->Startup(1024, &sd, 1);
	if (ret != RakNet::RAKNET_STARTED)
	{
		serverlog("server startup failed");
		return;
	}
	serverlog("server startup on port %d", SOCKET_PORT);
	server->SetMaximumIncomingConnections(2);

	g_bServerStarted = true;

	while (true)
	{
		for (auto packet = server->Receive(); packet; server->DeallocatePacket(packet), packet = server->Receive())
		{
			unsigned char id = getPacketIdentifier(packet);

			switch (id)
			{
			case ID_DISCONNECTION_NOTIFICATION:
				serverlog("ID_DISCONNECTION_NOTIFICATION from %s", packet->systemAddress.ToString(true));
				break;
			case ID_NEW_INCOMING_CONNECTION:
				serverlog("ID_NEW_INCOMING_CONNECTION from %s with GUID %" PRINTF_64_BIT_MODIFIER "u", packet->systemAddress.ToString(true), packet->guid);
				serverlog("Remote internal IDs:");
				for (int index=0; index < MAXIMUM_NUMBER_OF_INTERNAL_IDS; ++index)
				{
					RakNet::SystemAddress internalId = server->GetInternalID(packet->systemAddress, index);
					if (internalId!=RakNet::UNASSIGNED_SYSTEM_ADDRESS)
					{
						serverlog("%i. %s", index+1, internalId.ToString(true));
					}
				}
				break;
			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				serverlog("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
				break;
			case ID_CONNECTION_LOST:
				serverlog("ID_CONNECTION_LOST from %s\n", packet->systemAddress.ToString(true));;
				break;
			case ID_USER_PACKET:
				{
					serverlog("a user packet from client... %" PRINTF_64_BIT_MODIFIER "u", packet->guid);

					BitStream bs;
					bs.Write((MessageID)ID_TIMESTAMP);
					bs.Write(RakNet::GetTime());
					bs.Write((MessageID)ID_USER_PACKET);
					bs.Write((MessageID)1);

					//server->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
					server->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);
				}

				break;
			default:
				serverlog("unknown packet %u", id);
				break;
			}

		}

		RakSleep(1);
	}


	server->Shutdown(300);
	RakPeerInterface::DestroyInstance(server);	

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



	while (true)
	{
		for (auto packet = client->Receive(); packet; client->DeallocatePacket(packet), packet = client->Receive())
		{
			unsigned char id = getPacketIdentifier(packet);

			switch (id)
			{
			case ID_DISCONNECTION_NOTIFICATION:
				log("ID_DISCONNECTION_NOTIFICATION");
				break;
			case ID_ALREADY_CONNECTED:
				log("ID_ALREADY_CONNECTED with guid %" PRINTF_64_BIT_MODIFIER "u", packet->guid);
				break;
			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				log("ID_INCOMPATIBLE_PROTOCOL_VERSION");
				break;
			case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				log("ID_REMOTE_DISCONNECTION_NOTIFICATION"); 
				break;
			case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				log("ID_REMOTE_CONNECTION_LOST");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
				log("ID_REMOTE_NEW_INCOMING_CONNECTION");
				break;
			case ID_CONNECTION_BANNED: // Banned from this server
				log("We are banned from this server.");
				break;			
			case ID_CONNECTION_ATTEMPT_FAILED:
				log("Connection attempt failed");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				// Sorry, the server is full.  I don't do anything here but
				// A real app should tell the user
				log("ID_NO_FREE_INCOMING_CONNECTIONS");
				break;

			case ID_INVALID_PASSWORD:
				log("ID_INVALID_PASSWORD");
				break;

			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				log("ID_CONNECTION_LOST");
				break;

			case ID_CONNECTION_REQUEST_ACCEPTED:
				{
					// This tells the client they have connected
					log("ID_CONNECTION_REQUEST_ACCEPTED to %s with GUID %s\n", packet->systemAddress.ToString(true), packet->guid.ToString());
					log("My external address is %s\n", client->GetExternalID(packet->systemAddress).ToString(true));

					BitStream bs;
					bs.Write((MessageID)ID_TIMESTAMP);
					bs.Write(RakNet::GetTime());
					bs.Write((MessageID)ID_USER_PACKET);
					bs.Write((MessageID)1);

					client->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
				}

				break;
			case ID_USER_PACKET:
				log("a user packet from server... myguid: %" PRINTF_64_BIT_MODIFIER "u", client->GetMyGUID());
				break;
			default:
				log("unknown packet %u", id);
				break;
			}

		}

		RakSleep(1);
	}




	client->Shutdown(300);
	RakPeerInterface::DestroyInstance(client);	
}

int _tmain(int argc, _TCHAR* argv[])
{
	thread thread_server(server_task);

	while (!g_bServerStarted)
	{
		RakSleep(100);
	}

	thread thread_client1(client_task);
	thread thread_client2(client_task);
	thread_server.join();
	thread_client1.join();
	thread_client2.join();

	system("pause");
	return 0;
}

