
local Cache = {}

local ObjectBase = class("ObjectBase", function(object_name)
    assert(object_name)

    local entity = gx.GameSystem:getInstance():getECS():createEntity("ECS/Objects/" .. object_name .. ".json")

    return entity
end)

local ObjectFactory = class("ObjectFactory", function(object_name)
    assert(object_name)
    
    local object_class
    
    local cached_class = Cache[object_name]
    if cached_class then
        object_class = cached_class
    else
        -- 检查是否实现了object类
        local file_exists = cc.FileUtils:getInstance():isFileExist("src/Objects/" .. object_name .. ".lua")
        if file_exists then
            object_class = require("Objects/" .. object_name)
        else
            object_class = ObjectBase
        end
        
        Cache[object_name] = object_class
    end

    local object = object_class.new(object_name)
    return object
end)

local _M = {}

function _M.createObject(object_name)
    return ObjectFactory.new(object_name)
end

function _M.destroyObject(object)
    gx.GameSystem:getInstance():getECS():removeEntity(object)
end

return _M
