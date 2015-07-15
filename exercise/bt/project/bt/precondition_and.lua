
local BT = bt

local Common = BT.import(".common")

local ObjectClass = Common.Class("PreconditionAND")

function ObjectClass:initialize(lhs, rhs)
    assert(lhs)
    assert(rhs)
    self.m_lhs = lhs
    self.m_rhs = rhs

    BT.debug("precondition and initialize")
end

function ObjectClass:onEvaluate(input)
    return self.m_lhs:onEvaluate(input) and self.m_rhs:onEvaluate(input)
end

return ObjectClass
