
local SystemBase = class("SystemBase", function(system_name, com_name)
    assert(system_name)
    assert(com_name)

    local system = gx.System:create(system_name, com_name)
    
    system.m_listeners = {}
    
    system:registerScriptHandler(function(eventname, custom) 
        if eventname == "attached" then
            if system.onAttached then
                system:onAttached()
            end
        elseif eventname == "deattached" then
            for event_name, listener in pairs(system.m_listeners) do
                cc.Director:getInstance():getEventDispatcher():removeEventListener(listener)
            end
            system.m_listeners = {}
        
            if system.onDetached then
                system:onDetached()
            end
        end
    end)
    
    return system
end)

function SystemBase:registerEvent(event_name, callback)
    self:unregisterEvent(event_name)

    local dispathcer = cc.Director:getInstance():getEventDispatcher()
    local listener = cc.EventListenerCustom:create(event_name, callback)
    cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(listener, 1)
    
    if listener then
        self.m_listeners[event_name] = listener
    end
end

function SystemBase:unregisterEvent(event_name)
    local listener = self.m_listeners[event_name]
    if listener then
        cc.Director:getInstance():getEventDispatcher():removeEventListener(listener)
    end
    self.m_listeners[event_name] = nil
end

function SystemBase:dispatchEvent(event_name, args)
    local event = cc.EventCustom:new(event_name)
    event.args = args
    cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
end

local SystemFactory = class("SystemFactory", function(system_name, com_name)
    assert(system_name)
    assert(com_name)

    local system = gx.System:create(system_name, com_name)
    
    -- 是否实现了system类
    local system_class
    local file_exists = cc.FileUtils:getInstance():isFileExist("src/Systems/" .. system_name .. ".lua")
    if file_exists then
        system_class = require("Systems." .. system_name)
    else
        system_class = SystemBase
    end

    system:registerScriptHandler(function(eventname, custom) 
        if eventname == "clone" then
            custom:setSystem(system_class.new(system_name, com_name))
        end
    end)

    return system
end)

local _M = {}

function _M.createSystem(system_name, com_name)
    return SystemBase.new(system_name, com_name)
end
    
function _M.systemFactory(system_name, com_name)
    return SystemFactory.new(system_name, com_name)
end

return _M
