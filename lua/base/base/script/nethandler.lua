nethandler = nethandler or {}

nethandler.login = function(username, password)
    local p = Packet.new()
    p:addId(0xA007)
    p:addInt32(19245)
    p:addString(username)
    p:addString("dc483e80a7a0bd9ef71d8cf973673924")
    p:addInt32(0)
    p:addString("")
    p:addString("")
    p:addString("")
    p:addInt32(1)
    p:addString("")
    p:addString(username)
    p:addString("")
    p:addInt32(0)
    p:addString("")
    p:addString("")
    p:addString("")
    p:send()
end

nethandler.initRoleInfo = function()

end

local function onExistRole(...)
    log("onExistRole")

    local result = arg[1]
    if result ~= 1 then
        log("result: " .. tostring(result))    
    end
end

local m_handler_map = {}
local function registerHandler(id, fn)
    m_handler_map[id] = fn
end

nethandler.init = function()
    registerHandler(0xA006, onExistRole)
end

nethandler.call = function(id, ...)
    if m_handler_map[id] then
        m_handler_map[id](unpack(arg)) 
    else
        log("nethandler.call cannot find handler, id=" .. tostring(id))
    end
end

return nethandler
