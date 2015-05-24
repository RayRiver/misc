
local Utils = require("utils")

local ObjectClass = Utils.Class("Player")

function ObjectClass:initialize()
    self.m_sprite = love.graphics.newImage("data/image/player.png")

    local tw, th = self.m_sprite:getWidth(), self.m_sprite:getHeight()
    self.x = 0
    self.y = 0
    self.w = tw/4
    self.h = th/2
    self.direction = 1
    self.angle = 0

    self.speed = 3

    self.quad = love.graphics.newQuad(0, 0, self.w, self.h, tw, th)
end

function ObjectClass:update(dt)
    function love.keypressed(key)
        if key == 'k' then
        end
    end

    if love.keyboard.isDown("a") then
        self.x = self.x - self.speed
        self.direction = -1
    elseif love.keyboard.isDown("d") then
        self.x = self.x + self.speed
        self.direction = 1
    elseif love.keyboard.isDown("w") then
        self.y = self.y - self.speed
    elseif love.keyboard.isDown("s") then
        self.y = self.y + self.speed
    end
end

function ObjectClass:draw()
    love.graphics.draw(self.m_sprite, self.quad,
        self.x, self.y,
        self.angle,
        1*self.direction, 1,
        0, 0
    )
end

return ObjectClass
