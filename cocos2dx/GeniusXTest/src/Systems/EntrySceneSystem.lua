
local SystemClass = class("EntrySceneSystem", function(system_name, com_name)
    return ECS.createSystem(system_name, com_name)
end)

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

