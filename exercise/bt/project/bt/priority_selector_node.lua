
local BT = bt

local Common = BT.import(".common")
local Node = BT.import(".node")

local ObjectClass = Common.Class("PrioritySelectorNode", Node)

function ObjectClass:initialize(name, precondition)
    Node.initialize(self, name, precondition)
end

function ObjectClass:onInternalEvaluate(input)
    for _, child in ipairs(self.m_children) do
        if child:evaluate(input) then
            self.m_evaluate_select_child = child
            return true
        end
    end
    return false
end

function ObjectClass:onTransition(input)
    if self.m_current_select_child then
        self.m_current_select_child:transition(input)
        self.m_current_select_child = nil
    end
end

function ObjectClass:onUpdate(owner, input, output)
    if self.m_evaluate_select_child == nil then
        assert(false)
        return Common.RunningStatus.Finish
    end

    -- transition node
    if self.m_current_select_child ~= self.m_evaluate_select_child then
        self:transition(input)
        self.m_current_select_child = self.m_evaluate_select_child
    end

    -- update node
    if self.m_current_select_child then
        local state = self.m_current_select_child:update(owner, input, output)
        if state ~= Common.RunningStatus.Executing then
            self.m_current_select_child = nil
        end
        return state
    end

    assert(false)
    return Common.RunningStatus.Finish
end

return ObjectClass
