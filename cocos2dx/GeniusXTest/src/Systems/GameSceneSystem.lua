
local SystemClass
SystemClass = class("GameSceneSystem", function(system_name, com_name)
    return ECS.createSystem(system_name, com_name)
end)

function SystemClass:onAttached()
    local node = self:getComByType("NodeCom")
    if node then

    end
    
    self:registerEvent("onTest", handler(self, self.onTest))
    

    self:getNode():runAction(cc.Sequence:create(
        cc.DelayTime:create(3),
        cc.CallFunc:create(function() 
            self:dispatchEvent("onTest", {test=99})
        end)
    ))

end

function SystemClass:onTest(event)
    print("onTest", tostring(event), tostring(event.args.test))
end

return SystemClass
