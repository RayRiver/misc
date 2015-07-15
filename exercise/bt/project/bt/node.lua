
local BT = bt

local Common = BT.import(".common")

local ObjectClass = Common.Class("Node")

function ObjectClass:__tostring()
    return string.format("{%s:%s}", self.class.name, self.m_name)
end

function ObjectClass:initialize(name, precondition)
    self.m_children = Common.createTable()
    self.m_name = name or ""

    if precondition then
        self:setPrecondition(precondition)
    end

    BT.debugFormat("node %s initialize", tostring(self))
end

function ObjectClass:setName(name)
    self.m_name = name or ""
end

function ObjectClass:getName(name)
    return self.m_name
end

function ObjectClass:addChild(child, name)
    table.insert(self.m_children, child)
    if name then
        child:setName(name)
    end
    return self
end

function ObjectClass:setPrecondition(precondition)
    self.m_precondition = precondition
end

function ObjectClass:evaluate(input)
    BT.debugFormat("node %s evaluate", tostring(self))
    return (self.m_precondition == nil or self.m_precondition:onEvaluate(input)) and self:onInternalEvaluate(input)
end

function ObjectClass:transition(input)
    BT.debugFormat("node %s transition", tostring(self))
    return self:onTransition(input)
end

function ObjectClass:update(input, output)
    BT.debugFormat("node %s update", tostring(self))
    return self:onUpdate(input, output)
end

function ObjectClass:onInternalEvaluate(input)
    -- override me
    return true
end

function ObjectClass:onTransition(input)
    -- override me
end

function ObjectClass:onUpdate(input, output)
    -- override me
end

return ObjectClass
