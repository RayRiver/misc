
local BT = bt

local Common = BT.import(".common")
local Node = BT.import(".node")

local function init_status(self)
    for i, _ in ipairs(self.m_running_status) do
        self.m_running_status[i] = Common.RunningStatus.Executing
    end
end

local ObjectClass = Common.Class("ParallelNode", Node)

function ObjectClass:initialize(finish_condition, name, precondition)
    Node.initialize(self, name, precondition)

    if type(finish_condition) ~= "string" then
        self.m_finish_condition = Common.FinishCondition.OR
    else
        local s = string.lower(finish_condition)
        if s == Common.FinishCondition.AND or s == Common.FinishCondition.OR then
            self.m_finish_condition = s
        else
            assert(false)
            self.m_finish_condition = Common.FinishCondition.OR
        end
    end

    self.m_running_status = Common.createTable()
end

function ObjectClass:onInternalEvaluate(input)
    local status_count = #self.m_running_status
    local child_count = #self.m_children

    if status_count < child_count then
        for i, child in ipairs(self.m_children) do
            self.m_running_status[i] = Common.RunningStatus.Executing
        end
    end

    for _, child in ipairs(self.m_children) do
        local result = child:evaluate(input)
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

function ObjectClass:onUpdate(input, output)
    local finished_count = 0
    local child_count = #self.m_children

    for i, child in ipairs(self.m_children) do
        local state = self.m_running_status[i]
        if self.m_finish_condition == Common.FinishCondition.OR then
            -- OR
            if state == Common.RunningStatus.Executing then
                child:update(input, output)
            else
                finished_count = child_count
                break
            end
        else
            -- AND
            if state == Common.RunningStatus.Executing then
                child:update(input, output)
            else
                finished_count = finished_count + 1
            end
        end
    end

    if finished_count == child_count then
        init_status(self)
        return Common.RunningStatus.Finish
    else
        return Common.RunningStatus.Executing
    end
end

return ObjectClass
