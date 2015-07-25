
local lib = require("lib.init")
local utils = require("utils.init")
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

    function love.mousepressed(x, y, button)
        local owner = self:getOwner()
        if owner:getData("dead") then
            return
        end

        if button == "l" then
            x, y = utils.Camera:toWorld(x, y)
            owner:fire(x, y)
        end
    end
end

function ObjectClass:onDraw()
    local owner = self:getOwner()
    if owner:getData("dead") then
        return
    end

    local owner = self:getOwner()
    local x, y = owner:getPosition()
    local w, h = owner:getSize()

    local mouse_x, mouse_y = love.mouse.getPosition()
    mouse_x, mouse_y = utils.Camera:toWorld(mouse_x, mouse_y)

    love.graphics.line(x+w/2, y+h/2, mouse_x, mouse_y)
end

return ObjectClass

