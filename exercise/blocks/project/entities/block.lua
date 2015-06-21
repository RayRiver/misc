
local Utils = require("utils")
local Entity = require("entities.entity")

local ObjectClass = Utils.Class("Block", Entity)

function ObjectClass:initialize(world, config)
    config = config or {}
    config.static = true
    config.r = config.r or 100
    config.g = config.g or 100
    config.b = config.b or 200

    Entity.initialize(self, world, config)
end

return ObjectClass
