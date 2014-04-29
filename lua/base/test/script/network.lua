network = network or {}

local m_function_map = {}

local function onNetConnected()
    log("lua onNetConnected")
    nethandler.login("wntest98", "")
end

local function onNetDisconnect()
    log("lua onNetDisconnect")
end

local function onNetReceive(id, ...)
    log("lua onNetReceive id: 0x" .. string.format("%4X", id))
    nethandler.call(id, unpack(arg))
end

network.init = function()
    -- resigter callbacks
    event.register("onNetConnected", onNetConnected)
    event.register("onNetDisconnect", onNetDisconnect)
    event.register("onNetReceive", onNetReceive)

    net.start()
    log("network init ok")
end

network.send = function(packet)
    net.send(packet)
end

return network
