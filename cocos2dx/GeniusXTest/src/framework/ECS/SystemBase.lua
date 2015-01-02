
local SystemBase = class("SystemBase", function(system_class, system_name, com_name)
    assert(system_class)
    assert(system_name)
    assert(com_name)
    
    local system = gx.System:create(system_name, com_name)
    
    system:registerScriptHandler(function(eventname, custom) 
        if eventname == "clone" then
            custom:setSystem(system_class.new())
        elseif eventname == "attached" then
            if system.onAttached then
                system:onAttached()
            end
        end
    end)
    
    return system
end)

-- 返回创建函数
return function(system_class, system_name, com_name)
    return SystemBase.new(system_class, system_name, com_name)
end
