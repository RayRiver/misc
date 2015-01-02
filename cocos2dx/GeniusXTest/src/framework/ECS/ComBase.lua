
local ComBase = class("ComBase", function(com_class, com_name) 
    assert(com_class)
    assert(com_name)
    
    local com = gx.Com:create(com_name)
    
    com:registerScriptHandler(function(eventname, custom) 
        if eventname == "clone" then
            custom:setCom(com_class.new())
        end
    end)
    
    return com
end)

-- 返回创建函数
return function(com_class, com_name)
    return ComBase.new(com_class, com_name)
end
