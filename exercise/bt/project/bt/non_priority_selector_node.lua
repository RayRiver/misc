
local BT = bt

local Common = BT.import(".common")
local PrioritySelectorNode = BT.import(".priority_selector_node")

local ObjectClass = Common.Class("NonPrioritySelectorNode", PrioritySelectorNode)

function ObjectClass:onInternalEvaluate(input)
    if self.m_evaluate_select_child then
        if self.m_evaluate_select_child:evaluate(input) then
            return true
        end
    end
    return PrioritySelectorNode.onInternalEvaluate(input)
end

return ObjectClass
