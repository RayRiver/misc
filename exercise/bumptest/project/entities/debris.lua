
local Utils = require("utils")
local Entity = require("entities.entity")

local minSize = 5
local maxSize = 10
local minVel = -100
local maxVel = -1 * minVel
local bounciness = 0.1

local ObjectClass = Utils.Class("Debris", Entity)

function ObjectClass:initialize(world, args)
    args = args or {}
    args.w = math.random(minSize, maxSize)
    args.h = math.random(minSize, maxSize)

    Entity.initialize(self, world, args)

    self.r, self.g, self.b = args.r or 0, args.g or 0, args.b or 0

    self.lived = 0
    self.lifeTime = 1 + 3 * math.random()
    self.vx = math.random(minVel, maxVel)
    self.vy = math.random(minVel, maxVel)
end

function ObjectClass:moveColliding(dt)
    local world = self.world

    local desired_x = self.x + self.vx * dt
    local desired_y = self.y + self.vy * dt

    local next_x, next_y, cols, len = world:move(self, desired_x, desired_y, function(item, other)
        local kind = other.class.name
        if kind == "Block" then return "bounce" end
    end)

    for i=1, len do
        local col = cols[i]
        self:changeVelocityByCollisionNormal(col.normal.x, col.normal.y, bounciness)
    end

    self.x, self.y = next_x, next_y
end

function ObjectClass:update(dt)
    self.lived = self.lived + dt

    if self.lived > self.lifeTime then
        self:destroy()
    else
        self:changeVelocityByGravity(dt)
        self:moveColliding(dt)
    end
end

function ObjectClass:draw()
    Utils.drawFilledRectangle(self.x, self.y, self.w, self.h, self.r, self.g, self.b)
end

return ObjectClass

