#ifndef StreamBuffer_h__
#define StreamBuffer_h__

class StreamBuffer
{
public:
	StreamBuffer();
	virtual ~StreamBuffer();

	inline unsigned char *buffer() { return m_buffer; }
	inline size_t size() { return m_write_pos; };
	inline size_t buffer_size() { return m_buffer_size; }

	void clear();

	inline void setReadPos(size_t pos) { m_read_pos = pos; }
	inline void setWritePos(size_t pos) { m_write_pos = pos; }

	void reserve(size_t bytes);
	void read(unsigned char *buf, size_t len);
	void write(unsigned char *data, size_t len);
	void cut(size_t bytes);

private:
	enum { DEFAULT_BUFFER_SIZE = 1024 };
	unsigned char *m_buffer;	
	size_t m_buffer_size;
	size_t m_read_pos, m_write_pos;
};

#endif // StreamBuffer_h__
