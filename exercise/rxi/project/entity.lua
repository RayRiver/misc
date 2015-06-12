
local Utils = require("utils")
local Rect = require("rect")

local ObjectClass = Utils.Class("Entity", Rect)

function ObjectClass:initialize()
    Rect.initialize(self)

    self.last = Rect(0, 0)
    self.velocity = Rect(0, 0)
    self.maxVelocity = Rect(math.huge, math.huge)
    self.accel = Rect(0, 0)
    self.drag = Rect(0, 0)

    self.m_solid = true
end

function ObjectClass:isSolid()
    return self.m_solid
end

function ObjectClass:update(dt)
    if dt == 0 then return end

    Rect.clone(self, self.last)

    -- update velocity
    self.velocity.x = self.velocity.x + self.accel.x * dt
    self.velocity.y = self.velocity.y + self.accel.y * dt
    if math.abs(self.velocity.x) > self.maxVelocity.x then
        self.velocity.x = self.maxVelocity.x * Utils.sign(self.velocity.x)
    end
    if math.abs(self.velocity.y) > self.maxVelocity.y then
        self.velocity.y = self.maxVelocity.y * Utils.sign(self.velocity.y)
    end

    -- update position
    self.x = self.x + self.velocity.x * dt
    self.y = self.y + self.velocity.y * dt

    -- update drag
    if self.accel.x == 0 and self.drag.x > 0 then
        local sign = Utils.sign(self.velocity.x)
        self.velocity.x = self.velocity.x - self.drag.x * dt * sign
        if (self.velocity.x < 0) ~= (sign < 0) then
            self.velocity.x = 0
        end
    end
    if self.accel.y == 0 and self.drag.y > 0 then
        local sign = Utils.sign(self.velocity.y)
        self.velocity.y = self.velocity.y - self.drag.y * dt * sign
        if (self.velocity.y < 0) ~= (sign < 0) then
            self.velocity.y = 0
        end
    end
end

function ObjectClass:separate(other)
    if self == other then return end

    if not self:overlaps(other) then return end

    -- 检测到碰撞
    Rect.clone(self.last, self)
end

function ObjectClass:onOverlap(other)
    if self:isSolid() and other:isSolid() then
        self:separate(other)
    end
end

return ObjectClass
