
local lib = import("..init")
local Constants = import(".constants")
local Node = import(".node")

local ObjectClass = lib.Class("SequenceNode", Node)

function ObjectClass:initialize(name, precondition)
    Node.initialize(self, name, precondition)
end

function ObjectClass:onInternalEvaluate(owner, input)
    local index
    if self.m_current_select_index then
        index = self.m_current_select_index
    else
        index = 1
    end

    local child = self.m_children[index]
    if child then
        local result = child:evaluate(owner, input)
        if result then
            self.m_current_select_index = index
        end
        return result
    end
end

function ObjectClass:onTransition(input)
    if self.m_current_select_index then
        local child = self.m_children[self.m_current_select_index]
        if child then
            child:transition(input)
            self.m_current_select_index = nil
        end
    end
end

function ObjectClass:onUpdate(owner, input, output)
    if not self.m_current_select_index then
        return
    end

    local child = self.m_children[self.m_current_select_index]
    local state = child:update(owner, input, output)
    if state == Constants.RunningStatus.Finish then
        self.m_current_select_index = self.m_current_select_index + 1
        if self.m_current_select_index > #self.m_children then
            self.m_current_select_index = nil
        else
            state = Constants.RunningStatus.Executing
        end
    elseif state == Contants.RunningStatus.Terminal then
        self.m_current_select_index = nil
    end

    return state
end

return ObjectClass
