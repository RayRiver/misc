require("classlib")

local VAR_UNDEFINED = 0
local VAR_BOOL = 1
local VAR_INT = 2
local VAR_FLOAT = 3
local VAR_STRING = 4

local VAR_INT64 = 9
local VAR_NUMBER = 10

local VAR_BYTE = 11
local VAR_SHORT = 12

class.Packet()
function Packet:__init(...)
    self.args = VarList()
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
    self.args:addInt16(string.len(val))
    self.args:addString(val)
end

function Packet:send()
    net.send(self.args)
end

