#include "StreamBuffer.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

StreamBuffer::StreamBuffer()
	: m_buffer(nullptr)
	, m_buffer_size(0)
	, m_read_pos(0)
	, m_write_pos(0)
{
	this->reserve(DEFAULT_BUFFER_SIZE);
}

StreamBuffer::~StreamBuffer()
{
	if (m_buffer)
	{
		free(m_buffer);
		m_buffer = nullptr;
	}
}

void StreamBuffer::clear()
{
	m_write_pos = 0;
}

void StreamBuffer::reserve( size_t bytes )
{
	if (bytes > m_buffer_size)
	{
		bytes <<= 1;
		if (m_buffer)
		{
			m_buffer = (unsigned char *)realloc(m_buffer, bytes);
		}
		else
		{
			m_buffer = (unsigned char *)malloc(bytes);
		}
		m_buffer_size = bytes;
	}
}

void StreamBuffer::read( unsigned char *buf, size_t len )
{
	if (m_read_pos + len > m_write_pos)
	{
		len = m_write_pos - m_read_pos;
	}

	memcpy(buf, &m_buffer[m_read_pos], len);
	m_read_pos += len;
}

void StreamBuffer::write( unsigned char *data, size_t len )
{
	if (!data)
	{
		assert(false);
		return;
	}

	if (m_write_pos + len > m_buffer_size)
	{
		this->reserve(m_buffer_size * 2);
	}

	memcpy(&m_buffer[m_write_pos], data, len);
	m_write_pos += len;
}

void StreamBuffer::cut( size_t bytes )
{
	if (bytes > m_write_pos)
	{
		assert(false);
		return;
	}
	
	memmove(m_buffer, m_buffer+bytes, m_write_pos-bytes);
	m_read_pos = 0;
	m_write_pos = m_write_pos - bytes;
}

