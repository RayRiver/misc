
local SceneClass = class("GameScene", function(scene_name)
    return ECS.createScene(scene_name)
end)

function SceneClass:ctor()

end

return SceneClass
