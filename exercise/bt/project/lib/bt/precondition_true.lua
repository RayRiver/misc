
local lib = import("..init")

local ObjectClass = lib.Class("PreconditionTRUE")

function ObjectClass:initialize()
    lib.debug("precondition true initialize")
end

function ObjectClass:onEvaluate(input)
    return true
end

return ObjectClass
