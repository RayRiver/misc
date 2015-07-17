
local lib = import("..init")

local ObjectClass = lib.Class("PreconditionNOT")

function ObjectClass:initialize(lhs)
    assert(lhs)
    self.m_lhs = lhs

    lib.debug("precondition not initialize")
end

function ObjectClass:onEvaluate(input)
    return not self.m_lhs:onEvaluate(input)
end

return ObjectClass
