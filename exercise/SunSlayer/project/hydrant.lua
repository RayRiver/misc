
local Utils = require("utils")
local Bullet = require("bullet")

local ObjectClass = Utils.Class("Hydrant")

function ObjectClass:initialize()
    self.m_sprite = love.graphics.newImage("data/texture/hydrant.png")

    local part = love.graphics.newImage('data/texture/part.png')

    self.m_spout = love.graphics.newParticleSystem(part, 5000)
    self.m_spout:setAreaSpread('normal', 0.5, 0.5)
    self.m_spout:setParticleLifetime(0.1, 0.2)
    self.m_spout:setSpread(math.pi/3)
    self.m_spout:setLinearAcceleration(0, 500, 0, 500)
    self.m_spout:setColors(128, 255, 255, 255, 0, 128, 255, 255)
    self.m_spout:setSizes(2, 0)
    self.m_spout:setSpeed(50, 200)

    self.m_blast = love.graphics.newParticleSystem(part, 5000)
    self.m_blast:setParticleLifetime(0.1, 1.5)
    self.m_blast:setSpeed(100, 400)
    self.m_blast:setSpread(math.pi * 2)
    self.m_blast:setLinearAcceleration(0, 500, 0, 500)
    self.m_blast:setColors(128, 255, 255, 255, 0, 128, 255, 255)
    self.m_blast:setSizes(2, 0)
    self.m_blast:setSizeVariation(1)

    self.m_respawn_timer = Utils.Timer:new()
    self.m_shoot_timer = Utils.Timer:new()

    self.m_fly_sound = love.audio.newSource("data/audio/fly.wav")
    self.m_shoot_sound = love.audio.newSource("data/audio/shoot.wav")
    self.m_explode_sound = love.audio.newSource("data/audio/explode.wav")
    self.m_hit_sound = love.audio.newSource("data/audio/hit.wav")

    self.m_water_max = 3000

    self.m_can_shoot = true

    self.m_bullets = {}

    self:init()
end

function ObjectClass:init()
    self.m_dead = false
    
    self.w = 24
    self.h = 32
    
    self.x = 0
    self.y = -self.h/2
    
    self.vx = 0
    self.vy = 0
    
    self.speed = 8
    self.angle = 0

    self.m_water = 0--self.m_water_max
end

function ObjectClass:update(dt)
    self.m_respawn_timer.update(dt)
    self.m_shoot_timer.update(dt)

    for i, bullet in pairs(self.m_bullets) do
        bullet:update(dt)
        if bullet.m_dead then
            table.remove(self.m_bullets, i)
            self.m_blast:setPosition(bullet.x, bullet.y)
            self.m_blast:emit(4)
            self.m_hit_sound:stop()
            self.m_hit_sound:play()
        end
    end

    self.m_spout:update(dt)
    self.m_blast:update(dt)

    if self.m_dead then return end

    local d = Utils.Vector(0, self.h/2)
    d:rotate_inplace(self.angle)
    self.m_spout:setPosition(self.x + d.x, self.y + d.y)
    self.m_spout:setDirection(math.pi/2 + self.angle)

    if love.keyboard.isDown('up') then
        if self.m_water > 2 then
            self.m_water = self.m_water - 2
            self.m_spout:emit(5)
            self.vx = self.vx + (self.speed*math.cos(self.angle - math.pi/2) - self.vx)*0.1
            self.vy = self.vy + (self.speed*math.sin(self.angle - math.pi/2) - self.vy)*0.1
            self.m_fly_sound:play()
        else
            self.m_water = 0
            --self.vy = self.vy + 0.1
        end
    end

    if love.keyboard.isDown('left') then
        self.angle = self.angle - 0.05
    elseif love.keyboard.isDown('right') then
        self.angle = self.angle + 0.05
    end

    if self.y + self.h/2 + self.vy > 0 then
        if love.keyboard.isDown('up') or self.vy > 8 then
            self.vy = 0
            self:explode()
            return
        else
            self.vx = self.vx * 0.95
            self.vy = 0 - (self.y + self.h/2)
            self.angle = 0

            local delta = self.m_water_max - self.m_water
            if delta >= 10 then
                delta = math.floor(delta / 10)
            end
            self.m_water = self.m_water + delta
        end
    end

    self.x = self.x + self.vx
    self.y = self.y + self.vy

    if self.y >= 0 then
        self.vy = 0
    else
        self.vy = self.vy + 0.1
    end

    if love.keyboard.isDown('a') then
        if self.m_can_shoot then
            if self.m_water > 9 then
                local d = Utils.Vector(0, -self.h/2)
                d:rotate_inplace(self.angle)
                local bullet = Bullet:new(self.x + d.x, self.y + d.y, self.angle + (math.random() - 0.5)*0.1)
                table.insert(self.m_bullets, bullet)

                self.m_water = self.m_water - 9
                self.m_shoot_sound:stop()
                self.m_shoot_sound:play()
                self.m_can_shoot = false
                self.m_shoot_timer.add(0.1, function()
                    self.m_can_shoot = true
                end)
            end
        end
    end
end

function ObjectClass:draw()
    love.graphics.draw(self.m_spout)
    love.graphics.draw(self.m_blast)

    for _, bullet in pairs(self.m_bullets) do
        bullet:draw()
    end

    if not self.m_dead then
        love.graphics.draw(self.m_sprite, self.x, self.y, self.angle, 1, 1, self.w/2, self.h/2)
    end
end

function ObjectClass:explode()
    self.m_blast:setPosition(self.x, self.y)
    self.m_blast:emit(10 + self.m_water/3)
    self.m_dead = true
    self.m_water = 0

    self.m_explode_sound:play()

    self.m_respawn_timer.add(2.5, function()
        self:init()
    end)
end

return ObjectClass