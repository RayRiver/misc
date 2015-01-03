
local ObjectBase = class("ObjectBase", function(object_name)
    assert(object_name)

    local entity = gx.GameSystem:getInstance():getECS():createEntity("ECS/Objects/" .. object_name .. ".json")

    return entity
end)

local ObjectFactory = class("ObjectFactory", function(object_name)
    assert(object_name)

    -- 检查是否实现了object类
    local object_class
    local file_exists = cc.FileUtils:getInstance():isFileExist("src/Objects/" .. object_name .. ".lua")
    if file_exists then
        object_class = require("Objects." .. object_name)
    else
        object_class = ObjectBase
    end

    local object = object_class.new(object_name)
    return object
end)

local _M = {}

function _M.createObject(object_name)
    return ObjectBase.new(object_name)
end

function _M.objectFactory(object_name)
    return ObjectFactory.new(object_name)
end

return _M
