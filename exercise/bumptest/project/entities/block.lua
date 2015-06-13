
local Utils = require("utils")
local Entity = require("entities.Entity")

local ObjectClass = Utils.Class("Block", Entity)

function ObjectClass:initialize(world, args)
    Entity.initialize(self, world, args)
end

function ObjectClass:update(dt)

end

function ObjectClass:draw()
    Utils.drawFilledRectangle(self.x, self.y, self.w, self.h, 100, 100, 255)
end

return ObjectClass
