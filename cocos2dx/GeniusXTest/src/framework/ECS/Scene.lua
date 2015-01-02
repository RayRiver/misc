
local SceneBase = class("SceneBase", function(scene_name)
    assert(scene_name)

    local scene = cc.Scene:create()

    local sceneEntity = gx.GameSystem:getInstance():getECS():createEntity("ECS/Scenes/" .. scene_name .. ".json")
    scene:addChild(sceneEntity:getNode())

    return scene
end)

local SceneFactory = class("SceneFactory", function(scene_name)
    assert(scene_name)

    -- 检查是否实现了scene类
    local scene_class
    local file_exists = cc.FileUtils:getInstance():isFileExist("src/Scenes/" .. scene_name .. ".lua")
    if file_exists then
        scene_class = require("Scenes." .. scene_name)
    else
        scene_class = SceneBase
    end

    local scene = scene_class.new(scene_name)
    return scene
end)

local _M = {}

function _M.createScene(scene_name)
    return SceneBase.new(scene_name)
end

function _M.sceneFactory(scene_name)
    return SceneFactory.new(scene_name)
end

return _M
