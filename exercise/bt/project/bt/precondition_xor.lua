
local BT = bt

local Common = BT.import(".common")

local ObjectClass = Common.Class("PreconditionXOR")

function ObjectClass:initialize(lhs, rhs)
    assert(lhs)
    assert(rhs)
    self.m_lhs = lhs
    self.m_rhs = rhs
end

function ObjectClass:onEvaluate(input)
    return self.m_lhs:onEvaluate(input) ~= self.m_rhs:onEvaluate(input)
end

return ObjectClass
