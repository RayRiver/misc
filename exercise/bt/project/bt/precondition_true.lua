
local BT = bt

local Common = BT.import(".common")

local ObjectClass = Common.Class("PreconditionTRUE")

function ObjectClass:initialize()

end

function ObjectClass:onEvaluate(input)
    return true
end

return ObjectClass
