
local BT = bt

local Common = BT.import(".common")
local Node = BT.import(".node")

local ObjectClass = Common.Class("ActionNode", Node)

function ObjectClass:initialize(name, config, precondition)
    Node.initialize(self, name, precondition)

    self.m_config = config
    self.m_is_running = false
end

function ObjectClass:getNodeConfig()
    return self.m_config
end

function ObjectClass:onEnter(owner, input)
    BT.debugFormat("action %s onEnter...", tostring(self))
end

function ObjectClass:onExit(owner, input, state)
    BT.debugFormat("action %s onExit...", tostring(self))
end

function ObjectClass:onExecute(owner, input, output)
    -- override me
    return Common.RunningStatus.Finish
end

function ObjectClass:onTransition(input)
    if self.m_is_running then
        self:onExit(input, Common.RunningStatus.Terminal)
        self.m_is_running = false
    end
end

function ObjectClass:onUpdate(owner, input, output)
    if not self.m_is_running then
        self:onEnter(owner, input)
        self.m_is_running = true
    end

    local state = self:onExecute(owner, input, output)
    if state == Common.RunningStatus.Executing then
        return state
    else
        self.m_is_running = false
        self:onExit(owner, input, state)
        return state
    end
end

return ObjectClass
