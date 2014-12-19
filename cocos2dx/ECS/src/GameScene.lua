
local SceneClass = class("GameScene", function()
    return cc.Scene:create()
end)

function SceneClass:ctor()
    local ECS = gx.ECSManager:new()
    print("ECS: ", tostring(ECS))
end

return SceneClass
