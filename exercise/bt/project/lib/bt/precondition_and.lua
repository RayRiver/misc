
local lib = import("..init")

local ObjectClass = lib.Class("PreconditionAND")

function ObjectClass:initialize(lhs, rhs)
    assert(lhs)
    assert(rhs)
    self.m_lhs = lhs
    self.m_rhs = rhs

    lib.debug("precondition and initialize")
end

function ObjectClass:onEvaluate(owner, input)
    return self.m_lhs:onEvaluate(owner, input) and self.m_rhs:onEvaluate(owner, input)
end

return ObjectClass
