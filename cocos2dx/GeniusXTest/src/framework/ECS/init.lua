
local _M = {}

_M.gameSystem = gx.GameSystem:getInstance()

local module = import(".Com")
for k, v in pairs(module) do
    _M[k] = v
end

local module = import(".System")
for k, v in pairs(module) do
    _M[k] = v
end

local module = import(".Scene")
for k, v in pairs(module) do
    _M[k] = v
end

local module = import(".Object")
for k, v in pairs(module) do
    _M[k] = v
end

return _M
