
local Utils = require("utils")

local ObjectClass = Utils.Class("Entity")

local gravityAccel  = 3000 -- pixels per second^2

function ObjectClass:initialize(world, args)
    args = args or {}

    self.world = world
    self.x = args.x or 0
    self.y = args.y or 0
    self.w = args.w or 1
    self.h = args.h or 1
    self.updateOrder = args.updateOrder or 0

    self.vx = 0
    self.vy = 0

    self.world:add(self, self.x, self.y, self.w, self.h)
end

function ObjectClass:changeVelocityByGravity(dt)
    self.vy = self.vy + gravityAccel * dt
end

function ObjectClass:changeVelocityByCollisionNormal(nx, ny, bounciness)
    bounciness = bounciness or 0
    local vx, vy = self.vx, self.vy

    if (nx < 0 and vx > 0) or (nx > 0 and vx < 0) then
        vx = -vx * bounciness
    end

    if (ny < 0 and vy > 0) or (ny > 0 and vy < 0) then
        vy = -vy * bounciness
    end

    self.vx, self.vy = vx, vy
end

function ObjectClass:destroy()
    self.world:remove(self)
end

function ObjectClass:getCenter()
    return self.x + self.w / 2, self.y + self.h / 2
end

function ObjectClass:getClassUpdateOrder()
    return self.class.updateOrder or 0
end

function ObjectClass:getUpdateOrder()
    return self.updateOrder
end

return ObjectClass
