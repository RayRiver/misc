
local SystemClass = class("MoveToTargetSystem", function(system_name, com_name)
    return ECS.createSystem(system_name, com_name)
end)

function SystemClass:onUpdate()
    local com = self:getComByType("AI/MoveToTargetCom")
    if com and com.target then
        local entity = com:getEntity()
        local target = com.target

        local pos_x, pos_y = entity:getNode():getPosition()
        local target_x, target_y = target:getNode():getPosition()
        
        local speed = 5
        
        local dx = target_x - pos_x
        local dy = target_y - pos_y
        local n = math.sqrt(dx*dx + dy+dy)
        
        if n < 10 then
            self:dispatchEvent("onDestroyMonster", {monster=entity})
        else    
            dx = dx / n * speed
            dy = dy / n * speed
            entity:getNode():setPosition(pos_x + dx, pos_y + dy)
        end
    end
end

return SystemClass
