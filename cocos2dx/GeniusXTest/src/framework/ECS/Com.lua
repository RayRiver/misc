
local ComBase = class("ComBase", function(com_name) 
    assert(com_name)

    local com = gx.Com:create(com_name)

    return com
end)

local ComFactory = class("ComFactory", function(com_name)
    assert(com_name)

    local com = gx.Com:create(com_name)
    
    -- 是否实现了com类
    local com_class
    local file_exists = cc.FileUtils:getInstance():isFileExist("src/Coms/" .. com_name .. ".lua")
    if file_exists then
        com_class = require("Coms." .. com_name)
    else
        com_class = ComBase
    end

    -- 创建新的com
    com:registerScriptHandler(function(eventname, custom) 
        if eventname == "clone" then
            custom:setCom(com_class.new(com_name))
        end
    end)

    return com
end)

local _M = {}

function _M.createCom(com_name)
    return ComBase.new(com_name)
end

function _M.comFactory(com_name)
    return ComFactory.new(com_name)
end

return _M
