#include "BitStream.h"

#include <stdlib.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 512

BitStream::BitStream()
	: m_buffer(nullptr)
	, m_buffer_size(0)
	, m_read_pos(0)
	, m_write_pos(0)
{
	reserve(DEFAULT_BUFFER_SIZE);	
}

BitStream::BitStream( unsigned char *data, size_t len )
	: m_buffer(nullptr)
	, m_buffer_size(0)
	, m_read_pos(0)
	, m_write_pos(0)
{
	reserve(len);
	memcpy(m_buffer, data, len);
	m_write_pos = len;
}

BitStream::~BitStream()
{
	if (m_buffer)
	{
		free(m_buffer);
		m_buffer = nullptr;
	}
}

void BitStream::reserve( size_t bytes )
{
	if (bytes > m_buffer_size)
	{
		if (m_buffer)
		{
			size_t alloc_size = m_buffer_size;
			while (true)
			{
				alloc_size += alloc_size;
				if (alloc_size > bytes) break;
			}
			m_buffer = (uint8_t *)realloc(m_buffer, alloc_size);
			m_buffer_size = alloc_size;
		}
		else
		{
			if (bytes < DEFAULT_BUFFER_SIZE)
			{
				bytes = DEFAULT_BUFFER_SIZE;
			}
			else
			{
				bytes <<= 1;	
			}
			m_buffer = (uint8_t *)malloc(bytes);
			m_buffer_size = bytes;
		}
	}
}

void BitStream::cut( size_t bytes )
{
	if (bytes > m_write_pos)
	{
		return;
	}

	memmove(m_buffer, m_buffer+bytes, m_write_pos-bytes);
	m_read_pos = 0;
	m_write_pos = m_write_pos - bytes;
}

int8_t BitStream::readInt8()
{
	int8_t val;
	uint8_t *p = (uint8_t *)&val;
	p[0] = m_buffer[m_read_pos];
	m_read_pos += sizeof(int8_t);
	return val;
}

int16_t BitStream::readInt16()
{
	int16_t val;
	uint8_t *p = (uint8_t *)&val;
	p[0] = m_buffer[m_read_pos];
	p[1] = m_buffer[m_read_pos+1];
	m_read_pos += sizeof(int16_t);
	return val;
}

int32_t BitStream::readInt32()
{
	int32_t val;
	uint8_t *p = (uint8_t *)&val;
	p[0] = m_buffer[m_read_pos];
	p[1] = m_buffer[m_read_pos+1];
	p[2] = m_buffer[m_read_pos+2];
	p[3] = m_buffer[m_read_pos+3];
	m_read_pos += sizeof(int32_t);
	return val;
}

int64_t BitStream::readInt64()
{
	int64_t val;
	uint8_t *p = (uint8_t *)&val;
	p[0] = m_buffer[m_read_pos];
	p[1] = m_buffer[m_read_pos+1];
	p[2] = m_buffer[m_read_pos+2];
	p[3] = m_buffer[m_read_pos+3];
	p[4] = m_buffer[m_read_pos+4];
	p[5] = m_buffer[m_read_pos+5];
	p[6] = m_buffer[m_read_pos+6];
	p[7] = m_buffer[m_read_pos+7];
	m_read_pos += sizeof(int64_t);
	return val;
}

float BitStream::readFloat()
{
	float val;
	uint8_t *p = (uint8_t *)&val;
	p[0] = m_buffer[m_read_pos];
	p[1] = m_buffer[m_read_pos+1];
	p[2] = m_buffer[m_read_pos+2];
	p[3] = m_buffer[m_read_pos+3];
	m_read_pos += sizeof(float);
	return val;
}

double BitStream::readDouble()
{
	double val;
	uint8_t *p = (uint8_t *)&val;
	p[0] = m_buffer[m_read_pos];
	p[1] = m_buffer[m_read_pos+1];
	p[2] = m_buffer[m_read_pos+2];
	p[3] = m_buffer[m_read_pos+3];
	p[4] = m_buffer[m_read_pos+4];
	p[5] = m_buffer[m_read_pos+5];
	p[6] = m_buffer[m_read_pos+6];
	p[7] = m_buffer[m_read_pos+7];
	m_read_pos += sizeof(double);
	return val;
}

uint8_t * BitStream::readData( uint8_t *data, size_t len )
{
	if (m_write_pos - m_read_pos < len)	
	{
		len = m_write_pos - m_read_pos;
	}
	memcpy(data, m_buffer+m_read_pos, len);
	m_read_pos += len;
	return data;
}

void BitStream::writeInt8( int8_t val )
{
	reserve(m_write_pos + sizeof(int8_t));
	uint8_t *p = (uint8_t *)&val;
	m_buffer[m_write_pos+0] = p[0];
	m_write_pos += sizeof(int8_t);
}

void BitStream::writeInt16( int16_t val )
{
	reserve(m_write_pos + sizeof(int16_t));
	uint8_t *p = (uint8_t *)&val;
	m_buffer[m_write_pos+0] = p[0];
	m_buffer[m_write_pos+1] = p[1];
	m_write_pos += sizeof(int16_t);
}

void BitStream::writeInt32( int32_t val )
{
	reserve(m_write_pos + sizeof(int32_t));
	uint8_t *p = (uint8_t *)&val;
	m_buffer[m_write_pos+0] = p[0];
	m_buffer[m_write_pos+1] = p[1];
	m_buffer[m_write_pos+2] = p[2];
	m_buffer[m_write_pos+3] = p[3];
	m_write_pos += sizeof(int32_t);
}

void BitStream::writeInt64( int64_t val )
{
	reserve(m_write_pos + sizeof(int64_t));
	uint8_t *p = (uint8_t *)&val;
	m_buffer[m_write_pos+0] = p[0];
	m_buffer[m_write_pos+1] = p[1];
	m_buffer[m_write_pos+2] = p[2];
	m_buffer[m_write_pos+3] = p[3];
	m_buffer[m_write_pos+4] = p[4];
	m_buffer[m_write_pos+5] = p[5];
	m_buffer[m_write_pos+6] = p[6];
	m_buffer[m_write_pos+7] = p[7];
	m_write_pos += sizeof(int64_t);
}

void BitStream::writeFloat( float val )
{
	reserve(m_write_pos + sizeof(float));
	uint8_t *p = (uint8_t *)&val;
	m_buffer[m_write_pos+0] = p[0];
	m_buffer[m_write_pos+1] = p[1];
	m_buffer[m_write_pos+2] = p[2];
	m_buffer[m_write_pos+3] = p[3];
	m_write_pos += sizeof(float);
}

void BitStream::writeDouble( double val )
{
	reserve(m_write_pos + sizeof(double));
	uint8_t *p = (uint8_t *)&val;
	m_buffer[m_write_pos+0] = p[0];
	m_buffer[m_write_pos+1] = p[1];
	m_buffer[m_write_pos+2] = p[2];
	m_buffer[m_write_pos+3] = p[3];
	m_buffer[m_write_pos+4] = p[4];
	m_buffer[m_write_pos+5] = p[5];
	m_buffer[m_write_pos+6] = p[6];
	m_buffer[m_write_pos+7] = p[7];
	m_write_pos += sizeof(double);
}

void BitStream::writeData( uint8_t *data, size_t len )
{
	reserve(m_write_pos + len);
	memcpy(m_buffer+m_write_pos, data, len);
	m_write_pos += len;
}
