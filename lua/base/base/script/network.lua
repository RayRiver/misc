network = network or {}

local m_function_map = {}

local function onNetConnected()
    print("lua onNetConnected")
    logic.login("wntest98", "")
end

local function onNetDisconnect()
    print("lua onNetDisconnect")
end

local function onNetReceive(id, ...)
    print("lua onNetReceive")

    if m_function_map[id] then
        m_function_map[id]()
    else
        log("undefined network protocol id: " .. tostring(id))
    end
end

m_function_map[0xA008] = function(...)
    log("onNetReceiveLoginResp")
end

m_function_map[0xA006] = function(...)
    log("onNetReceiveExistRole")
end

network.init = function()
    -- resigter network callback
    event.register("onNetConnected", onNetConnected)
    event.register("onNetDisconnect", onNetDisconnect)
    event.register("onNetReceive", onNetReceive)

    net.start()

    log("network init ok")
end

return network
