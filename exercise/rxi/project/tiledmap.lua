
local Utils = require("utils")
local Tile = require("tile")
local Entity = require("entity")

local ObjectClass = Utils.Class("TiledMap", Entity)

function ObjectClass:initialize()
    Entity.initialize(self)

    self.m_tiled_map = Utils.Tiled.Map:new()
    self.m_tiled_map:load("data/map/home")

    self.x = -210
    self.y = -210

    self.m_tiled_map:setPos(self.x, self.y)

    self.tilewidth = self.m_tiled_map.tilewidth
    self.tileheight = self.m_tiled_map.tileheight
    self.widthInTiles = self.m_tiled_map.width
    self.heightInTiles = self.m_tiled_map.height

    self.width = self.m_tiled_map.tilewidth * self.m_tiled_map.width
    self.height = self.m_tiled_map.tileheight * self.m_tiled_map.height

    self.m_solid = false

    self.tiles = {}
    local layer = self.m_tiled_map:getLayer("main")
    layer:foreachTile(function(tile_config)
        local tile = Tile:new(tile_config)
        self.tiles[tile_config.index] = tile
    end)

    --Utils.print("tiledmap: ", self)
end

function ObjectClass:draw()
    self.m_tiled_map:draw()
end

function ObjectClass:onOverlap(other)
    -- 根据other找出有重叠的tile
    local start_x = math.floor((other:left() - self.x) / self.tilewidth)
    local start_y = math.floor((other:top() - self.y) / self.tileheight)
    local end_x = math.floor((other:right() - self.x) / self.tilewidth)
    local end_y = math.floor((other:top() - self.y) / self.tileheight)
    start_x = math.max(start_x, 0)
    start_y = math.max(start_y, 0)
    end_x = math.min(end_x, self.widthInTiles-1)
    end_y = math.min(end_y, self.heightInTiles-1)

    for y = start_y, end_y, 1 do
        for x = start_x, end_x, 1 do
            local index = y * self.widthInTiles + x
            local tile = self.tiles[index]
            if tile then
                tile:onOverlap(other)
            end
        end
    end
end

return ObjectClass
