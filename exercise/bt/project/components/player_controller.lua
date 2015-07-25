
local lib = require("lib.init")
local Component = import(".component")

local ObjectClass = lib.Class("PlayerController", Component)

function ObjectClass:onAttached()

end

function ObjectClass:onDetached()

end

function ObjectClass:onUpdate(dt)
    local owner = self:getOwner()
    if owner:getData("dead") then
        return
    end

    local vx, vy = 0, 0
    if love.keyboard.isDown("a") then
        vx = -1
    elseif love.keyboard.isDown("d") then
        vx = 1
    end
    if love.keyboard.isDown("w") then
        vy = -1
    elseif love.keyboard.isDown("s") then
        vy = 1
    end

    local speed = 500
    if vx == 0 and vy == 0 then
        owner:setVelocity(0, 0)
    else
        local n = math.sqrt(vx * vx + vy * vy)
        vx = vx / n * speed
        vy = vy / n * speed
        owner:setVelocity(vx, vy)
    end
end

return ObjectClass

