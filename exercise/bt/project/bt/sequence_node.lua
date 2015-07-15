
local BT = bt

local Common = BT.import(".common")
local Node = BT.import(".node")

local ObjectClass = Common.Class("SequenceNode", Node)

function ObjectClass:initialize(name, precondition)
    Node.initialize(self, name, precondition)
end

function ObjectClass:onInternalEvaluate(input)
    local child
    if self.m_current_select_child then
        child = self.m_current_select_child
    else
        child = self.m_children[1]
    end

    if child then
        local result = self.m_current_select_child:evaluate(input)
        if result then
            self.m_current_select_child = child
        end
        return result
    end
end

function ObjectClass:onTransition(input)
    if self.m_current_select_child then
        self.m_current_select_child:transition(input)
        self.m_current_select_child = nil
    end
end

function ObjectClass:onUpdate(input, output)
    if not self.m_current_select_child then
        return
    end

    local state = self.m_current_select_child:update(input, output)
    if state == Common.RunningStatus.Finish then
        self.m_current_select_child = self.m_current_select_child + 1
        if self.m_current_select_child > #self.m_children then
            self.m_current_select_child = nil
        else
            state = Common.RunningStatus.Executing
        end
    elseif state == Common.RunningStatus.Terminal then
        self.m_current_select_child = nil
    end

    return state
end

return ObjectClass
