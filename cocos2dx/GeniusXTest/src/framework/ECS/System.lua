
local Cache = {}

local SystemBase = class("SystemBase", function(system_name, com_name)
    assert(system_name)
    assert(com_name)

    local system = gx.System:create(system_name, com_name)

    system.m_listeners = {}
    system.m_named_schedulers = {}
    system.m_unnamed_schedulers = {}

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

            for scheduler_name, listener in pairs(system.m_named_schedulers) do
                cc.Director:getInstance():getScheduler():unscheduleScriptEntry(listener)
            end
            system.m_named_schedulers = {}

            for _, listener in ipairs(system.m_unnamed_schedulers) do
                cc.Director:getInstance():getScheduler():unscheduleScriptEntry(listener)
            end
            system.m_unnamed_schedulers = {}

            if system.onDetached then
                system:onDetached()
            end
        elseif eventname == "update" then
            if system.onUpdate then
                system:onUpdate()
            end
        else
            local event = "onEvent_" .. eventname
            if system[event] then
                system[event](eventname)
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
        self.m_listeners[event_name] = nil
    end
end

function SystemBase:dispatchEvent(event_name, args)
    local event = cc.EventCustom:new(event_name)
    event.args = args
    cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
end

function SystemBase:registerScheduler(callback, interval, scheduler_name)
    local listener = cc.Director:getInstance():getScheduler():scheduleScriptFunc(callback, interval, false)

    if listener then
        if scheduler_name then
            self:unregisterScheduler(scheduler_name)
            self.m_named_schedulers[scheduler_name] = listener
        else
            table.insert(self.m_unnamed_schedulers, listener)
        end
    end
end

function SystemBase:unregisterScheduler(scheduler_name)
    local listener = self.m_named_schedulers[scheduler_name]
    if listener then
        cc.Director:getInstance():getScheduler():unscheduleScriptEntry(listener)
        self.m_named_schedulers[scheduler_name] = nil
    end
end

local SystemFactory = class("SystemFactory", function(system_name, com_name)
    assert(system_name)
    assert(com_name)

    local system = gx.System:create(system_name, com_name)

    local system_class

    local cached_class = Cache[system_name]
    if cached_class then
        system_class = cached_class
    else
        -- 是否实现了system类
        local file_exists = cc.FileUtils:getInstance():isFileExist("src/Systems/" .. system_name .. ".lua")
        if file_exists then
            system_class = require("Systems/" .. system_name)
            print("create system from class ", tostring(system_name))
        else
            system_class = SystemBase
            print("create system from base ", tostring(system_name))
        end

        Cache[system_name] = system_class
    end

    system:registerScriptHandler(function(eventname, custom)
        if eventname == "clone" then
            local system = system_class.new(system_name, com_name)
            custom:setSystem(system)
        end
    end)

    return system
end)

local _M = {}

function _M.createSystemBase(system_name, com_name)
    return SystemBase.new(system_name, com_name)
end

function _M.systemFactory(system_name, com_name)
    return SystemFactory.new(system_name, com_name)
end

return _M
