
local SceneBase = class("SceneBase", function(scene_name)
    assert(scene_name)

    local scene = cc.Scene:create()
    
    local sceneEntity = gx.GameSystem:getInstance():getECS():createEntity("ECS/Scenes/" .. scene_name .. ".json")
    scene:addChild(sceneEntity:getNode())

    return scene
end)

-- 返回创建函数
return function(scene_name)
    return SceneBase.new(scene_name)
end
