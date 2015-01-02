
local SCENE_NAME = "EntryScene"

local SceneClass = class(SCENE_NAME, function()
    return cc.Scene:create()
end)

function SceneClass:ctor()
    local scene = ECS.createScene(SCENE_NAME)
    self:addChild(scene:getNode())
end

return SceneClass

