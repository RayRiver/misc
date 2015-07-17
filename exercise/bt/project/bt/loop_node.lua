
local BT = bt

local Common = BT.import(".common")
local Node = BT.import(".node")

local ObjectClass = Common.Class("LoopNode", Node)

function ObjectClass:initialize(name, loop_count, precondition)
    Node.initialize(self, name, precondition)

    self.m_loop_count = loop_count
    self.m_current_loop_count = 0
end

function ObjectClass:onInternalEvaluate(input)
    if self.m_loop_count == nil or self.m_current_loop_count < self.m_loop_count then
        local child = self.m_children[1]
        if child and child:evaluate(input) then
            return true
        end
    end
    return false
end

function ObjectClass:onTransition(input)
    local child = self.m_children[1]
    if child then
        child:transition(input)
    end
    self.m_current_loop_count = 0
end

function ObjectClass:onUpdate(owner, input, output)
    local state = Common.RunningStatus.Finish

    local child = self.m_children[1]
    if child then
        state = child:update(owner, input, output)
        if state == Common.RunningStatus.Finish then
            if self.m_loop_count then
                self.m_current_loop_count = self.m_current_loop_count + 1
                if self.m_current_loop_count < self.m_loop_count then
                    state = Common.RunningStatus.Executing
                end
            else
                -- infinite
                state = Common.RunningStatus.Executing
            end
        end
    end

    if state ~= Common.RunningStatus.Executing then
        self.m_current_loop_count = 0
    end

    return state
end

return ObjectClass
