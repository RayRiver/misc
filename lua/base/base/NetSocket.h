#ifndef NetSocket_h__
#define NetSocket_h__

#include <mutex>

#include "StreamBuffer.h"
#include "BitStream.h"

class NetSocket
{
public:
	NetSocket();
	virtual ~NetSocket();

	inline int fd() { return m_fd; }
	inline bool isValid() { return m_bValid; }

	inline StreamBuffer &getReadBuffer() { return m_read_buffer; }
	inline StreamBuffer &getWriteBuffer() { return m_write_buffer; }
	inline BitStream &getReadStream() { return m_read_stream; }
	inline BitStream &getWriteStream() { return m_write_stream; }

	void do_read();
	void do_write();
	void do_error(int error_code);

	void update();
	void dispatch(StreamBuffer &stream);

	void connect(const char *hostname, unsigned short port);
	void disconnect();
	void write(unsigned char *buf, size_t len);

	virtual void onConnected() = 0;
	virtual void onDisconnect() = 0;
	virtual void onRead(BitStream &stream) = 0;

private:
	bool _do_connect(const char *hostname, unsigned short port);
	void _do_connect_callback(bool connected);

private:
	int m_fd;
	bool m_bValid;

	StreamBuffer m_read_buffer;
	StreamBuffer m_write_buffer;

	BitStream m_read_stream;
	BitStream m_write_stream;
	std::mutex m_read_mutex;
	std::mutex m_write_mutex;

};

#endif // NetSocket_h__
