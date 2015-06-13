
local Utils = require("utils")

local Input = Utils.Class("Input")

local _instance

function Input:instance()
    if _instance == nil then
        _instance = Input:new()
    end
    return _instance
end

function Input:initialize()
    self.inputs = {}
end

function Input:pushInput(k)
    table.insert(self.inputs, k)
end

function Input:popInputs()
    local inputs = self.inputs
    self.inputs = {}
    return inputs
end

return Input
