
local _M = {}

-- 常量
local Constants = import(".constants")
for k, v in pairs(Constants) do
    _M[k] = v
end

-- 工厂
_M.Factory = import(".factory")
_M.Reader = import(".reader")

local Class = import("..middleclass")
local ActionNode = import(".action_node")
_M.ActionNodeClass = function(name)
    return Class(name, ActionNode)
end
_M.ConditionClass = function(name)
    local class = Class(name)
    return class
end

-- 注册类
local factory = _M.Factory
factory:registerNodeClass("PrioritySelectorNode", import(".priority_selector_node"))
factory:registerNodeClass("NonPrioritySelectorNode", import(".non_priority_selector_node"))
factory:registerNodeClass("SequenceNode", import(".sequence_node"))
factory:registerNodeClass("LoopNode", import(".loop_node"))
factory:registerNodeClass("ParallelNode", import(".parallel_node"))

factory:registerNodeClass("ActionNode", import(".action_node"))

factory:registerCondClass("PreconditionTRUE", import(".precondition_true"))
factory:registerCondClass("PreconditionFALSE", import(".precondition_false"))
factory:registerCondClass("PreconditionNOT", import(".precondition_not"))
factory:registerCondClass("PreconditionAND", import(".precondition_and"))
factory:registerCondClass("PreconditionOR", import(".precondition_or"))
factory:registerCondClass("PreconditionXOR", import(".precondition_xor"))

return _M

