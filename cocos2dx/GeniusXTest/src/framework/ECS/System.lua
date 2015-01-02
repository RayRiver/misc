
local SystemBase = class("SystemBase", function(system_name, com_name)
    assert(system_name)
    assert(com_name)

    local system = gx.System:create(system_name, com_name)
    
    system:registerScriptHandler(function(eventname, custom) 
        if eventname == "attached" then
            if system.onAttached then
                system:onAttached()
            end
        end
    end)
    
    return system
end)

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
