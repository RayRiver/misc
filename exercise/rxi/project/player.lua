
local Utils = require("utils")
local Entity = require("entity")

local ObjectClass = Utils.Class("Player", Entity)

function ObjectClass:initialize()
    Entity.initialize(self)

    self.m_sprite = love.graphics.newImage("data/image/player.png")

    local tw, th = self.m_sprite:getWidth(), self.m_sprite:getHeight()
    self.x = 0
    self.y = 0
    self.width = tw/4
    self.height = th/2
    self.direction = 1
    self.angle = 0


    self.speed = 300
    self.drag.x = 900
    self.drag.y = 900

    self.quad = love.graphics.newQuad(0, 0, self.width, self.height, tw, th)
end

function ObjectClass:update(dt)
    function love.keypressed(key)
        if key == 'k' then
        end
    end

    if love.keyboard.isDown("a") then
        --self.x = self.x - self.speed
        self.direction = -1
        self.accel.x = -self.speed
    elseif love.keyboard.isDown("d") then
        --self.x = self.x + self.speed
        self.direction = 1
        self.accel.x = self.speed
    else
        self.accel.x = 0
    end

    if love.keyboard.isDown("w") then
        --self.y = self.y - self.speed
        self.accel.y = self.accel.y - self.speed
    elseif love.keyboard.isDown("s") then
        --self.y = self.y + self.speed
        self.accel.y = self.accel.y + self.speed
    else
        self.accel.y = 0
    end

    Entity.update(self, dt)
end

function ObjectClass:draw()
    love.graphics.draw(self.m_sprite, self.quad,
        self.x, self.y,
        self.angle,
        1*self.direction, 1,
        0, 0
    )
end

function ObjectClass:onOverlap(other)
    Entity.onOverlap(self, other)
end

return ObjectClass
