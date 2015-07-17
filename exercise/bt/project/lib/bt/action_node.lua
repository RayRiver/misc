
local lib = import("..init")
local Constants = import(".constants")
local Node = import(".node")

local ObjectClass = lib.Class("ActionNode", Node)

function ObjectClass:initialize(name, config, precondition)
    Node.initialize(self, name, precondition)

    self.m_config = config
    self.m_is_running = false
end

function ObjectClass:getNodeConfig()
    return self.m_config
end

-- override me
function ObjectClass:onEnter(owner, input)
    lib.debugFormat("action %s onEnter...", tostring(self))
end

-- override me
function ObjectClass:onExit(owner, input, state)
    lib.debugFormat("action %s onExit...", tostring(self))
end

-- override me
function ObjectClass:onExecute(owner, input, output)
    return Constants.RunningStatus.Finish
end

function ObjectClass:onTransition(input)
    if self.m_is_running then
        self:onExit(input, Constants.RunningStatus.Terminal)
        self.m_is_running = false
    end
end

function ObjectClass:onUpdate(owner, input, output)
    if not self.m_is_running then
        self:onEnter(owner, input)
        self.m_is_running = true
    end

    local state = self:onExecute(owner, input, output)
    if state == Constants.RunningStatus.Executing then
        return state
    else
        self.m_is_running = false
        self:onExit(owner, input, state)
        return state
    end
end

return ObjectClass
