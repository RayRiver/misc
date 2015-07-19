
local lib = import("..init")

local ObjectClass = lib.Class("PreconditionFALSE")

function ObjectClass:initialize()
    lib.debug("precondition false initialize")
end

function ObjectClass:onEvaluate(owner, input)
    return false
end

return ObjectClass
