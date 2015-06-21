
local Utils = require("utils")
local Entity = require("entities.entity")

local ENTITY_WIDTH = 32
local ENTITY_HEIGHT = 64

local ObjectClass = Utils.Class("Blockman", Entity)

function ObjectClass:initialize(world, config)
    config = config or {}
    config.width = config.width or ENTITY_WIDTH
    config.height = config.height or ENTITY_HEIGHT

    Entity.initialize(self, world, config)
end

function ObjectClass:onCollideFilter(other)
    local kind = other.class.name
    if kind == "Block" or kind == "Blockman" then return "slide" end
end

return ObjectClass
