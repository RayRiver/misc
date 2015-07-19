
local lib = import("..init")
local PrioritySelectorNode = import(".priority_selector_node")

local ObjectClass = lib.Class("NonPrioritySelectorNode", PrioritySelectorNode)

function ObjectClass:onInternalEvaluate(owner, input)
    if self.m_evaluate_select_child then
        if self.m_evaluate_select_child:evaluate(owner, input) then
            return true
        end
    end
    return PrioritySelectorNode.onInternalEvaluate(self, owner, input)
end

return ObjectClass
