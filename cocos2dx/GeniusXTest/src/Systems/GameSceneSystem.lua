
local COM_NAME = "GameSceneCom"
local SYSTEM_NAME = "GameSceneSystem"

local SystemClass
SystemClass = class(SYSTEM_NAME, function()
    return ECS.createSystem(SystemClass, SYSTEM_NAME, COM_NAME)
end)

function SystemClass:ctor()

end

function SystemClass:onAttached()
    local node = self:getComByType("NodeCom")
    if node then

    end
end

return SystemClass
