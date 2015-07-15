
local BT = bt

local Common = BT.import(".common")

local ObjectClass = Common.Class("PreconditionFALSE")

function ObjectClass:initialize()
    BT.debug("precondition false initialize")
end

function ObjectClass:onEvaluate(input)
    return false
end

return ObjectClass
