
local lib = import("..init")

local ObjectClass = lib.Class("PreconditionNOT")

function ObjectClass:initialize(lhs)
    assert(lhs)
    self.m_lhs = lhs

    lib.debug("precondition not initialize")
end

function ObjectClass:onEvaluate(owner, input)
    return not self.m_lhs:onEvaluate(owner, input)
end

return ObjectClass
