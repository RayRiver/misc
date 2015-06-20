
local Utils = require("utils")
local Entity = require("entities.entity")

local ENTITY_WIDTH = 32
local ENTITY_HEIGHT = 64

local ObjectClass = Utils.Class("Guardian", Entity)

function ObjectClass:initialize(world, args)
    args = args or {}
    args.w = ENTITY_WIDTH
    args.h = ENTITY_HEIGHT

    self.target = args.target or nil

    Entity.initialize(self, world, args)
end

function ObjectClass:update(dt)
    if self.target then
        local cx, cy = self:getCenter()
        local target_x, target_y = self.target:getCenter()

        local dx, dy = target_x - cx, target_y - cy
        local dist2 = dx * dx + dy * dy

        if dist2 < 200 * 200 then
            self.aim_target = true

            --local item_info, len = self.world:querySegmentWithCoords(cx, cy, target_x, target_y)
            -- item_info[1] is self
            --local info  = item_info[2]

        end
    end
end

function ObjectClass:draw()
    Utils.drawFilledRectangle(self.x, self.y, self.w, self.h, 255, 0, 255)

    if self.target and self.aim_target then
        local cx, cy = self:getCenter()
        local target_x, target_y = self.target:getCenter()

        love.graphics.setColor(255, 255, 0, 255)

        love.graphics.setLineWidth(2)
        love.graphics.line(cx, cy, target_x, target_y)
        love.graphics.setLineWidth(1)
    end
end

return ObjectClass
