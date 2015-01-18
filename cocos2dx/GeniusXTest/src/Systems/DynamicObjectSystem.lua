
local SystemClass = class("DynamicObjectSystem", function(system_name, com_name)
    return ECS.createSystemBase(system_name, com_name)
end)

function SystemClass:onAttached()

end

function SystemClass:onUpdate()
    local com = self:getComByType("DynamicObjectCom")
    local speed_x, speed_y = com:getSpeed()

    if speed_x ~= 0 or speed_y ~= 0 then
        local node = self:getNode()
        local x, y = node:getPosition()
        node:setPosition(x + speed_x, y + speed_y)
        com:setDesiredPosition(x + speed_x, y + speed_y)
    end
end

return SystemClass
