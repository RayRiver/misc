
local Set = require("lib.tiled.set")
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

    self.m_sets = {}
    for i = 1, #module.tilesets do
        local set = Set:new(module.tilesets[i])
        table.insert(self.m_sets, set)
    end

    self.m_layers = {}
    for i = 1, #module.layers do
        if module.layers[i].type == "tilelayer" then
            local layer = Layer:new(module.layers[i], self.m_sets)
            table.insert(self.m_layers, layer)
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

-- the module
return setmetatable({new = new},
    {__call = function(_, ...) return new(...) end})
