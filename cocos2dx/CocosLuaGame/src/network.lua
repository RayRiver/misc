local net = network

network.MSG_LOGIN_RESP = 0xA006

local m_tMessages = {}
local m_tFunctionMap = {}

local function onConnected()
    cclog("onConnected.......")
    net.login("wntest99", "a123456")
end

local function onDisconnect()
    cclog("onDisconnect.......")
end

local function onReceive(args)
    table.insert(m_tMessages, args)
end

network.start()

network.registerHandler(function(event, args)
    local event_name = args[1]

    if event_name == "onConnected" then
        onConnected()
    elseif event_name == "onDisconnect" then
        onDisconnect()
    elseif event_name == "onReceive" then
        table.remove(args, 1)
        onReceive(args)
    else
        cclog("unknown event name %s", event_name)
    end
end)

-- 每帧处理网络消息
cc.Director:getInstance():getScheduler():scheduleScriptFunc(function()
    if #m_tMessages == 0 then return end

    local args = m_tMessages[1]
    table.remove(m_tMessages, 1)

    cclog("onReceive......." .. tostring(#args))
    for i = 1, #args do
        cclog(tostring(i) .. ": " .. tostring(args[i]))
    end
    
    -- find message function
    local fn = m_tFunctionMap[args[1]]
    if not fn then
        cclog("cannot find message function 0x%02X", args[1])
        return
    end
    
    table.remove(args, 1)
    fn(args)
end, 0, false)

function net.register(id, fn)
    m_tFunctionMap[id] = fn
end

-- 网络消息处理



function net.login(username, password)
    local args = LuaValueList()
    args:pushInt(19245)
    args:pushString(username)
    args:pushString("dc483e80a7a0bd9ef71d8cf973673924")
    args:pushInt(0)
    args:pushString("")
    args:pushString("")
    args:pushString("")
    args:pushInt(1)
    args:pushString("")
    args:pushString(username)
    args:pushString("")
    args:pushInt(0)
    args:pushString("")
    args:pushString("")
    args:pushString("")
    network.send(0xA007, args)
end

return net
