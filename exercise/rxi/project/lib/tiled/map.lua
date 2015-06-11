
local Sets = require("lib.tiled.sets")
local Layer = require("lib.tiled.layer")

local Map = {}
Map.__index = Map

local function new(class)
    return setmetatable({
        x = 0,
        y = 0,
    }, Map)
end

function Map:load(map)
    local module = require(map)
    package.loaded[map] = nil

    -- support orthogonal only
    assert(module.orientation == "orthogonal", "tiled map load error: support orthogonal only")

    self.width = module.width
    self.height = module.height
    self.tilewidth = module.tilewidth
    self.tileheight = module.tileheight

    self.m_sets = Sets:new()
    for i = 1, #module.tilesets do
        self.m_sets:addSet(module.tilesets[i])
    end

    self.m_layers = {}
    self.m_layers_map = {}
    for i = 1, #module.layers do
        if module.layers[i].type == "tilelayer" then
            local layer = Layer:new(module.layers[i], self.m_sets, self.tilewidth, self.tileheight)
            table.insert(self.m_layers, layer)
            self.m_layers_map[layer.name] = layer
        end
    end
end

function Map:move(dx, dy)
    self.x = self.x + dx
    self.y = self.y + dy
    for _, layer in ipairs(self.m_layers) do
        layer:move(dx, dy)
    end
end

function Map:setPos(x, y)
    self:move(x - self.x, y - self.y)
end

function Map:draw()
    for _, layer in ipairs(self.m_layers) do
        layer:draw()
    end
end

function Map:getLayer(name)
    return self.m_layers_map[name]
end

-- the module
return setmetatable({new = new},
    {__call = function(_, ...) return new(...) end})
