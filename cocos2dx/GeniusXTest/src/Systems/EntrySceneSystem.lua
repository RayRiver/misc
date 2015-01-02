
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
        
        local exit = node:getNodeByName("exit")
        exit:addTouchEventListener(handlerTouchEnded(self, self.onClickButtonExit))
    end
end

function SystemClass:onClickButtonPlay(sender)
    app:enterScene("GameScene")
end

function SystemClass:onClickButtonExit(sender)
    cc.Director:getInstance():endToLua()
end

return SystemClass

