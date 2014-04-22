#include "NetEngine.h"

#include <assert.h>

#include "Sys.h"
#include "NetDef.h"
#include "NetSocket.h"

using namespace std;

NetEngine * NetEngine::instance()
{
	static NetEngine obj;
	return &obj;
}

void NetEngine::thread_task(NetEngine *engine)
{
	if (engine)
	{
		engine->run();
	}
}

NetEngine::NetEngine()
	: m_thread(nullptr)
	, m_bRunning(false)
{
#ifdef _WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf("Error at WSAStartup()\n");
	}
#endif
}

NetEngine::~NetEngine()
{
	if (m_thread && m_bRunning)
	{
		this->stop();
	}
}

void NetEngine::start()
{
	if (m_thread) 
	{
		assert(false);
		return;
	}
	m_thread = new thread(NetEngine::thread_task, this);
}

void NetEngine::stop()
{
	if (m_bRunning)
	{
		m_bRunning = false;
		m_thread->join();	
		delete m_thread;
		m_thread = nullptr;
	}
}

void NetEngine::run()
{
	m_bRunning = true;

	fd_set readable;
	fd_set writable;
	fd_set exception;

	int nfds;
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 50000;

	vector<NetSocket *> socks;
	while (m_bRunning)
	{
		size_t num = m_socks.size();
		if (num == 0)
		{
			Sys::sleep(100);
			continue;
		}

		FD_ZERO(&readable);
		FD_ZERO(&writable);
		FD_ZERO(&exception);

		int fd_max = 0;
		socks.clear();
		if (num > 0)
		{
			lock_guard<mutex> lock(m_socks_mutex);
			for (auto sock : m_socks)
			{
				int fd = sock->fd();
				if (fd == INVALID_SOCKET)
				{
					continue;
				}
				socks.push_back(sock);

				if (fd_max < fd) fd_max = fd;

				if (sock->getWriteStream().size() > 0)
				{
					FD_SET(fd, &writable);
				}
				else
				{
					FD_SET(fd, &readable);
				}
				FD_SET(fd, &exception);
			}
		}

		nfds = select(fd_max+1, &readable, &writable, &exception, &timeout);
		if (nfds > 0)
		{
			for (auto sock : socks)
			{
				if (!sock->isValid()) continue;

				int fd = sock->fd();
				if (FD_ISSET(fd, &exception))
				{
					// TODO
					sock->do_error(0);
				}
				if (sock->getWriteStream().size() > 0)
				{
					if (FD_ISSET(fd, &writable))	
					{
						sock->do_write();
					}
				}
				else
				{
					if (FD_ISSET(fd, &readable))
					{
						sock->do_read();
					}
				}
			}
		}

		Sys::sleep(2);
	}
}

void NetEngine::update()
{
	for (auto sock : m_socks)
	{
		sock->update();
	}
}

void NetEngine::add( NetSocket *sock )
{
	lock_guard<mutex> lock(m_socks_mutex);

	size_t index = 0;
	if (this->find(sock, index))
	{
		assert(false);
		return;
	}

	m_socks.push_back(sock);
}

void NetEngine::remove( NetSocket *sock )
{
	lock_guard<mutex> lock(m_socks_mutex);

	size_t index = 0;
	if (!this->find(sock, index))
	{
		assert(false);
		return;
	}

	m_socks.erase(m_socks.begin() + index);
}

bool NetEngine::find( NetSocket *sock, size_t &index )
{
	for (size_t i=0; i<m_socks.size(); ++i)
	{
		if (m_socks[i] == sock)
		{
			index = i;
			return true;
		}
	}
	return false;
}


