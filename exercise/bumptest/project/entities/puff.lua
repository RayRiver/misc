
local Utils = require("utils")
local Entity = require("entities.entity")

local defaultVx      = 0
local defaultVy      = -10
local defaultMinSize = 2
local defaultMaxSize = 10

local ObjectClass = Utils.Class("Puff", Entity)

function ObjectClass:initialize(world, args, updateOrder, x, y, vx, vy, minSize, maxSize)
    args = args or {}

    local vx, vy = args.vx or defaultVx, args.vy or defaultVy
    local minSize = args.minSize or defaultMinSize
    local maxSize = args.maxSize or defaultMaxSize
    args.w = math.random(minSize, maxSize)
    args.h = math.random(minSize, maxSize)

    Entity.initialize(self, world, args)

    self.lived = 0
    self.lifeTime = 1 + math.random()

    self.vx, self.vy = vx, vy
end

function ObjectClass:update(dt)
    self.lived = self.lived + dt

    if self.lived >= self.lifeTime then
        self:destroy()
    else
        -- expand
        local cx, cy = self:getCenter()
        local percent = self.lived / self.lifeTime
        if percent < 0.2 then
            self.w = self.w + (100 + percent) * dt
            self.h = self.h + (100 + percent) * dt
        else
            self.w = self.w + (20 + percent) * dt
        end
        self.x = cx - self.w / 2
        self.y = cy - self.h / 2

        local next_x = self.x + self.vx * dt
        local next_y = self.y + self.vy * dt
        self.world:update(self, next_x, next_y)
        self.x, self.y = next_x, next_y
    end
end

function ObjectClass:draw()
    local percent = (self.lifeTime-self.lived)/self.lifeTime

    local percent1 = percent
    --if percent1 < 0.8 then percent1 = 0 end
    local r, g, b = 200, 100, 0
    r, g, b = 255 - (255-r) * percent1, 255 - (255-g) * percent1, 255 - (255-b) * percent1

    local opacity = 1 * percent

    Utils.drawFilledRectangle(self.x, self.y, self.w, self.h,
        r, g, b, opacity)
end

return ObjectClass
