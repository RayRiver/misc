network = network or {}

local m_function_map = {}

local function onNetConnected()
    print("lua onNetConnected")
    nethandler.login("wntest98", "")
end

local function onNetDisconnect()
    print("lua onNetDisconnect")
end

local function onNetReceive(id, ...)
    print("lua onNetReceive id: " .. tostring(id))
    nethandler.call(id, unpack(arg))
    --[[
    if m_function_map[id] then
        m_function_map[id](unpack(arg))
    else
        log("undefined network protocol id: " .. tostring(id))
    end
    --]]
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
