# -*- coding: utf-8 -*-

from common.bytes import ByteReader, ByteWriter

bw = ByteWriter()
bw.write_int8(99)
bw.write_int16(91)
bw.write_int32(92)
bw.write_float(99.9)
bw.write_double(88.9)
bw.write_string(u"我的12345")

br = ByteReader(bw.data())
print br.read_int8()
print br.read_int16()
print br.read_int32()
print br.read_float()
print br.read_double()
print br.read_string()
