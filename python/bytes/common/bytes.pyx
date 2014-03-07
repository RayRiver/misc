# -*- coding: utf-8 -*-

cimport cython
from libc.limits cimport UINT_MAX

ctypedef signed long long int64_t
ctypedef unsigned long long uint64_t

cdef extern from "bytes_c.cpp":
    struct data_stream_t
    data_stream_t *alloc_size(data_stream_t *stream, size_t size)

    # read
    void * create_read_stream(bytes data)
    void delete_read_stream(void * ss)
    char read_int8(void * ss)
    unsigned char read_uint8(void * ss)
    short read_int16(void * ss)
    unsigned short read_uint16(void * ss)
    int read_int32(void * ss)
    unsigned int read_uint32(void * ss)
    int64_t read_int64(void * ss)
    uint64_t read_uint64(void * ss)
    double read_float(void * ss)
    double read_double(void * ss)
    bytes read_bytes(void * ss, size_t size)

    # write
    void * create_write_stream()
    void delete_write_stream(void * ss)
    void write_int8(void * ss, char value)
    void write_uint8(void * ss, unsigned char value)
    void write_int16(void * ss, short value)
    void write_uint16(void * ss, unsigned short value)
    void write_int32(void * ss, int value)
    void write_uint32(void * ss, unsigned int value)
    void write_int64(void * ss, int64_t)
    void write_uint64(void * ss, uint64_t)
    void write_float(void * ss, double value)
    void write_double(void * ss, double value)
    void write_bytes(void * ss, bytes data)
    size_t get_write_pos(void * ss)
    bytes get_stream_data(void * ss)

@cython.final
cdef class ByteReader:
    cdef:
        void *stream

    def __init__(self, data):
        self.stream = create_read_stream(data)

    def __dealloc__(self):
        delete_read_stream(self.stream)

    cpdef char read_int8(self):
        return read_int8(self.stream)

    cpdef unsigned char read_uint8(self):
        return read_uint8(self.stream)

    cpdef short read_int16(self):
        return read_int16(self.stream)

    cpdef unsigned short read_uint16(self):
        return read_uint16(self.stream)

    cpdef int read_int32(self):
        return read_int32(self.stream)

    cpdef unsigned int read_uint32(self):
        return read_uint32(self.stream)

    cpdef int64_t read_int64(self):
        return read_int64(self.stream)

    cpdef uint64_t read_uint64(self):
        return read_uint64(self.stream)

    cpdef double read_float(self):
        return read_float(self.stream)

    cpdef double read_double(self):
        return read_double(self.stream)

    cpdef bytes read_bytes(self):
        size = read_uint16(self.stream)
        return read_bytes(self.stream, size)

    cpdef unicode read_string(self):
        data = self.read_bytes()
        return bytes.decode(data, encoding="utf-8")

@cython.final
cdef class ByteWriter:
    cdef:
        void *stream

    def __init__(self):
        self.stream = create_write_stream()

    def __dealloc__(self):
        delete_write_stream(self.stream)

    cpdef write_int8(self, value):
        write_int8(self.stream, value)

    cpdef write_uint8(self, value):
        write_uint8(self.stream, value)

    cpdef write_int16(self, value):
        write_int16(self.stream, value)

    cpdef write_uint16(self, value):
        write_uint16(self.stream, value)

    cpdef write_int32(self, value):
        write_int32(self.stream, value)

    cpdef write_uint32(self, value):
        write_uint32(self.stream, value)

    cpdef write_int64(self, value):
        write_int64(self.stream, value)

    cpdef write_uint64(self, value):
        write_uint64(self.stream, value)

    cpdef write_float(self, value):
        write_float(self.stream, value)

    cpdef write_double(self, value):
        write_double(self.stream, value)

    cpdef write_bytes(self, data):
        write_uint16(self.stream, len(data))
        write_bytes(self.stream, data)

    cpdef write_string(self, s):
        data = unicode.encode(s, encoding="utf-8")
        self.write_bytes(data)

    cpdef bytes data(self):
        return get_stream_data(self.stream)









