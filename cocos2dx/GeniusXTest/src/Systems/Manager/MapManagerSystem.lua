
local SystemClass = class("MapManagerSystem", function(system_name, com_name)
    return ECS.createSystemBase(system_name, com_name)
end)

function SystemClass:onAttached()
    local node = self:getComByType("NodeCom")
    if node then
        local map = node:getNodeByName("map")

        local collision_layer = map:getLayer("Collision")
        local mask_layer = map:getLayer("Mask")
        collision_layer:setVisible(false)
        mask_layer:setVisible(false)
    end
end

function SystemClass:onUpdate()

end

return SystemClass
