
local lib = import("..init")

local ObjectClass = lib.Class("PreconditionOR")

function ObjectClass:initialize(lhs, rhs)
    assert(lhs)
    assert(rhs)
    self.m_lhs = lhs
    self.m_rhs = rhs

    lib.debug("precondition or initialize")
end

function ObjectClass:onEvaluate(owner, input)
    return self.m_lhs:onEvaluate(owner, input) or self.m_rhs:onEvaluate(owner, input)
end

return ObjectClass
