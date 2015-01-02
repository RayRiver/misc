
local SceneClass = class("EntryScene", function()
    return cc.Scene:create()
end)

function SceneClass:ctor()
    self.entity = ECS.gameSystem:getECS():createEntity("EntryScene.json")
    self:addChild(self.entity:getNode())
end

return SceneClass

