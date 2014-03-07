#include <iostream>
#include <sstream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>

#include "Python.h"


using namespace std;


struct data_stream_t
{
	size_t size;
	size_t write_ptr;
	size_t read_ptr;
	char *data;
};

inline data_stream_t *alloc_size(data_stream_t *stream, size_t size)
{
	if (stream)
	{
		while (stream->size - stream->write_ptr < size)
		{
			stream->data = (char *)realloc(stream->data, stream->size * 2);
			stream->size += stream->size;
		}
	}
	else
	{
		stream = (data_stream_t *)malloc(sizeof(data_stream_t));
		stream->size = size;
		stream->write_ptr = 0;
		stream->read_ptr = 0;
		stream->data = (char *)malloc(stream->size);
	}

	return stream;
}

/*
read methods
*/

inline void * create_read_stream(PyObject *obj)
{
	Py_ssize_t size = PyString_Size(obj);
	char *s = PyString_AsString(obj);
	
	data_stream_t *stream = alloc_size(0, size);
	memcpy(stream->data, s, size);
	return (void *)stream;
}

inline void delete_read_stream(void *ss)
{
	data_stream_t *stream = (data_stream_t *)ss;
	if (stream)
	{
		if (stream->data)
		{
			free(stream->data);
		}
		free(stream);
	}
}

inline char read_int8(void * ss)
{
	const size_t size = 1;
	data_stream_t *stream = (data_stream_t *)ss;
	char value = stream->data[stream->read_ptr];
	stream->read_ptr += size;
	return value;
}

inline unsigned char read_uint8(void * ss)
{
	return (unsigned char)read_int8(ss);
}

inline short read_int16(void * ss)
{
	const size_t size = 2;
	data_stream_t *stream = (data_stream_t *)ss;
	unsigned char *bytes = (unsigned char *)stream->data + stream->read_ptr;
	short value = (bytes[0] | (bytes[1] << 8));
	stream->read_ptr += size;
	return value;
}

inline unsigned short read_uint16(void * ss)
{
	return (unsigned short)read_int16(ss);
}

inline int read_int32(void * ss)
{
	const size_t size = 4;
	data_stream_t *stream = (data_stream_t *)ss;
	unsigned char *bytes = (unsigned char *)stream->data + stream->read_ptr;
	short value = (bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24));
	stream->read_ptr += size;
	return value;
}

inline unsigned int read_uint32(void * ss)
{
	return (unsigned int)read_int32(ss);
}

inline int64_t read_int64(void * ss)
{
	const size_t size = 8;
	data_stream_t *stream = (data_stream_t *)ss;
	unsigned char *bytes = (unsigned char *)stream->data + stream->read_ptr;
	int64_t value = 0;
	value |= (int64_t)bytes[0];
	value |= (int64_t)bytes[1] << 8;
	value |= (int64_t)bytes[2] << 16;
	value |= (int64_t)bytes[3] << 24;
	value |= (int64_t)bytes[4] << 32;
	value |= (int64_t)bytes[5] << 40;
	value |= (int64_t)bytes[6] << 48;
	value |= (int64_t)bytes[7] << 56;
	stream->read_ptr += size;
	return value;
}

inline uint64_t read_uint64(void * ss)
{
	return (uint64_t)read_int64(ss);
}

inline double read_float(void * ss)
{
	const size_t size = 4;
	data_stream_t *stream = (data_stream_t *)ss;
	unsigned char *bytes = (unsigned char *)stream->data + stream->read_ptr;
	stream->read_ptr += size;
	return _PyFloat_Unpack4((const unsigned char*)bytes, true);
}

inline double read_double(void * ss)
{
	const size_t size = 8;
	data_stream_t *stream = (data_stream_t *)ss;
	unsigned char *bytes = (unsigned char *)stream->data + stream->read_ptr;
	stream->read_ptr += size;
	return _PyFloat_Unpack8((const unsigned char*)bytes, true);
}

inline PyObject * read_bytes(void * ss, size_t size)
{
	data_stream_t *stream = (data_stream_t*)ss;
	stream->read_ptr += size;
	return PyString_FromStringAndSize(stream->data + stream->read_ptr - size, size);
}

/*
write methods
*/

inline void * create_write_stream()
{
	data_stream_t *stream = alloc_size(0, 128);
	return (void *)stream;
}

inline void delete_write_stream(void * ss)
{
	data_stream_t *stream = (data_stream_t *)ss;
	if (stream)
	{
		if (stream->data)
		{
			free(stream->data);
		}
		free(stream);
	}
}

inline void write_int8(void * ss, char value)
{
	const size_t nAlloc = 1;
	data_stream_t *stream = (data_stream_t *)ss;
	stream = alloc_size(stream, nAlloc);
	if (stream)
	{
		stream->data[stream->write_ptr] = (char)value;
		stream->write_ptr += 1;
	}
}

inline void write_uint8(void * ss, unsigned char value)
{
	const size_t nAlloc = 1;
	data_stream_t *stream = (data_stream_t *)ss;
	stream = alloc_size(stream, nAlloc);
	if (stream)
	{
		stream->data[stream->write_ptr] = (char)value;
		stream->write_ptr += 1;
	}
}

inline void write_int16(void * ss, short value)
{
	const size_t nAlloc = 2;
	data_stream_t *stream = (data_stream_t *)ss;
	stream = alloc_size(stream, nAlloc);
	if (stream)
	{
		stream->data[stream->write_ptr] = (char)value;
		stream->data[stream->write_ptr+1] = (char)(value >> 8);
		stream->write_ptr += nAlloc;
	}
}

inline void write_uint16(void * ss, unsigned short value)
{
	write_int16(ss, (short)value);
}

inline void write_int32(void * ss, int value)
{
	const size_t nAlloc = 4;
	data_stream_t *stream = (data_stream_t *)ss;
	stream = alloc_size(stream, nAlloc);
	if (stream)
	{
		stream->data[stream->write_ptr] = (char)value;
		stream->data[stream->write_ptr+1] = (char)(value >> 8);
		stream->data[stream->write_ptr+2] = (char)(value >> 16);
		stream->data[stream->write_ptr+3] = (char)(value >> 24);
		stream->write_ptr += nAlloc;
	}
}

inline void write_uint32(void * ss, unsigned int value)
{
	write_int32(ss, (int)value);
}

inline void write_int64(void * ss, int64_t value)
{
	const size_t nAlloc = 8;
	data_stream_t *stream = (data_stream_t *)ss;
	stream = alloc_size(stream, nAlloc);
	if (stream)
	{
		stream->data[stream->write_ptr] = (char)value;
		stream->data[stream->write_ptr+1] = (char)(value >> 8);
		stream->data[stream->write_ptr+2] = (char)(value >> 16);
		stream->data[stream->write_ptr+3] = (char)(value >> 24);
		stream->data[stream->write_ptr+4] = (char)(value >> 32);
		stream->data[stream->write_ptr+5] = (char)(value >> 40);
		stream->data[stream->write_ptr+6] = (char)(value >> 48);
		stream->data[stream->write_ptr+7] = (char)(value >> 56);
		stream->write_ptr += nAlloc;
	}
}

inline void write_uint64(void * ss, uint64_t value)
{
	write_int64(ss, (int64_t)value);
}

inline void write_float(void * ss, double value)
{
	const size_t nAlloc = 4;
	data_stream_t *stream = (data_stream_t *)ss;
	stream = alloc_size(stream, nAlloc);

	char out[nAlloc];
	_PyFloat_Pack4(value, (unsigned char *)&out, true);

	if (stream)
	{
		memcpy(stream->data+stream->write_ptr, out, nAlloc);
		stream->write_ptr += nAlloc;
	}
}

inline void write_double(void * ss, double value)
{
	const size_t nAlloc = 8;
	data_stream_t *stream = (data_stream_t *)ss;
	stream = alloc_size(stream, nAlloc);

	char out[nAlloc];
	_PyFloat_Pack8(value, (unsigned char *)&out, true);

	if (stream)
	{
		memcpy(stream->data+stream->write_ptr, out, nAlloc);
		stream->write_ptr += nAlloc;
	}
}

inline void write_bytes(void * ss, PyObject *obj)
{
	char *data = PyString_AsString(obj);
	Py_ssize_t size = PyString_Size(obj);

	const size_t nAlloc = size;
	data_stream_t *stream = (data_stream_t *)ss;
	stream = alloc_size(stream, nAlloc);
	memcpy(stream->data+stream->write_ptr, data, nAlloc);
	stream->write_ptr += nAlloc;
}

inline size_t get_write_pos(void * ss)
{
	data_stream_t *stream = (data_stream_t *)ss;
	return stream->write_ptr;
}

inline PyObject * get_stream_data(void * ss)
{
	data_stream_t *stream = (data_stream_t*)ss;
	return PyString_FromStringAndSize(stream->data, stream->write_ptr);
}
