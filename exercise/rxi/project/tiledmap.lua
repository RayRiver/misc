
local Utils = require("utils")

local ObjectClass = Utils.Class("TiledMap")

function ObjectClass:initialize()
    self.m_tiled_map = Utils.Tiled.Map:new()
    self.m_tiled_map:load("data/map/home")

    self.x = -210
    self.y = -210

    self.m_tiled_map:setPos(self.x, self.y)
    self.w = self.m_tiled_map.tilewidth * self.m_tiled_map.width
    self.h = self.m_tiled_map.tileheight * self.m_tiled_map.height

    self.tilewidth = self.m_tiled_map.tilewidth
    self.tileheight = self.m_tiled_map.tileheight

    local layer = self.m_tiled_map:getLayer("main")
    layer:foreachTile(function(tile)
    end)
end

function ObjectClass:draw()
    self.m_tiled_map:draw()
end

function ObjectClass:onOverlap(other)
    local layer = self.m_tiled_map:getLayer("main")
    layer:foreachTile(function(tile)
        if Utils.rectIntersect(tile, other) then
            print(layer.x+tile.offset_x, layer.y+tile.offset_y)
        end
    end)
end

return ObjectClass
