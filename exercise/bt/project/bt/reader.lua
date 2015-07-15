
local BT = bt

local function load_table(t)

end

local _M = {}

function _M.loadString(str)
    local chunk = loadstring(str)
    if chunk then
        local t = chunk()
        if t then
            return load_table(t)
        end
    end
end

function _M.loadFile(file)
    local f = io.open(file, "r")
    if f then
        local s = f:read("*a")
        if s then
            return _M.loadString(s)
        end
    end
end

return _M
