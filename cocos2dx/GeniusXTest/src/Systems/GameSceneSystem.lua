
local SystemClass
SystemClass = class("GameSceneSystem", function(system_name, com_name)
    return ECS.createSystem(system_name, com_name)
end)

function SystemClass:onAttached()
    local node = self:getComByType("NodeCom")
    if node then

    end
end

return SystemClass
