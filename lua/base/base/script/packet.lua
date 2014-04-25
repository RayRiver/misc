require("classlib")

local VAR_UNDEFINED = 0
local VAR_STRING = 1
--local VAR_RESERVED_DONT_USE_1,
local VAR_INT = 3
local VAR_FLOAT = 4
local VAR_NUMBER = 5
local VAR_BOOL = 6
local VAR_INT64 = 7

-- not defined
local VAR_BYTE = 8
local VAR_SHORT = 9

class.Packet()
function Packet:__init(...)
    self.args = VarList()

    -- add header
    self.args:addInt32(0)
    self.args:addInt32(0x100)
    self.args:addInt32(0)
    self.args:addInt32(2)
    self.args:addInt32(0)
    self.args:addInt32(0)
    self.args:addInt32(5)
    self.args:addInt32(6)
    self.args:addInt32(7)
    self.args:addInt32(8)
end

function Packet:addId(id)
    self.args:addInt32(id)
end

function Packet:addInt8(val)
    self.args:addInt8(VAR_BYTE)
    self.args:addInt8(val)
end

function Packet:addInt16(val)
    self.args:addInt8(VAR_SHORT)
    self.args:addInt16(val)
end

function Packet:addInt32(val)
    self.args:addInt8(VAR_INT)
    self.args:addInt32(val)
end

function Packet:addInt64(val)
    self.args:addInt8(VAR_INT64)
    self.args:addInt64(val)
end

function Packet:addFloat(val)
    self.args:addInt8(VAR_FLOAT)
    self.args:addFloat(val)
end

function Packet:addDouble(val)
    self.args:addInt8(VAR_DOUBLE)
    self.args:addDouble(val)
end

function Packet:addString(val)
    self.args:addInt8(VAR_STRING)
    self.args:addString(val)
end

function Packet:send()
    net.send(self.args)
end

