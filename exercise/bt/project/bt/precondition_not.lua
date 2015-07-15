
local BT = bt

local Common = BT.import(".common")

local ObjectClass = Common.Class("PreconditionNOT")

function ObjectClass:initialize(lhs)
    assert(lhs)
    self.m_lhs = lhs

    BT.debug("precondition not initialize")
end

function ObjectClass:onEvaluate(input)
    return not self.m_lhs:onEvaluate(input)
end

return ObjectClass
