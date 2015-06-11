
local Utils = require("utils")
local Entity = require("entity")

local ObjectClass = Utils.Class("Tile", Entity)

function ObjectClass:initialize(tile_config)
    Entity.initialize(self)

    self.x = tile_config.x
    self.y = tile_config.y
    self.width = tile_config.w
    self.height = tile_config.h
    self.col = tile_config.col
    self.row = tile_config.row
    self.index = tile_config.index
    self.gid = tile_config.gid
end

function ObjectClass:setSlope()

end

function ObjectClass:onOverlap(other)
    --print("overlap: ", self.col, self.row)
end

return ObjectClass
