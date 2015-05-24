
local Utils = require("utils")

local ObjectClass = Utils.Class("Sun")

function ObjectClass:initialize()
    self.m_sprite = love.graphics.newImage('data/texture/sun.png')
    self.x, self.y = 500, -3000
    self.size = 160
    self.r = 1024
    self.m_dead = false

    self.m_hp_max = 1000
    self.m_hp = self.m_hp_max

    self.m_fire = love.graphics.newParticleSystem(self.m_sprite, 500)
    self.m_fire:setParticleLifetime(0.1, 0.3)
    self.m_fire:setSpeed(10, 200)
    self.m_fire:setSpread(math.pi*2)
    self.m_fire:setColors(255, 255, 0, 255, 255, 128, 0, 255, 255, 0, 0, 0)
    self.m_fire:setEmissionRate(20)
    self.m_fire:setPosition(self.x, self.y)

    local part = love.graphics.newImage('data/texture/part.png')

    self.m_explosion = love.graphics.newParticleSystem(part, 5000)
    self.m_explosion:setParticleLifetime(0.1, 0.6)
    self.m_explosion:setSpeed(100, 700)
    self.m_explosion:setLinearAcceleration(0, 500, 0, 500)
    self.m_explosion:setSpread(math.pi*2)
    self.m_explosion:setColors(255, 255, 0, 255, 255, 128, 0, 255, 255, 0, 0, 255, 40, 40, 40, 255)
    self.m_explosion:setSizes(8, 0)

    self.m_trail = love.graphics.newParticleSystem(part, 5000)
    self.m_trail:setParticleLifetime(0.1, 0.6)
    self.m_trail:setSpeed(200, 400)
    self.m_trail:setSpread(math.pi/12)
    self.m_trail:setColors(255, 255, 0, 255, 255, 128, 0, 255, 255, 0, 0, 255, 40, 40, 40, 255)
    self.m_trail:setSizes(14, 2)
end

function ObjectClass:update(dt)
    self.m_explosion:update(dt)
    self.m_trail:update(dt)
    self.m_fire:update(dt)

    self.m_fire:setSizes(self.r/160, self.r/160*1.1)
end

function ObjectClass:draw()
    love.graphics.setBlendMode('additive')
    love.graphics.draw(self.m_trail)
    love.graphics.setBlendMode('alpha')

    love.graphics.draw(self.m_sprite, self.x, self.y, 0, self.r/self.size, self.r/self.size, self.size/2, self.size/2)
    love.graphics.setBlendMode('additive')
    love.graphics.draw(self.m_fire)
    love.graphics.draw(self.m_explosion)
    love.graphics.setBlendMode('alpha')
end

return ObjectClass
