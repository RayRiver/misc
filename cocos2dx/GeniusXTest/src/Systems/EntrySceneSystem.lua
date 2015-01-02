
local COM_NAME = "EntrySceneCom"
local SYSTEM_NAME = "EntrySceneSystem"

local SystemClass
SystemClass = class(SYSTEM_NAME, function()
    return ECS.createSystem(SystemClass, SYSTEM_NAME, COM_NAME)
end)

function SystemClass:ctor()

end

function SystemClass:onAttached()
    local node = self:getComByType("NodeCom")
    if node then
        local play = node:getNodeByName("play")
        play:addTouchEventListener(handlerTouchEnded(self, self.onClickButtonPlay))
    end
end

function SystemClass:onClickButtonPlay(sender)
    print("touch play!")
end

return SystemClass

