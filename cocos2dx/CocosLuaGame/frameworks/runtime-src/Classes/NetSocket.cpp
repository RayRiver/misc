#include "NetSocket.h"

#include "NetDef.h"
#include "NetManager.h"
#include "ThreadObj.h"
#include "ThreadManager.h"
#include "Log.h"

using namespace std;

NetSocket::NetSocket()
	: m_fd(INVALID_SOCKET)
	, m_bValid(true)
	, m_bConnectTrigger(false)
	, m_bDisconnectTrigger(false)
{

}

NetSocket::~NetSocket()
{
	if (m_fd != INVALID_SOCKET)
	{
		shutdown(m_fd, SD_BOTH);
		closesocket(m_fd);
		m_fd = INVALID_SOCKET;
	}
	m_read_buffer.clear();
	m_write_buffer.clear();
	m_read_stream.clear();
	m_write_stream.clear();
}

void NetSocket::connect(const char *hostname, unsigned short port)
{
	class ConnectThreadObj : public ThreadObj
	{
	private:
		string m_hostname;
		unsigned short m_port;
		NetSocket *m_netSocket;
	public:
		ConnectThreadObj(const char *hostname, unsigned short port, NetSocket *s)
		{
			m_hostname = hostname;
			m_port = port;
			m_netSocket = s;
		}
		void run()
		{
			bool bConnected = m_netSocket->_do_connect(m_hostname.c_str(), m_port);	
			m_netSocket->_do_connect_callback(bConnected);
		}
		void finish()
		{

		}
	};

	ThreadManager::instance()->start(new ConnectThreadObj(hostname, port, this), "async_connect_thread");
}

bool NetSocket::_do_connect(const char *hostname, unsigned short port)
{
	sockaddr_in conn;
	conn.sin_family = AF_INET;
	conn.sin_port = ntohs(port);
	//conn.sin_addr.s_addr = INADDR_ANY;
	conn.sin_addr.s_addr = inet_addr(hostname);

	memset(&(conn.sin_zero), 0, sizeof((const char*)conn.sin_zero));
	int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// block mode
	u_long arg = 0;
	::ioctlsocket(fd, FIONBIO, &arg);

	// try connect
	int result = ::connect(fd, (const sockaddr*)&conn, sizeof(sockaddr_in));
	if(result < 0)
	{
		closesocket(fd);
		return false;
	}

	m_fd = fd;
	return true;
}

void NetSocket::_do_connect_callback(bool connected)
{
	if (!connected)
	{
		do_error(3);
		m_fd = INVALID_SOCKET;
	}
	else
	{
		// none block mode
		u_long arg = 1;
		if(::ioctlsocket(m_fd, FIONBIO, &arg) != 0)
		{
			do_error(4);
			m_fd = INVALID_SOCKET;
		}
		else
		{
			m_bConnectTrigger = true;
		}
	}
}

void NetSocket::disconnect()
{
	if(m_fd != INVALID_SOCKET)
	{
		m_bDisconnectTrigger = true;
	}
}

void NetSocket::do_read()
{
	int ret = 0, bytes = 0;
	do {
		ret = ::recv(m_fd, (char *)m_read_buffer.buffer()+m_read_buffer.size(), m_read_buffer.buffer_size()-m_read_buffer.size(), 0);
		if (ret <= 0) break;
		m_read_buffer.setWritePos(m_read_buffer.size()+ret);
		bytes += ret;
	} while (true);

	if (bytes < 0)
	{
		// TODO
		this->do_error(1);
	}
	else if (bytes != 0)
	{
		m_read_mutex.lock();
		m_read_stream.writeData(m_read_buffer.buffer(), m_read_buffer.size());
		m_read_mutex.unlock();
		m_read_buffer.clear();
	}
}

void NetSocket::do_write()
{
	{
		lock_guard<mutex> lock(m_write_mutex);	
		if (m_write_stream.size() > 0)
		{
			m_write_buffer.write(m_write_stream.buffer(), m_write_stream.size());
			m_write_stream.clear();
		}
	}

	int ret = 0, bytes = 0;
	{
		do {
			ret = ::send(m_fd, (const char *)m_write_buffer.buffer(), m_write_buffer.size(), 0);
			if (ret <= 0) break;
			m_write_buffer.cut(ret);
			bytes += ret;
		} while(true);
	}

	if (bytes <= 0)
	{
		// TODO
		this->do_error(2);
	}
	else if (bytes != 0)
	{
		
	}
}

void NetSocket::do_error( int error_code )
{
	int system_error_code = 0;
#ifdef _WIN32
	system_error_code = GetLastError();
#endif
	Log("do error: %d, %d", error_code, system_error_code);
}

void NetSocket::update()
{
	if (m_bConnectTrigger)
	{
		this->onConnected();
		m_bConnectTrigger = false;
		return;
	}

	if (m_bDisconnectTrigger)
	{
		if (m_fd != INVALID_SOCKET)
		{
			shutdown(m_fd, SD_BOTH);
			closesocket(m_fd);
			m_fd = INVALID_SOCKET;
		}
		m_read_buffer.clear();
		m_write_buffer.clear();
		m_read_stream.clear();
		m_write_stream.clear();

		this->onDisconnect();
		m_bDisconnectTrigger = false;
		return;
	}

	vector<BitStream> streams;
	m_read_mutex.lock();
	while (m_read_stream.size() > 0)
	{
		unsigned char *data = m_read_stream.buffer();
		size_t bytes = m_read_stream.size();

		size_t offset = 0;
		int len = this->onReadLength(data, bytes, offset);
		if (len > 0)
		{
			// read packet stream
			BitStream packet_stream;
			packet_stream.writeData(data+offset, len);
			streams.push_back(packet_stream);
			m_read_stream.cut(offset + len);
		}
	}
	m_read_mutex.unlock();

	// dispatch
	for (auto &bs : streams)
	{
		this->onRead(bs);
	}

}

void NetSocket::write( unsigned char *buf, size_t len )
{
	lock_guard<mutex> lock(m_write_mutex);	
	m_write_stream.writeData(buf, len);
}



