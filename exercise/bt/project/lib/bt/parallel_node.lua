
local lib = import("..init")
local Constants = import(".constants")
local Node = import(".node")

local function init_status(self)
    for i, _ in ipairs(self.m_running_status) do
        self.m_running_status[i] = Constants.RunningStatus.Executing
    end
end

local ObjectClass = lib.Class("ParallelNode", Node)

function ObjectClass:initialize(name, finish_condition, precondition)
    Node.initialize(self, name, precondition)

    if type(finish_condition) ~= "string" then
        self.m_finish_condition = Constants.FinishCondition.OR
    else
        local s = string.lower(finish_condition)
        if s == Constants.FinishCondition.AND or s == Constants.FinishCondition.OR then
            self.m_finish_condition = s
        else
            assert(false)
            self.m_finish_condition = Constants.FinishCondition.OR
        end
    end

    self.m_running_status = {}
end

function ObjectClass:onInternalEvaluate(owner, input)
    local status_count = #self.m_running_status
    local child_count = #self.m_children

    if status_count < child_count then
        for i, child in ipairs(self.m_children) do
            self.m_running_status[i] = Constants.RunningStatus.Executing
        end
    end

    for _, child in ipairs(self.m_children) do
        local result = child:evaluate(owner, input)
        if not result then
            return false
        end
    end

    return true
end

function ObjectClass:onTransition(input)
    init_status(self)

    for _, child in ipairs(self.m_children) do
        child:transition(input)
    end
end

function ObjectClass:onUpdate(owner, input, output)
    local finished_count = 0
    local child_count = #self.m_children

    for i, child in ipairs(self.m_children) do
        local state = self.m_running_status[i]
        if self.m_finish_condition == Constants.FinishCondition.OR then
            -- OR
            if state == Constants.RunningStatus.Executing then
                child:update(owner, input, output)
            else
                finished_count = child_count
                break
            end
        else
            -- AND
            if state == Constants.RunningStatus.Executing then
                child:update(input, output)
            else
                finished_count = finished_count + 1
            end
        end
    end

    if finished_count == child_count then
        init_status(self)
        return Constants.RunningStatus.Finish
    else
        return Constants.RunningStatus.Executing
    end
end

return ObjectClass
