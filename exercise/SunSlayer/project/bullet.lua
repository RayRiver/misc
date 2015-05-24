
local Utils = require("utils")

local ObjectClass = Utils.Class("Bullet")

function ObjectClass:initialize(x, y, angle)
    self.x, self.y = x, y
    self.vx, self.vx = 0, 0
    self.w, self.h = 16, 16
    self.angle = angle
    self.speed = 16
    self.m_dead = false
    self.m_time = 0
    self.m_dead_time = 2

    self.m_sprite = love.graphics.newImage('data/texture/water.png')

    local part = love.graphics.newImage('data/texture/part.png')

    self.m_spout = love.graphics.newParticleSystem(part, 5000)
    self.m_spout:setParticleLifetime(0.05, 0.1)
    self.m_spout:setColors(128, 255, 255, 255, 0, 128, 255, 255)
    self.m_spout:setSizes(1.5, 0.5)
    self.m_spout:setEmissionRate(20)
end

function ObjectClass:update(dt)
    self.m_time = self.m_time + dt

    self.m_spout:update(dt)
    self.m_spout:setPosition(self.x, self.y)

    self.vx, self.vy = self.speed*math.cos(self.angle - math.pi/2), self.speed*math.sin(self.angle - math.pi/2)
    self.x, self.y = self.x + self.vx, self.y + self.vy

    if self.y > 0 then
        self.m_dead = true
    elseif self.m_time > self.m_dead_time then
        self.m_dead = true
    end
end

function ObjectClass:draw()
    love.graphics.draw(self.m_spout)
    love.graphics.draw(self.m_sprite, self.x, self.y, self.angle, 1, 1, self.w/2, self.h/2)
end

return ObjectClass
