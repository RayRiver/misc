
local BT = bt

local Common = BT.import(".common")

local ObjectClass = Common.Class("Node")

function ObjectClass:initialize(name, precondition)
    self.m_children = Common.createTable()
    self.m_name = name or ""

    if precondition then
        self:setPrecondition(precondition)
    end
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
    return (self.m_precondition == nil or self.m_precondition:onEvaluate(input)) and self:onInternalEvaluate(input)
end

function ObjectClass:transition(input)
    return self:onTransition(input)
end

function ObjectClass:update(input, output)
    print("update node: " .. tostring(self.m_name))
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
