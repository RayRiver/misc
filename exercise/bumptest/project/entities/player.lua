
local Utils = require("utils")
local Entity = require("entities.entity")
local Input = require("input")
local Puff = require("entities.puff")
local Debris = require("entities.debris")

local ObjectClass = Utils.Class("Player", Entity)
--ObjectClass:include(Utils.Stateful)

local ENTITY_WIDTH = 32
local ENTITY_HEIGHT = 64
local bounciness = 0.1

function ObjectClass:initialize(map, world, args)
    args = args or {}
    args.w = ENTITY_WIDTH
    args.h = ENTITY_HEIGHT

    Entity.initialize(self, world, args)

    self.map = map
    self.isDead = false
    self.onGround = false
    self.isJumping = false
    self.isFlying = false

    self.puffCoolDown = 0
    self.puffCoolDownMax = 2

    self.r, self.g, self.b = 55, 255, 55
end

function ObjectClass:update(dt)
    self:updateInputs(dt)
    self:changeVelocityByGravity(dt)
    self:moveColliding(dt)
end

function ObjectClass:die()
    self.isDead = true
    self.r, self.g, self.b = 255, 0, 0

    for i = 1, 20 do
        Debris:new(self.world, {
            x = math.random(self.x, self.x+self.w),
            y = math.random(self.y, self.y+self.h),
            r = self.r,
            g = self.g,
            b = self.b,
        })
    end

    local cx,cy = self:getCenter()
    self.w = math.random(8, 10)
    self.h = math.random(8, 10)
    self.x = cx + self.w / 2
    self.y = cy + self.h / 2
    self.vx = math.random(-100, 100)
    self.vy = math.random(-100, 100)
    self.world:remove(self)
    self.world:add(self, self.x, self.y, self.w, self.h)
end

function ObjectClass:updateInputs(dt)
    if self.isDead then return end

    local vx, vy = self.vx, self.vy

    local speed = 20000

    if love.keyboard.isDown("a") then
        vx = -speed * dt
    elseif love.keyboard.isDown("d") then
        vx = speed * dt
    else
        vx = 0
    end
    if love.keyboard.isDown("w") then
        --vy = -speed * dt
    elseif love.keyboard.isDown("s") then
        --vy = speed * dt
    else
        --vy = 0
    end

    local inputs = Input:instance():popInputs()
    local input_jump = false
    local input_die = false
    for _, k in ipairs(inputs) do
        if k == "k" then
            input_jump = true
            break
        elseif k == "j" then
            input_die = true
            break
        end
    end
    if input_jump then
        if self.onGround then
            self.isJumping = true
            vy = - 1000
        else
            self.isFlying = true
            self.puffCoolDown = 0
            self.puffUpdateOrder = 0
        end
    end

    if input_die then
        self:die()
        return
    end

    if self.isFlying then
        if not love.keyboard.isDown("k") then
            self.isFlying = false
        end

        vy = vy - 7000 * dt
        if vy < -500 then
            vy = -500
        end

        if self.puffCoolDown == 0 then
            self.puffUpdateOrder = self.puffUpdateOrder + 1
            Puff:new(self.world, {
                x = self.x + (self.w/4),
                y = self.y+self.h,
                vx = 20 * (1-math.random()),
                vy = 50,
                minSize = 1,
                maxSize = 3,
                updateOrder = self.puffUpdateOrder,
            })
            Puff:new(self.world, {
                x = self.x + (self.w/4*3),
                y = self.y+self.h,
                vx = 20 * (1-math.random()),
                vy = 50,
                minSize = 1,
                maxSize = 3,
                updateOrder = self.puffUpdateOrder,
            })
        end
        self.puffCoolDown = self.puffCoolDown + 1
        if self.puffCoolDown == self.puffCoolDownMax then
            self.puffCoolDown = 0
        end
    end

    self.vx, self.vy = vx, vy
end

function ObjectClass:moveColliding(dt)
    self.onGround = false
    local world = self.world

    local desired_x = self.x + self.vx * dt
    local desired_y = self.y + self.vy * dt

    local next_x, next_y, cols, len = world:move(self, desired_x, desired_y, function(item, other)
        local kind = other.class.name
        if kind == 'Block' or kind == 'Guardian' then
            return 'slide'
        end
    end)

    --Utils.print("len: ", cols)
    for i = 1, len do
        local col = cols[i]

        self:changeVelocityByCollisionNormal(col.normal.x, col.normal.y, bounciness)

        if col.normal.y < 0 then
            self.onGround = true
            self.isJumping = false
            self.isFlying = false
            self.vy = 0
        elseif col.normal.y > 0 then
            self.vy = 0
        end
    end

    self.x, self.y = next_x, next_y
end

function ObjectClass:draw(drawDebug)
    Utils.drawFilledRectangle(self.x, self.y, self.w, self.h, self.r, self.g, self.b)
end

return ObjectClass
